 ///
 /// @file    TcpConnection.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 17:54:01
 ///
 
#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace wd
{
class Acceptor
{
public:
	Acceptor(int listenfd,const InetAddress &addr);
	void ready();
	int accept();
	int fd() const
	{return _listenSock.fd();}
private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();
private:
	Socket _listenSock;//为了拿到文件描述符，通过调用_listenSock.fd()拿到文件描述符，这里
	InetAddress _addr;//需要多次用到sfd 
};
}
#endif
