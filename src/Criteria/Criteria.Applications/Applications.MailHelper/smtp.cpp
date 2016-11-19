/*
Module : SMTP.CPP
Purpose: Implementation for a MFC class encapsulation of the SMTP protocol
Created: PJN / 22-05-1998
History: PJN / 15-06-1998 1) Fixed the case where a single dot occurs on its own
                          in the body of a message
													2) Class now supports Reply-To Header Field
                          3) Class now supports file attachments

				 PJN / 18-06-1998 1) Fixed a memory overwrite problem which was occurring 
				                  with the buffer used for encoding base64 attachments

         PJN / 27-06-1998 1) The case where a line begins with a "." but contains
                          other text is now also catered for. See RFC821, Section 4.5.2
                          for further details.
                          2) m_sBody in CSMTPMessage has now been made protected.
                          Client applications now should call AddBody instead. This
                          ensures that FixSingleDot is only called once even if the 
                          same message is sent a number of times.
                          3) Fixed a number of problems with how the MIME boundaries
                          were defined and sent.
                          4) Got rid of an unreferenced formal parameter 
                          compiler warning when doing a release build

         PJN / 11-09-1998 1) VC 5 project file is now provided
                          2) Attachment array which the message class contains now uses
                          references instead of pointers.
                          3) Now uses Sleep(0) to yield our time slice instead of Sleep(100),
                          this is the preferred way of writting polling style code in Win32
                          without serverly impacting performance.
                          4) All Trace statements now display the value as returned from
                          GetLastError
                          5) A number of extra asserts have been added
                          6) A AddMultipleRecipients function has been added which supports added a 
                          number of recipients at one time from a single string
                          7) Extra trace statements have been added to help in debugging

         PJN / 12-09-98   1) Removed a couple of unreferenced variable compiler warnings when code
                          was compiled with Visual C++ 6.0
                          2) Fixed a major bug which was causing an assert when the CSMTPAttachment
                          destructor was being called in the InitInstance of the sample app. 
                          This was inadvertingly introduced for the 1.2 release. The fix is to revert 
                          fix 2) as done on 11-09-1998. This will also help to reduce the number of 
                          attachment images kept in memory at one time.

         PJN / 18-01-99   1) Full CC & BCC support has been added to the classes

         PJN / 22-02-99   1) Addition of a Get and SetTitle function which allows a files attachment 
                          title to be different that the original filename
                          2) AddMultipleRecipients now ignores addresses if they are empty.
                          3) Improved the reading of responses back from the server by implementing
                          a growable receive buffer
                          4) timeout is now 60 seconds when building for debug

         PJN / 25-03-99   1) Now sleeps for 250 ms instead of yielding the time slice. This helps 
                          reduce CPU usage when waiting for data to arrive in the socket

         PJN / 14-05-99   1) Fixed a bug with the way the code generates time zone fields in the Date headers.

         PJN / 10-09-99   1) Improved CSMTPMessage::GetHeader to include mime field even when no attachments
                          are included.

         PJN / 16-02-00   1) Fixed a problem which was occuring when code was compiled with VC++ 6.0.




Copyright (c) 1998 - 2000 by PJ Naughter.  
All rights reserved.

*/

//////////////// Includes ////////////////////////////////////////////
#include "smtp.h"

char CSMTPAttachment::m_base64tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                      "abcdefghijklmnopqrstuvwxyz0123456789+/";
#define BASE64_MAXLINE  76
#define EOL  "\r\n"

#include "bOS/Tracer.h"


#include <stdlib.h>
#include <stdio.h>


//////////////// Implementation //////////////////////////////////////
CSMTPSocket::CSMTPSocket()
{
  m_hSocket = INVALID_SOCKET; //default to an invalid scoket descriptor

  // Initialize WinSock
    WORD wVer    = MAKEWORD(2,2);    
    if (WSAStartup(wVer,&wsaData) != NO_ERROR)
	{
        printf("WSAStartup %d\r\n", WSAGetLastError());        
        throw; 
    }
}

CSMTPSocket::~CSMTPSocket()
{
  Close();

  WSACleanup();
}

bool CSMTPSocket::Create()
{
  m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
  return (m_hSocket != INVALID_SOCKET);
}

bool CSMTPSocket::Connect(const char* pszHostAddress, int nPort)
{
	CM_CODEBLOCK(CSMTPSocket::Connect)
  //must have been created first
  assert(m_hSocket != INVALID_SOCKET);
  
	//Determine if the address is in dotted notation
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)nPort);
	sockAddr.sin_addr.s_addr = inet_addr(pszHostAddress);

	//If the address is not dotted notation, then do a DNS 
	//lookup of it.
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(pszHostAddress);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
      WSASetLastError(WSAEINVAL); 
			return FALSE;
		}
	}

	//Call the protected version which takes an address 
	//in the form of a standard C style struct.
	return Connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
}

