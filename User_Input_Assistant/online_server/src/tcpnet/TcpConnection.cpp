 ///
 /// @file    TcpConnection.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 14:16:36
 ///
 
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>

namespace wd
{
TcpConnection::TcpConnection(int sockfd,EpollPoller *loop)
:_sockfd(sockfd)
,_sockIO(sockfd)
,_localAddr(wd::Socket::getLocalAddr(sockfd))
,_peerAddr(wd::Socket::getPeerAddr(sockfd))
,_isShutdownWrite(false)
,_loop(loop)
{
	_sockfd.nonblock();//文件描述符复用
}
TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite)
	{
		_isShutdownWrite=true;
		shutdown();//关闭文件描述符
	}
}
//接收文件内容
std::string TcpConnection::receive()
{
	char buf[65536];
	memset(buf,0,sizeof(buf));
	size_t ret=_sockIO.readline(buf,sizeof(buf));//读取内容
	if(ret==0)
	{
		return std::string();
	}
	else
		return std::string(buf);
}
//发送文件内容
void TcpConnection::send(const std::string &msg)
{
	size_t len=msg.length();//获得要发送消息的大小
	_sockIO.writen((const char*)&len,sizeof(int));//先发送文件大小
	_sockIO.writen(msg.c_str(),msg.size());//发文件内容
}
//停止写
void TcpConnection::shutdown()
{
	if(_!isShutdownWrite)
	{
		_sockfd.shutdownWrite();
	}
	_isShutdownWrite=true;
}
//返回服务器端和本地的IP地址和端口号
std::string TcpConnection::toString()
{
	char str[100];
	snprintf(str,sizeof(str),"%s:%d -> %s:%d",
				_localAddr.ip().c_str(),
				_localAddr.port(),
				_peerAddr.ip().c_str(),
				_peerAddr.port());
	return std::string(str);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCb=cb;
}
void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCb=cb;
}
void TcpConnection::setCloseCallback(TcopConnctionCallback cb)
{
	_onCloseCb=cb;
}
void TcpConnection::handleConnectionCallback()
{
	if(_onConnection)
		_onConnectionCb(shared_from_this());
}
void TcpConnection::handleMessageCallback()
{
	if(_onMessageCb)
		_onConnectionCb(shared_from_this());
}
void TcpConnection::handleCloseCallback()
{
	if(_onCloseCb)
		_onCloseCb(shared_from_this());
}

void TcpConnection::sendInLoop(const std::string &msg)
{
	_loop->runInLoop(std::bind(&TcpConnecton::send,this,msg));
}
}
