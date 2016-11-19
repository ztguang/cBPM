#include "bOSSockets.h"
#include "bOSSocketException.h"
using namespace bOS::Net;

SocketWrapper::AcceptedSocket::AcceptedSocket(socket_type s, sockaddr_in a)
{
	sock_ = s;
	addr_=a;
}

SocketWrapper::AcceptedSocket::AcceptedSocket(const AcceptedSocket &a)
{
	sock_ = a.sock_;
	addr_ = a.addr_;
}

SocketWrapper::SocketWrapper()
{
	sockstate_ = CLOSED;
}

SocketWrapper::SocketWrapper(const SocketWrapper::AcceptedSocket &as)
{
	sock_ = as.sock_;
	sockaddress_=as.addr_;
	sockstate_=ACCEPTED;
}

SocketWrapper::~SocketWrapper()
{
	if (sockstate_ != CLOSED)
	{
/*
#ifdef WIN32
		closesocket(sock_);
#else
*/
		::close(sock_);
//#endif
	}
}

void SocketWrapper::listen(int port, int backlog)
{
	if (sockstate_ != CLOSED)
	{
		throw SocketLogicException("socket not in CLOSED state");
	}

	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == INVALID_SOCKET)
	{
		throw SocketRunTimeException("socket failed");
	}

	sockaddr_in local;

	memset(&local, 0, sizeof(local));

	local.sin_family = AF_INET;
	local.sin_port = htons((u_short)port);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	if (::bind(sock_, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
	{
		throw SocketRunTimeException("bind failed");
	}

	if (::listen(sock_, backlog) == SOCKET_ERROR)
	{
		throw SocketRunTimeException("listen failed");
	}

	memset(&sockaddress_, 0, sizeof(sockaddress_));
	sockstate_ = LISTENING;
}

SocketWrapper::AcceptedSocket SocketWrapper::accept()
{
	if (sockstate_ != LISTENING)
		throw SocketLogicException("socket not listening");

	sockaddr_in from;
	socklen_t len = sizeof(from);

	memset(&from, 0, len);

	socket_type newsocket = ::accept(sock_, (sockaddr*)&from, &len);
	if (newsocket == INVALID_SOCKET)
	{
		throw SocketRunTimeException("accept failed");
	}

	return AcceptedSocket(newsocket, from);
}

void SocketWrapper::connect(const char *address, int port)
{
	if (sockstate_ != CLOSED)
	{
		throw SocketLogicException("socket not in CLOSED state");
	}

	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == INVALID_SOCKET)
	{
		throw SocketRunTimeException("socket failed");
	}

	hostent *hp;

	unsigned long addr = inet_addr(address);
	if (addr != INADDR_NONE)
	{
		hp = gethostbyaddr((const char*)&addr, 4, AF_INET);
	}
	else
	{
		hp = gethostbyname(address);
	}

	if (hp == NULL)
	{
		throw SocketRunTimeException("cannot resolve address");
	}

	if (hp->h_addrtype != AF_INET)
	{
		throw SocketRunTimeException
			("address resolved with TCP incompatible type");
	}

	memset(&sockaddress_, 0, sizeof(sockaddress_));
	memcpy(&(sockaddress_.sin_addr), hp->h_addr_list[0], hp->h_length);
	sockaddress_.sin_family = AF_INET;
	sockaddress_.sin_port = htons((u_short)port);

	if (::connect(sock_, (sockaddr*)&sockaddress_, sizeof(sockaddress_)) == SOCKET_ERROR)
	{
		throw SocketRunTimeException("connect failed");
	}

	sockstate_ = CONNECTED;
}

const char* SocketWrapper::address() const
{
	if (sockstate_ != CONNECTED && sockstate_ != ACCEPTED)
	{
		throw SocketLogicException("socket not connected");
	}

	return inet_ntoa(sockaddress_.sin_addr);
}

int SocketWrapper::port() const
{
	if (sockstate_ != CONNECTED && sockstate_ != ACCEPTED)
	{
		throw SocketLogicException("socket not connected");
	}

	return ntohs(sockaddress_.sin_port);
}

void SocketWrapper::write(const void *buf, size_t len)
{
	if (sockstate_ != CONNECTED && sockstate_ != ACCEPTED)
	{
		throw SocketLogicException("socket not connected");
	}

	int written;
	while (len != 0)
	{
		if ((written = send(sock_, (const char*)buf, (int)len, 0)) == SOCKET_ERROR)
		{
			throw SocketRunTimeException("write failed");
		}

		len -= written;
		buf = (const char*)buf + written;
	}
}

size_t SocketWrapper::read(void *buf, size_t len)
{
	if (sockstate_ != CONNECTED && sockstate_ != ACCEPTED)
	{
		cout << "socket not connected" << endl;
		throw SocketLogicException("socket not connected");
	}

	cout << "SocketWrapper::read reading ........." << endl;
	int readn = recv(sock_, (char*)buf, (int)len, 0);
	if (readn == SOCKET_ERROR)
	{
		cout << "read failed" << endl;
		throw SocketRunTimeException("read failed");
	}

	return (size_t)readn;
}

void SocketWrapper::close()
{
	if (sockstate_ != CLOSED)
	{
/*
#ifdef WIN32
		if (closesocket(sock_) == SOCKET_ERROR)
			throw SocketRunTimeException("close failed");
#else
*/
		if (::close(sock_))
			throw SocketRunTimeException("close failed");
//#endif
		sockstate_ = CLOSED;
	}
}

bool socketsInit()
{
/*
#ifdef WIN32

	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 0), &wsadata) == 0)
		return true;
	else
		return false;
#else
*/
	return true;
//#endif
}

void socketsEnd()
{

//#ifdef WIN32
//	WSACleanup();
//#endif

}
