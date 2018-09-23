 ///
 /// @file    Socket.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 16:31:15
 ///
 
#include "Socket.h"
#inlcude "InetAddress.h"
#include "SocketUtil.h"

namespace wd
{
Socket::Socket(int sockfd)
:_sockfd(sockfd)
{}
Socket::Socket()
:_sockfd(createSocketFd())//构造函数要调用函数createSocketFd()创建一个套接字
{}
Socket::~Socket()
{
	::close(_sockfd);
}
void Socket::nonblock()//套接字复用设置
{
	setNonblock(_sockfd);
}
//执行shutdown(),如果把第二个参数设置成SHUT_WR,其实就是请求关闭端进入FIN_WAIT2
//文件描述符并不会立马失效，对端依然能发数据，请求端依然能接收数据。
void Socket::shutdownWrite()
{
	if(::shutdown(_sockfd,SHUT_WR)==-1)
	{
		perror("shotdown write error!");
	}
}
//函数getsockname()和getpeername()都是对已经建立连接的socket连接的描述符进行读写的。
//getsockname:可以获得一个与socket相关的地址，服务器端可以通过它得到相关客户端地址，而客户端
//也可以得到当前已连接成功的socket的IP和端口
InetAddress Socket::getLocalAddr(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(sockaddr_in);
	if(::getsockname(sockfd,(struct sockaddr*)&addr,&len)==-1)
	{
		perror("getsockname error");
	}
	return InetAddress(addr);
}
//获取客户端的IP和端口
InetAddress Socket::getPeerAddr(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(sockaddr_in);
	if(::getpeername(sockfd,(struct sockaddr *)&addr)==-1)
	{
		perror("getpeername error");
	}
	return Inetaddress(addr);
}
}