bool CSMTPSocket::Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	CM_CODEBLOCK(CSMTPSocket::Connect)
	return (connect(m_hSocket, lpSockAddr, nSockAddrLen) != SOCKET_ERROR);
}

bool CSMTPSocket::Send(char* pszBuf, int nBuf)
{
	CM_CODEBLOCK(CSMTPSocket::Send)
  //must have been created first
  assert(m_hSocket != INVALID_SOCKET);

  return (send(m_hSocket, pszBuf, nBuf, 0) != SOCKET_ERROR);
}

int CSMTPSocket::Receive(char* pszBuf, int nBuf)
{
	CM_CODEBLOCK(CSMTPSocket::Receive)
  //must have been created first
  assert(m_hSocket != INVALID_SOCKET);

  return recv(m_hSocket, pszBuf, nBuf, 0); 
}

void CSMTPSocket::Close()
{
	CM_CODEBLOCK(CSMTPSocket::Close)
	if (m_hSocket != INVALID_SOCKET)
	{
		assert(SOCKET_ERROR != closesocket(m_hSocket));
		m_hSocket = INVALID_SOCKET;
	}
}

bool CSMTPSocket::IsReadible(bool& bReadible)
{
	CM_CODEBLOCK(CSMTPSocket::IsReadible)
  timeval timeout = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(m_hSocket, &fds);
  int nStatus = select(0, &fds, NULL, NULL, &timeout);
  if (nStatus == SOCKET_ERROR)
  {
    return FALSE;
  }
  else
  {
    bReadible = !(nStatus == 0);
    return TRUE;
  }
}


CSMTPAddress::CSMTPAddress() 
{
}

CSMTPAddress::CSMTPAddress(const CSMTPAddress& address)
{
  *this = address;
}

CSMTPAddress::CSMTPAddress(const String& sAddress) : 
              m_sEmailAddress(sAddress) 
{
  assert(m_sEmailAddress.size()); //An empty address is not allowed
}

CSMTPAddress::CSMTPAddress(const String& sFriendly, const String& sAddress) : 
              m_sFriendlyName(sFriendly), m_sEmailAddress(sAddress) 
{
  assert(m_sEmailAddress.size()); //An empty address is not allowed
}

CSMTPAddress& CSMTPAddress::operator=(const CSMTPAddress& r) 
{ 
  m_sFriendlyName = r.m_sFriendlyName; 
	m_sEmailAddress = r.m_sEmailAddress; 
	return *this;
}

String CSMTPAddress::GetRegularFormat() const
{
	CM_CODEBLOCK(CSMTPAddress::GetRegularFormat)
  assert(m_sEmailAddress.size()); //Email Address must be valid

  String sAddress;
  if (m_sFriendlyName.length() == 0 )
    sAddress = m_sEmailAddress;  //Just transfer the address across directly
  else
    sAddress=m_sFriendlyName;
	sAddress+=" ";
	sAddress+="<";
	sAddress+=m_sEmailAddress;
	sAddress+=">";

  return sAddress;
}

CSMTPAttachment::CSMTPAttachment()
{
  m_pszEncoded = NULL;
  m_nEncodedSize = 0;
}

CSMTPAttachment::~CSMTPAttachment()
{
  //free up any memory we allocated
  if (m_pszEncoded)
	{
    delete [] m_pszEncoded;
		m_pszEncoded = NULL;
	}
}

bool CSMTPAttachment::Attach(const String& sFilename)
{
CM_CODEBLOCK(CSMTPAttachment::Attach)

  assert(sFilename.length());  //Empty Filename !

  //free up any memory we previously allocated
  if (m_pszEncoded)
  {
    delete [] m_pszEncoded;
    m_pszEncoded = NULL;
  }

  //determine the file size
  /*TODO
  if ( !(bOS::IO::FileSystem::getFileAttributeFlags( sFilename ) & Exists & RegularFile) )
  {
    CM_TRACE_ERROR("Failed to get the status for file " << sFilename << " probably does not exist");
    return false;
  }
  */

  StringBuffer sFile;
  bOS::IO::FileSystem::getStringFileBinary(sFilename.c_str(), sFile);
  //allocate the encoded buffer
  int nOutSize = Base64BufferSize(sFile.size());
  m_pszEncoded = new char[nOutSize];

  //Do the encoding
  EncodeBase64(sFile.getData(), sFile.size(), m_pszEncoded, nOutSize, &m_nEncodedSize);

  //Hive away the filename
  char sPath[_MAX_PATH];
  char sFname[_MAX_FNAME];
  char sExt[_MAX_EXT];

  /**/
  _splitpath(sFilename.c_str(), NULL, NULL, sFname, sExt);
  //_tmakepath(sPath, NULL, NULL, sFname, sExt);

  m_sFilename = sFilename;
  m_sTitle = sFname;
  m_sTitle+=".";
  m_sTitle+= sExt;


  return true;
}

