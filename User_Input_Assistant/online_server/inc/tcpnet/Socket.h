 ///
 /// @file    Socket.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 16:20:26
 ///
 
#ifndef __WD_SOCKET_H
#define __WD_SOCKET_H

#include "Noncopyable.h"

namespace wd
{
class InetAddress;
class Socket:public Noncopyable
{
public:
	Socket(int sockfd);//自定义的构造函数
	Socket();//默认构造函数，我们要重写默认构造函数
	~Socket();
	void shutdownWrite();//关闭写端，不能在发送数据，但依然可以接收数据
	int fd() const
	{return _sockfd;}
	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);
private:
	int _sockfd;
};
}
#endif
