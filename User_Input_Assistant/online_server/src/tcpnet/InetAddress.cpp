 ///
 /// @file    InetAddress.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 15:56:18
 ///
 
#include "InetAddress.h"
using namespace wd;

InetAddress::InetAddress(short port)
{
	::memset(&_addr,0,sizeof(_addr));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);
	_addr.sin_addr.s_addr=INADDR_ANY;
}

InetAddress::InetAddress(const char *pIp,short port)
{
	::memset(&_addr,0,sizeof(_addr));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);
	_addr.sin_addr.s_addr=inet_addr(pIp);
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
:_addr(addr)
{}

const struct sockaddr_in *getSockaddrrPtr() const
{
	return _addr;
}

std::string InetAddress:: ip() const
{
	return std::string (inet_ntoa(_addr.sin_addr));//网络地址转主机地址
}
unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);
}