int CSMTPAttachment::Base64BufferSize(int nInputSize)
{
  int nOutSize = (nInputSize+2)/3*4;                    // 3:4 conversion ratio
  nOutSize += strlen(EOL)*nOutSize/BASE64_MAXLINE + 3;  // Space for newlines and NUL
  return nOutSize;
}

bool CSMTPAttachment::EncodeBase64(const char* pszIn, int nInLen, char* pszOut, int nOutSize, int* nOutLen)
{
	CM_CODEBLOCK(CSMTPAttachment::EncodeBase64)
  //Input Parameter validation
  assert(pszIn);
  assert(pszOut);
  assert(nOutSize);
  assert(nOutSize >= Base64BufferSize(nInLen));

#ifndef _DEBUG
  //justs get rid of "unreferenced formal parameter"
  //compiler warning when doing a release build
  nOutSize;
#endif

  //Set up the parameters prior to the main encoding loop
  int nInPos  = 0;
  int nOutPos = 0;
  int nLineLen = 0;

  // Get three characters at a time from the input buffer and encode them
  for (int i=0; i<nInLen/3; ++i) 
  {
    //Get the next 2 characters
    int c1 = pszIn[nInPos++] & 0xFF;
    int c2 = pszIn[nInPos++] & 0xFF;
    int c3 = pszIn[nInPos++] & 0xFF;

    //Encode into the 4 6 bit characters
    pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
    pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4)];
    pszOut[nOutPos++] = m_base64tab[((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6)];
    pszOut[nOutPos++] = m_base64tab[c3 & 0x3F];
    nLineLen += 4;

    //Handle the case where we have gone over the max line boundary
    if (nLineLen >= BASE64_MAXLINE-3) 
    {
      char* cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      nLineLen = 0;
    }
  }

  // Encode the remaining one or two characters in the input buffer
  char* cp;
  switch (nInLen % 3) 
  {
    case 0:
    {
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    case 1:
    {
      int c1 = pszIn[nInPos] & 0xFF;
      pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
      pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4)];
      pszOut[nOutPos++] = '=';
      pszOut[nOutPos++] = '=';
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    case 2:
    {
      int c1 = pszIn[nInPos++] & 0xFF;
      int c2 = pszIn[nInPos] & 0xFF;
      pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
      pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4)];
      pszOut[nOutPos++] = m_base64tab[((c2 & 0x0F) << 2)];
      pszOut[nOutPos++] = '=';
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    default: 
    {
      assert(FALSE); 
      break;
    }
  }
  pszOut[nOutPos] = 0;
  *nOutLen = nOutPos;
  return TRUE;
}





CSMTPMessage::CSMTPMessage() : m_sXMailer("CSMTPConnection v1.3")
{
}

CSMTPMessage::~CSMTPMessage()
{
	unsigned int uiSize = m_Attachments.size();
	for ( unsigned int ui=0; ui<uiSize; ui++)
	{
		delete m_Attachments.at(ui);
	}
}

int CSMTPMessage::GetNumberOfRecipients(RECIPIENT_TYPE RecipientType) const
{
	CM_CODEBLOCK(CSMTPMessage::GetNumberOfRecipients)
  int nSize = 0;
  switch (RecipientType)
  {
    case TO:  nSize = m_ToRecipients.size();  break;
    case CC:  nSize = m_CCRecipients.size();  break;
    case BCC: nSize = m_BCCRecipients.size(); break;
    default: assert(FALSE);                      break;
  }

	return nSize;
}

int CSMTPMessage::AddRecipient(CSMTPAddress& recipient, RECIPIENT_TYPE RecipientType)
{
  int nIndex = -1;
  switch (RecipientType)
  {
    case TO:  m_ToRecipients.push_back (recipient); nIndex = m_ToRecipients.size(); break;
    case CC:  m_CCRecipients.push_back(recipient);  nIndex = m_CCRecipients.size();break;
    case BCC: m_BCCRecipients.push_back(recipient); nIndex = m_BCCRecipients.size();break;
    default: assert(false);                            break;
  }

  return nIndex;
}

