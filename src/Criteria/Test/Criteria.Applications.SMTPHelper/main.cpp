#include "smtp.h"

int main()
{
  //Test the multiple recipients code
  
  /*
  CSMTPMessage testm;
  testm.AddMultipleRecipients(_T("   OK1 <  admin@mfarina.it  >  , My Boss <admin@mfarina.it>   ; Joe <admin@mfarina.it>"), CSMTPMessage::TO);
  testm.AddMultipleRecipients(_T("PJ Naughter <admin@mfarina.it>  ,Joe <admin@mfarina.it>"), CSMTPMessage::CC);
  testm.AddMultipleRecipients(_T("PJ Naughter <  admin@mfarina.it  >  , My Boss <admin@mfarina.it>   ; Joe <admin@mfarina.it>"), CSMTPMessage::BCC);
  */

  //Create the SMTP connection
  CSMTPConnection smtp;

  //Connect to the server
  if (!smtp.Connect("mail.proandpro.it"))
  {
    //CString sResponse = smtp.GetLastCommandResponse();
    return false;
  }

  //Create a test message
  CSMTPMessage m;
  CSMTPAddress From("Consulting Web-Supporto Tecninco", "m.farina@proandpro.it"); //Change these values to your settings
  m.m_From = From;

  CSMTPAddress To("Maurizio Farina", "m.farina@proandpro.it");   //Change these values to your settings
  m.AddRecipient(To, CSMTPMessage::TO);

  
  /*
  CSMTPAddress BCC(_T("PJ Naughter"), _T("g.celentano@proandpro.it"));  //Change these values to your settings
  m.AddRecipient(BCC, CSMTPMessage::BCC);
*/
  m.m_sSubject = "Un saluto per Raimondo";
  m.AddBody("<html><body>Gentile utente, <br>stiamo sperimentando un nuovo servizio di notifica vocale su mail. In allegato il file da ascoltare.Saluti.</body></html>");

  /*
	//Testing Reply To support
	m.m_ReplyTo = CSMTPAddress(_T("Another PJ"), _T("admin@mfarina.it"));
*/
	//Testing attachment support
	CSMTPAttachment attachment;
	String sFile = "C:\\mySoftware\\Scenario\\ExecutionEnvironment\\database\\DM\\external\\CCR_102.pdf";
	String sName = "preventivo.pdf";
	attachment.Attach(sFile);
	m.AddAttachment(&attachment);
  


  //Sent the message
  if (!smtp.SendMessage(m))
  {
    String sResponse = smtp.GetLastCommandResponse();
    return false;
  }

  //Disconnect from the server
  smtp.Disconnect();

	return false;
}