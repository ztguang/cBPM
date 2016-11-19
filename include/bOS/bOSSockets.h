#ifndef INCLUDED_SOCKETS_H
#define INCLUDED_SOCKETS_H

//TO_BE_EXPORTED

#include "bOS.h"

bool BOS_API socketsInit();
void BOS_API socketsEnd();

class BOS_API SocketWrapper
{
	class AcceptedSocket
	{
	private:
		AcceptedSocket(socket_type s, sockaddr_in a);
		AcceptedSocket(const AcceptedSocket &a);
		AcceptedSocket& operator=(const AcceptedSocket &);

		socket_type sock_;
		sockaddr_in addr_;

		friend class SocketWrapper;
	};

public:

	enum sockstate_type
	{
		CLOSED,
		LISTENING,
		ACCEPTED,
		CONNECTED
	};

	SocketWrapper();
	SocketWrapper(const AcceptedSocket &as);
	~SocketWrapper();
	
	//server methods

	// binds and listens on a given port number
	void listen(int port, int backlog = 100);
	AcceptedSocket accept();


	//client methods
	void connect(const char *address, int port);

	// server-client methods
	sockstate_type state() const { return sockstate_; }
	const char * address() const;
	int port() const;

	void write(const void *buf, size_t len);
	size_t read(void *buf, size_t len);

	void close();

private:

	SocketWrapper(const SocketWrapper&);
	SocketWrapper& operator=(const SocketWrapper&);

	socket_type sock_;
	sockaddr_in sockaddress_;
	sockstate_type sockstate_;
};

#endif