/*
void CSMTPMessage::RemoveRecipient(int nIndex, RECIPIENT_TYPE RecipientType)
{
  switch (RecipientType)
  {
    case TO:  m_ToRecipients.erase (.RemoveAt(nIndex);  break;
    case CC:  m_CCRecipients.RemoveAt(nIndex);  break;
    case BCC: m_BCCRecipients.RemoveAt(nIndex); break;
    default:  assert(FALSE);                    break;
  }
}
*/

CSMTPAddress CSMTPMessage::GetRecipient(int nIndex, RECIPIENT_TYPE RecipientType) const
{
  CSMTPAddress address;

  switch (RecipientType)
  {
    case TO:  address = m_ToRecipients[nIndex];  break;
    case CC:  address = m_CCRecipients[nIndex];  break;
    case BCC: address = m_BCCRecipients[nIndex]; break;
    default: assert(false);                            break;
  }

  return address;
}

int CSMTPMessage::AddAttachment(CSMTPAttachment* pAttachment)
{
  assert(pAttachment->GetFilename().size()); //an empty filename !
	m_Attachments.push_back(pAttachment);
	return m_Attachments.size();
}

/*
void CSMTPMessage::RemoveAttachment(int nIndex)
{
	m_Attachments.RemoveAt(nIndex);
}
*/

CSMTPAttachment* CSMTPMessage::GetAttachment(int nIndex) const
{
	return m_Attachments[nIndex];
}

int CSMTPMessage::GetNumberOfAttachments() const
{
	return m_Attachments.size();
}

String CSMTPMessage::GetHeader() const
{
	CM_CODEBLOCK(CSMTPMessage::GetHeader)

	char acBuffer[5000];
  //Form the Timezone info which will form part of the Date header
  TIME_ZONE_INFORMATION tzi;
  int nTZBias;
  if (GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_DAYLIGHT)
    nTZBias = tzi.Bias + tzi.DaylightBias;
  else

  nTZBias = tzi.Bias;
  sprintf(acBuffer, "%.2d%.2d", -nTZBias/60, nTZBias%60);

  StringBuffer sDate;
  sDate.append (bOS::Utils::DateTime::getCurrentDateTime().toString());
  sDate.append (acBuffer);

  //Create the "To:" part of the header
  String sTo;
  for (int i=0; i<GetNumberOfRecipients(TO); i++)
  {
    CSMTPAddress recipient = GetRecipient(i, TO);
    if (i)
 		  sTo += ",";
    sTo += recipient.GetRegularFormat();
  }

  //Create the "Cc:" part of the header
  String sCc;
  for (int i=0; i<GetNumberOfRecipients(CC); i++)
  {
    CSMTPAddress recipient = GetRecipient(i, CC);
    if (i)
 		  sCc += ",";
    sCc += recipient.GetRegularFormat();
  }

  //No Bcc info added in header

	//Stick everything together
	StringBuffer sBuf;
  if (sCc.length() > 0 )
	  sprintf(acBuffer, "From: %s\r\nTo: %s\r\nCc: %s\r\nSubject: %s\r\nDate: %s\r\nX-Mailer: %s\r\n", 
							  m_From.GetRegularFormat().c_str(),
                sTo.c_str(), 
                sCc.c_str(),
							  m_sSubject.c_str(),
							  sDate.getData(),
							  m_sXMailer.c_str());
  else
	  sprintf(acBuffer,"From: %s\r\nTo: %s\r\nSubject: %s\r\nDate: %s\r\nX-Mailer: %s\r\n", 
							  m_From.GetRegularFormat().c_str(),
                sTo.c_str(), 
							  m_sSubject.c_str(),
							  sDate.getData(),
							  m_sXMailer.c_str());

	sBuf.append (acBuffer);

	//Add the optional Reply-To Field
	if (m_ReplyTo.m_sEmailAddress.length() > 0)
	{
		sprintf(acBuffer, "Reply-To: %s\r\n", m_ReplyTo.GetRegularFormat().c_str());
		sBuf.append (acBuffer);
	}

	//Add the optional fields if attachments are included
	if (m_Attachments.size())
	{
		sBuf.append("MIME-Version: 1.0\r\nContent-type: multipart/mixed; boundary=\"#BOUNDARY#\"\r\n");
	}
	else
	{
		// avoid long textual message being automatically converted by the server:
		//sBuf.append("MIME-Version: 1.0\r\nContent-type: text/plain; charset=US-ASCII\r\n");    
		if (bHtmlFormat )
		{
			sBuf.append("MIME-Version: 1.0\r\nContent-type: text/html; charset=US-ASCII\r\n");    
		}
		else
		{
		// avoid long textual message being automatically converted by the server:
			sBuf.append("MIME-Version: 1.0\r\nContent-type: text/plain; charset=US-ASCII\r\n");    
		}
	}

	sBuf.append ("\r\n");

	//Return the result
	return sBuf.getData();
}

