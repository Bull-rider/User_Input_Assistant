 ///
 /// @file    SocketIO.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 16:56:50
 ///
 
#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__
#include <stdio.h>

namespace wd
{
class SocketIO
{
public:
	SocketIO(int sockfd);//这个文件描述符是accept()后得到的，用它进行文件内容的传递

	size_t readn(char *buf,size_t count);
	size_t writen(const char *buf,size_t count);
	size_t readline(char *buf,size_t max_len);

private:
	size_t recv_peek(char *buf,size_t count);
private:
	int _sockfd;
};

}
#endif
