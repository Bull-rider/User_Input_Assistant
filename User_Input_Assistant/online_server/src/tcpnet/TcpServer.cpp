 ///
 /// @file    TcpServer.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 15:31:01
 ///
 
#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketUtil.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
TcpServer::TcpServer(const string &ip,unsigned short port)
:_acceeptor(createSocketFd(),InetAddress(ip.c_str(),port))
:_poller(_acceptor)
{}

void TcpServer::start()
{
	_acceptor.ready();
	_poller.setConnectionCallback(_TcpServerCallback);
	_poller.setMessageCallback(_messageCallback);
	_poller.setloseCallback(_closeCallback);
	_poller.loop();
}

void TcpServer::stop()
{
	_poller.unloop();
}
void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	_connectionCallback=cb;
}
void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	_messageCallback=cb;
}
void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	_closeCallback=cb;
}
}