void CSMTPMessage::FixSingleDot(String& sBody)
{
	CM_CODEBLOCK(CSMTPMessage::FixSingleDot)
  int nFind = sBody.find ("\n.");
  if (nFind != -1)
  {
	  String sLeft = sBody.substr (1, nFind+1);
	  String sRight=sBody.substr(nFind+1);
	  FixSingleDot(sRight);
	  sBody = sLeft + "." + sRight;
  }
}

void CSMTPMessage::AddBody(const String& sBody)
{
  m_sBody = sBody;

  //Fix the case of a single dot on a line in the message body
  FixSingleDot(m_sBody);
}

/*
bool CSMTPMessage::AddMultipleRecipients(const String& sRecipients, RECIPIENT_TYPE RecipientType)
{
	CM_CODEBLOCK(TODO)
	assert(sRecipients.length()); //An empty string is now allowed
	
	//Loop through the whole string, adding recipients as they are encountered
	int length = sRecipients.length();
	char* buf = new TCHAR[length + 1];	// Allocate a work area (don't touch parameter itself)
	strcpy(buf, sRecipients.c_str());
	for (int pos=0, start=0; pos<=length; pos++)
	{
		//Valid separators between addresses are ',' or ';'
		if ((buf[pos] == ',') || (buf[pos] == ';') || (buf[pos] == 0))
		{
			buf[pos] = 0;	//Redundant when at the end of string, but who cares.
      String sTemp(&buf[start]);

			// Now divide the substring into friendly names and e-mail addresses
      CSMTPAddress To;
			int nMark = sTemp.find('<');
			if (nMark >= 0)
			{
				To.m_sFriendlyName = sTemp.Left(nMark);
				int nMark2 = sTemp.Find('>');
				if (nMark2 < nMark)
				{
          //An invalid string was sent in, fail the call
					delete[] buf;
          SetLastError(ERROR_INVALID_DATA);
          CM_TRACE_ERROR("An error occurred while parsing the recipients string"));
					return false;
				}
				// End of mark at closing bracket or end of string
				nMark2 > -1 ? nMark2 = nMark2 : nMark2 = sTemp.GetLength() - 1;
				To.m_sEmailAddress = sTemp.Mid(nMark + 1, nMark2 - (nMark + 1));
			}
			else
			{
				To.m_sEmailAddress = sTemp;
				To.m_sFriendlyName = "";
			}

      //Finally add the new recipient to the array of recipients
			To.m_sEmailAddress.TrimRight();
			To.m_sEmailAddress.TrimLeft();
			To.m_sFriendlyName.TrimRight();
			To.m_sFriendlyName.TrimLeft();
      if (To.m_sEmailAddress.GetLength())
        AddRecipient(To, RecipientType);

      //Move on to the next position
			start = pos + 1;
		}
	}
	delete[] buf;
	return TRUE;
}
*/






CSMTPConnection::CSMTPConnection()
{
  m_bConnected = FALSE;
#ifdef _DEBUG
  m_dwTimeout = 60000; //default timeout of 60 seconds when debugging
#else
  m_dwTimeout = 2000;  //default timeout of 2 seconds for normal release code
#endif
}

CSMTPConnection::~CSMTPConnection()
{
  if (m_bConnected)
    Disconnect();
}

bool CSMTPConnection::Connect(const char* pszHostName, int nPort)
{
  CM_CODEBLOCK(CSMTPConnection::Connect)

  //paramater validity checking
  assert(pszHostName);

  //Create the socket
  if (!m_SMTP.Create())
  {
    CM_TRACE_ERROR("Failed to create client socket, GetLastError returns: " << GetLastError());
    return false;
  }

  //Connect to the SMTP Host
  if (!m_SMTP.Connect(pszHostName, nPort))
  {
    CM_TRACE_ERROR("Could not connect to the SMTP server") // %s on port %d, GetLastError returns: %d\n"), pszHostName, nPort, GetLastError());
    return false;
  }
  else
  {
    //We're now connected !!
    m_bConnected = true;

    //check the response to the login
    if (!ReadCommandResponse(220))
    {
	  CM_TRACE_ERROR("An unexpected SMTP login response was received\n");
      Disconnect();
      return FALSE;
    }

		//retreive the localhost name
    char sHostName[100];
		gethostname(sHostName, sizeof(sHostName));

    //Send the HELO command
	StringBuffer sBuf;
	sBuf.append ("HELO ");
	sBuf.append (sHostName);
	sBuf.append ("%s\r\n");
	int nCmdLength = strlen(sBuf.getData());
    if (!m_SMTP.Send((char*)sBuf.getData(), nCmdLength))
    {
      Disconnect();
      CM_TRACE_ERROR("An unexpected error occurred while sending the HELO command\n");
      return false;
    }
		//check the response to the HELO command
    if (!ReadCommandResponse(250))
    {
      Disconnect();
      CM_TRACE_ERROR("An unexpected HELO response was received\n");
      return false;
    } 

    return true;
  }
}

