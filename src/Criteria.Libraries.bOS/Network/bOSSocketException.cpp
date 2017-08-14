#include "bOSSocketException.h"
using namespace bOS::Net;

using namespace std;

SocketRunTimeException::SocketRunTimeException(const string &what)
: runtime_error(what)
{
       //ztg alter
/*
#ifdef WIN32
	errnum_ = ::WSAGetLastError();
#else
*/
	errnum_ = errno;
//#endif
}

const char * SocketRunTimeException::what() const throw()
{
	ostringstream ss;
	ss << runtime_error::what();
	ss << " error number: " << errnum_;
	msg_ = ss.str();
	return msg_.c_str();
}
