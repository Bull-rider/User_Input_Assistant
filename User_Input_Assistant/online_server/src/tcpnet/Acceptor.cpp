 ///
 /// @file    Acceptor.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 19:10:08
 ///
 

#include "Acceptor.h"
#include "SocketUtil.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
Acceptor::Acceptor(int listenfd,const InetAddress &addr)
:_listenSock(listenfd)
,_addr(addr)
{}
//绑定和监听都在函数ready()中完成
void Acceptor::ready()
{
	setReuseAddr(true);
	setReusePort(true);
	bind();
	listen()
}
int Acceptor::accept()
{
	int peerfd=::accept(_listenSock.fd(),NULL,NULL);
	if(peerfd==-1)
	{
		perror("accept error");
	}
	return peerfd;
}

void Acceptor::setReuseAddr(bool flag)//地址复用
{
	int on=(flag?1:0);
	if(::setsockopt(_listenSock.fd(),SOL_SOCKET<SO_REUSEADDR,&on,static_cast<socklen_t
				>(sizeof(on)))==-1)
	{
		perror("setsockopt reuseaddr error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
}
//端口复用
void Acceptor::setRusePort(bool flag)
{
#ifndef SO_REUSEPORT
	int on=(falg?1:0);
	if(::setsockopt(_listenSock.fd(),SOL_SOCKET,SO_REUSEPORT,&on,
				static_cast<socklen_t>(sizeof(on)))==-1)
	{
		perror("setsockopt reuseport error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
#else
	if(flag)
	{
		fprintf(stderr,"SO_REUSEPORT is not supported!\n");
	}
#endif
}
//bind()函数
void Acceptor::bind()
{
	if(-1==::bind(_listenSock.fd(),(const struct sockaddr *)&_addr.getSockAddrPtr()
				,sizeof(InetAddress)))
	{
		perror("bind error");
		::close(_listenScok.fd());
		exit(EXIT_FAILURE);
	}
}
//监听listen()函数
void Acceptor::listen()
{
	if(-1==::listen(_listenSock.fd(),10))
	{
		perror("listen error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
}


}