bool CSMTPConnection::Disconnect()
{
CM_CODEBLOCK(CSMTPConnection::Disconnect)
	bool bSuccess = false;      

  //disconnect from the SMTP server if connected 
  if (m_bConnected)
  {
    char sBuf[10];
    strcpy(sBuf, "QUIT\r\n");
    int nCmdLength = strlen(sBuf);
    if (!m_SMTP.Send(sBuf, nCmdLength))
      CM_TRACE_ERROR("Failed in call to send QUIT command, GetLastError returns: " << GetLastError());

    //Check the reponse
    bSuccess = ReadCommandResponse(221);
    if (!bSuccess)
    {
      SetLastError(ERROR_BAD_COMMAND);
      CM_TRACE_ERROR("An unexpected QUIT response was received\n");
    }

    //Reset all the state variables
    m_bConnected = FALSE;
  }
  else
    CM_TRACE_ERROR("Already disconnected from SMTP server, doing nothing\n");
 
  //free up our socket
  m_SMTP.Close();
 
  return bSuccess;
}

bool CSMTPConnection::SendMessage(CSMTPMessage& Message)
{
	char acBuffer[5000];

	CM_CODEBLOCK(CSMTPConnection::SendMessage)

	//paramater validity checking
  assert(m_bConnected); //Must be connected to send a message

  //Send the MAIL command
	assert(Message.m_From.m_sEmailAddress.length());

	sprintf(acBuffer, "MAIL FROM:<%s>\r\n", Message.m_From.m_sEmailAddress.c_str());
	int nCmdLength = strlen(acBuffer);
  if (!m_SMTP.Send(acBuffer, nCmdLength))
  {
    CM_TRACE_ERROR("Failed in call to send MAIL command, GetLastError returns: " << GetLastError());
    return false;
  }

  //check the response to the MAIL command
  if (!ReadCommandResponse(250))
  {
    SetLastError(ERROR_BAD_COMMAND);
    CM_TRACE_ERROR("An unexpected MAIL response was received\n");
    return false;
  } 

  //Send the RCPT command, one for each recipient (includes the TO, CC & BCC recipients)

  //Must be sending to someone
  assert(Message.GetNumberOfRecipients(CSMTPMessage::TO) + 
         Message.GetNumberOfRecipients(CSMTPMessage::CC) + 
         Message.GetNumberOfRecipients(CSMTPMessage::BCC));

  //First the "To" recipients
  for (int i=0; i<Message.GetNumberOfRecipients(CSMTPMessage::TO); i++)
  {
    CSMTPAddress recipient = Message.GetRecipient(i, CSMTPMessage::TO);
    if (!SendRCPTForRecipient(recipient))
      return false;
  }

  //Then the "CC" recipients
  for (int i=0; i<Message.GetNumberOfRecipients(CSMTPMessage::CC); i++)
  {
    CSMTPAddress recipient = Message.GetRecipient(i, CSMTPMessage::CC);
    if (!SendRCPTForRecipient(recipient))
      return false;
  }

  //Then the "BCC" recipients
  for (int i=0; i<Message.GetNumberOfRecipients(CSMTPMessage::BCC); i++)
  {
    CSMTPAddress recipient = Message.GetRecipient(i, CSMTPMessage::BCC);
    if (!SendRCPTForRecipient(recipient))
      return false;
  }

  //Send the DATA command
  char* pszDataCommand = "DATA\r\n";
  nCmdLength = strlen(pszDataCommand);
  if (!m_SMTP.Send(pszDataCommand, nCmdLength))
  {
    CM_TRACE_ERROR("Failed in call to send MAIL command, GetLastError returns: " << GetLastError());
    return false;
  }

  //check the response to the DATA command
  if (!ReadCommandResponse(354))
  {
    SetLastError(ERROR_BAD_COMMAND);
    CM_TRACE_ERROR("An unexpected DATA response was received\n");
    return false;
  } 

  //Send the Header
  String sHeader = Message.GetHeader();
  if (!m_SMTP.Send((char*)sHeader.c_str(), sHeader.length()))
  {
    CM_TRACE_ERROR("Failed in call to send the header, GetLastError returns: " << GetLastError());
    return false;
  }

	//Send the Mime Header for the body
  if (Message.m_Attachments.size())
  {
	  String sBodyHeader;
	if (Message.IsHTML() )
	{
		sBodyHeader = "\r\n--#BOUNDARY#\r\nContent-Type: text/html; charset=us-ascii\r\nContent-Transfer-Encoding: quoted-printable\r\n\r\n";
	}
	else
	{
		sBodyHeader = "\r\n--#BOUNDARY#\r\nContent-Type: text/plain; charset=us-ascii\r\nContent-Transfer-Encoding: quoted-printable\r\n\r\n";
	}
	if (!m_SMTP.Send((char*)sBodyHeader.c_str(), sBodyHeader.length()))
	{
		CM_TRACE_ERROR("Failed in call to send the body header, GetLastError returns: " << GetLastError());
		return false;
	}
  }

  //Send the body
  if (!m_SMTP.Send((char*)Message.m_sBody.c_str(), Message.m_sBody.length()))
  {
    CM_TRACE_ERROR("Failed in call to send the header, GetLastError returns: "  << GetLastError());
    return false;
  }

  //Send all the attachments
  for (int i=0; i<Message.m_Attachments.size(); i++)
  {
    CSMTPAttachment* pAttachment = Message.m_Attachments[i];

		//First send the Mime header for each attachment

	sprintf(acBuffer, "\r\n\r\n--#BOUNDARY#\r\nContent-Type: application/octet-stream; name=%s\r\nContent-Transfer-Encoding: base64\r\nContent-Disposition: attachment; filename=%s\r\n\r\n", 
                    pAttachment->GetFilename().c_str(), pAttachment->GetTitle().c_str());

		nCmdLength = strlen(acBuffer);
		if (!m_SMTP.Send(acBuffer, nCmdLength))
		{
			CM_TRACE_ERROR("Failed in call to send Mime attachment header, GetLastError returns: " << GetLastError());
			return false;
		}

    //Then send the encoded attachment
    if (!m_SMTP.Send((char*)pAttachment->GetEncodedBuffer(), pAttachment->GetEncodedSize()))
    {
      CM_TRACE_ERROR("Failed in call to send the attachment, GetLastError returns: " << GetLastError());
      return false;
    }
  }

	//Send the final mime boundary
  if (Message.m_Attachments.size())
  {
	  char* pszFinalBoundary = "\r\n--#BOUNDARY#--";
	  nCmdLength = strlen(pszFinalBoundary);
	  if (!m_SMTP.Send(pszFinalBoundary, nCmdLength))
	  {
		  CM_TRACE_ERROR("Failed in call to send Mime attachment header, GetLastError returns: " << GetLastError());
		  return false;
	  }
  }

  //Send the end of message indicator
  char* pszEOM = "\r\n.\r\n";
	nCmdLength = strlen(pszEOM);
  if (!m_SMTP.Send(pszEOM, nCmdLength))
  {
    CM_TRACE_ERROR("Failed in call to send end of message indicator, GetLastError returns: " << GetLastError());
    return false;
  }

  //check the response to the End of Message command
  if (!ReadCommandResponse(250))
  {
    SetLastError(ERROR_BAD_COMMAND);
    CM_TRACE_ERROR("An unexpected end of message response was received\n");
    return false;
  } 

	return true;
}

