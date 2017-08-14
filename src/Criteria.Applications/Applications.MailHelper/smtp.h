#ifndef __SMTP_H__
#define __SMTP_H__

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
#include "bOS/bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOS/bOSDateTime.h"
using namespace bOS::Utils;

#include "bOS/bOSFileSystem.h"

#include <winsock2.h>
#include <assert.h>
#include <vector>

//Simple Socket wrapper class
class CSMTPSocket
{
public:
//Constructors / Destructors
  CSMTPSocket();
  ~CSMTPSocket();

//methods
  bool Create();
  bool Connect(const char* pszHostAddress, int nPort );
  bool Send(char* pszBuf, int nBuf);
  void Close();
  int Receive(char*, int nBuf);
  bool IsReadible(bool& bReadible);

protected:
  bool Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen);
  SOCKET m_hSocket;

  WSADATA wsaData;
};

                     
//Encapsulation of an SMTP email address, used for recipients and in the From: field
class CSMTPAddress
{
public: 
//Constructors / Destructors
  CSMTPAddress();
  CSMTPAddress(const CSMTPAddress& address);
	CSMTPAddress(const String& sAddress);
	CSMTPAddress(const String& sFriendly, const String& sAddress);
	CSMTPAddress& operator=(const CSMTPAddress& r);

//Methods
  String GetRegularFormat() const;

//Data members
 String        m_sFriendlyName; //Would set it to contain something like "PJ Naughter"
 String        m_sEmailAddress; //Would set it to contains something like "pjn@indigo.ie"
};


//Encapsulation of an SMTP file attachment
class CSMTPAttachment
{
public:
//Constructors / Destructors
	CSMTPAttachment();
  ~CSMTPAttachment();

//methods
  bool Attach(const String& sFilename);
  String GetFilename() const { return m_sFilename; };
  const char* GetEncodedBuffer() const { return m_pszEncoded; };
  int GetEncodedSize() const { return m_nEncodedSize; };
  String GetTitle() const { return m_sTitle; };
  void SetTitle(const String& sTitle) { m_sTitle = sTitle; };

protected:
  int Base64BufferSize(int nInputSize);
  bool EncodeBase64(const char* aIn, int aInLen, char* aOut, int aOutSize, int* aOutLen);
  static char m_base64tab[];

  String  m_sFilename;    //The filename you want to send
  String  m_sTitle;       //What it is to be known as when emailed
  char*    m_pszEncoded;   //The encoded representation of the file
  int      m_nEncodedSize; //size of the encoded string
};


////////////////// Forward declaration
class CSMTPConnection;


//Encapsulation of an SMTP message
class CSMTPMessage
{
public:
//Enums
	enum RECIPIENT_TYPE { TO, CC, BCC };

//Constructors / Destructors
  CSMTPMessage();
  ~CSMTPMessage();

//Recipient support
	int              GetNumberOfRecipients(RECIPIENT_TYPE RecipientType = TO) const;
	int              AddRecipient(CSMTPAddress& recipient, RECIPIENT_TYPE RecipientType = TO);
	void             RemoveRecipient(int nIndex, RECIPIENT_TYPE RecipientType = TO);
	CSMTPAddress     GetRecipient(int nIndex, RECIPIENT_TYPE RecipientType = TO) const;

//Attachment support
	int GetNumberOfAttachments() const;
	int AddAttachment(CSMTPAttachment* pAttachment);
	void RemoveAttachment(int nIndex);
	CSMTPAttachment* GetAttachment(int nIndex) const;

	//Misc methods
	virtual String  GetHeader() const;
	void    AddBody(const String& sBody);
	bool    AddMultipleRecipients(const String& sRecipients, RECIPIENT_TYPE RecipientType);

	void SetHTMLFormat( bool bHtml) {  bHtmlFormat = bHtml;}
	bool IsHTML() { return bHtmlFormat;}
	                          
	//Data Members
	CSMTPAddress m_From;
	String      m_sSubject;
	String      m_sXMailer;
	CSMTPAddress m_ReplyTo;

protected:
  void FixSingleDot(String& sBody);

	String m_sBody;
	vector<CSMTPAddress> m_ToRecipients;
	vector<CSMTPAddress> m_CCRecipients;
	vector<CSMTPAddress> m_BCCRecipients;
	vector<CSMTPAttachment*> m_Attachments;

	bool bHtmlFormat;

  friend class CSMTPConnection;
};


//The main class which encapsulates the SMTP connection
class CSMTPConnection
{
public:
//Constructors / Destructors
  CSMTPConnection();
  ~CSMTPConnection();

//Methods
  bool Connect(const char* , int nPort=25);
  bool Disconnect();
  String GetLastCommandResponse() const { return m_sLastCommandResponse; };
  int     GetLastCommandResponseCode() const { return m_nLastCommandResponseCode; };
  long GetTimeout() const { return m_dwTimeout; };
  void    SetTimeout(long dwTimeout) { m_dwTimeout = dwTimeout; };
	bool    SendMessage(CSMTPMessage& Message);

protected:
  bool SendRCPTForRecipient(CSMTPAddress& recipient);
	virtual bool ReadCommandResponse(int nExpectedCode);
  virtual bool ReadResponse(char* pszBuffer, int nInitialBufSize, char* pszTerminator, 
                            int nExpectedCode, char** ppszOverFlowBuffer, int nGrowBy=4096);

  CSMTPSocket m_SMTP;
  bool m_bConnected;
  String     m_sLastCommandResponse;
	long m_dwTimeout;
  int         m_nLastCommandResponseCode;
};


#endif //__SMTP_H__

