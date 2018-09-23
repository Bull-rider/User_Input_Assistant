 ///
 /// @file    InetAddress.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 15:48:46
 ///
#ifndef _WD_INETADDRESS_H
#define _WD_INETADDRESS_H

#include <netinet/in.h>
#include <string>

namespace wd
{
class InetAddress
{
public:
	InetAddress(short port);//当只传一个端口号时
	InetAddress(const char *pIp,short port);//传IP和端口号时
	InetAddress(const struct sockaddr_in &addr);//传一个包含IP和端口号的结构体时
	cosnt struct sockaddr_in *getSockAddrPtr()const;
	std::string ip() const;
	unsigned short port() const;
private:
	struct sockaddr_in _addr;
};
}
#endif