bool CSMTPConnection::SendRCPTForRecipient(CSMTPAddress& recipient)
{
	CM_CODEBLOCK(CSMTPConnection::SendRCPTForRecipient)

	char acBuffer[5000];
	assert(recipient.m_sEmailAddress.length()); //must have an email address for this recipient

	sprintf(acBuffer, "RCPT TO:<%s>\r\n", recipient.m_sEmailAddress.c_str());
  int nCmdLength = strlen(acBuffer);
  if (!m_SMTP.Send(acBuffer, nCmdLength))
  {
    CM_TRACE_ERROR("Failed in call to send RCPT command, GetLastError returns: " << GetLastError());
    return false;
  }

  //check the response to the RCPT command
  if (!ReadCommandResponse(250))
  {
    SetLastError(ERROR_BAD_COMMAND);
    CM_TRACE_ERROR("An unexpected RCPT response was received\n");
    return false;
  } 
  
  return true;
}

bool CSMTPConnection::ReadCommandResponse(int nExpectedCode)
{
  char* pszOverFlowBuffer = NULL;
  char sBuf[256];
  bool bSuccess = ReadResponse(sBuf, 256, "\r\n", nExpectedCode, &pszOverFlowBuffer);
  if (pszOverFlowBuffer)
    delete [] pszOverFlowBuffer;

  return bSuccess;
}

bool CSMTPConnection::ReadResponse(char* pszBuffer, int nInitialBufSize, char* pszTerminator, int nExpectedCode, char** ppszOverFlowBuffer, int nGrowBy)
{
	CM_CODEBLOCK(CSMTPConnection::ReadResponse)

  assert(ppszOverFlowBuffer);          //Must have a valid string pointer
  assert(*ppszOverFlowBuffer == NULL); //Initially it must point to a NULL string

  //must have been created first
  assert(m_bConnected);

  //The local variables which will receive the data
  char* pszRecvBuffer = pszBuffer;
  int nBufSize = nInitialBufSize;
  
  //retrieve the reponse using until we
	//get the terminator or a timeout occurs
	bool bFoundTerminator = FALSE;
	int nReceived = 0;
	DWORD dwStartTicks = ::GetTickCount();
	while (!bFoundTerminator)
	{
		//Has the timeout occured
		if ((::GetTickCount() - dwStartTicks) >	m_dwTimeout)
		{
		  pszRecvBuffer[nReceived] = '\0';
      SetLastError(WSAETIMEDOUT);
      m_sLastCommandResponse = pszRecvBuffer; //Hive away the last command reponse
			return FALSE;
		}

    //check the socket for readability
    bool bReadible;
    if (!m_SMTP.IsReadible(bReadible))
    {
	    pszRecvBuffer[nReceived] = '\0';
			m_sLastCommandResponse = pszRecvBuffer; //Hive away the last command reponse
			return FALSE;
    }
    else if (!bReadible) //no data to receive, just loop around
    {
      Sleep(250); //Sleep for a while before we loop around again
      continue;
    }

		//receive the data from the socket
    int nBufRemaining = nBufSize-nReceived-1; //Allows allow one space for the NULL terminator
    if (nBufRemaining<0)
      nBufRemaining = 0;
	  int nData = m_SMTP.Receive(pszRecvBuffer+nReceived, nBufRemaining);

    //Reset the idle timeout if data was received
    if (nData>=0)
    {
			dwStartTicks = ::GetTickCount();

      //Increment the count of data received
		  nReceived += nData;							   
    }

    //If an error occurred receiving the data
		if (nData == SOCKET_ERROR)
		{
      //NULL terminate the data received
      if (pszRecvBuffer)
		    pszBuffer[nReceived] = '\0';

      m_sLastCommandResponse = pszRecvBuffer; //Hive away the last command reponse
		  return FALSE; 
		}
		else
		{
      //NULL terminate the data received
      if (pszRecvBuffer)
		    pszRecvBuffer[nReceived] = '\0';

      if (nBufRemaining-nData == 0) //No space left in the current buffer
      {
        //Allocate the new receive buffer
        nBufSize += nGrowBy; //Grow the buffer by the specified amount
        LPSTR pszNewBuf = new char[nBufSize];

        //copy the old contents over to the new buffer and assign 
        //the new buffer to the local variable used for retreiving 
        //from the socket
        if (pszRecvBuffer)
          strcpy(pszNewBuf, pszRecvBuffer);
        pszRecvBuffer = pszNewBuf;

        //delete the old buffer if it was allocated
        if (*ppszOverFlowBuffer)
          delete [] *ppszOverFlowBuffer;
        
        //Remember the overflow buffer for the next time around
        *ppszOverFlowBuffer = pszNewBuf;        
      }
		}

    //Check to see if the terminator character(s) have been found
		bFoundTerminator = (strstr(pszRecvBuffer, pszTerminator) != NULL);
	}

	//Remove the terminator from the response data
  pszRecvBuffer[nReceived - strlen(pszTerminator)] = '\0';

  //determine if the response is an error
	char sCode[4];
	strncpy(sCode, pszRecvBuffer, 3);
	sCode[3] = '\0';
	sscanf(sCode, "%d", &m_nLastCommandResponseCode);
	bool bSuccess = (m_nLastCommandResponseCode == nExpectedCode);

  if (!bSuccess)
  {
    SetLastError(WSAEPROTONOSUPPORT);
    m_sLastCommandResponse = pszRecvBuffer; //Hive away the last command reponse
  }

  return bSuccess;
}
