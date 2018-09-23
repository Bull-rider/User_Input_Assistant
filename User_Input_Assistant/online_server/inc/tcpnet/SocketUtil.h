 ///
 /// @file    SocketUtil.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 17:35:44
 ///
#ifndef __WD_SOCKETUTIL_H__
#define __WD_SOCKETUTIL_H__

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>

namespace wd
{
inline int createSocketFd()//创建套接字
{
	int fd=::socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket create error");
	}
	return fd;
}
inline void setNonblock(int fd)//套接字复用
{
	int flags=::fcntl(fd,F_GETFL,0);
	flags |=O_NONBLOCK;
	::fcntl(fd,F_SETFL,flags);
}
inline int createEpollFd()
{
	int epfd=::eoll_create1(0);
	if(-1==efd)
	{
		perror("epoll_create error");
		exit(EXIT_FAILURE);
	}
	return epfd;
}

inline int createEventFd()
{
	int evtfd=::eventfd(0,EFD_NONBLACK|EFD_CLOEXEC);//eventfd()用于进程间通信
	if(-1==evtfd)
	{
		perror("eventfd error");
		exit(EXIT_FAILURE);
	}
	return evtfd;
}
//添加新的客户端请求，文件描述符到epoll兴趣队列中
inline void addEpollFdRead(int efd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	int ret=epoll_ctl(efd,EPOLL_CTL_ADD,fd,&ev);//将fd添加到epoll兴趣列表中
	if(-1==ret)
	{
		perror("epoll_ctl error");
		exit(EXIT_FAILURE);
	}
}
//从epoll兴趣列表中删除一个文件描述符
inline void delEpollReadFd(int efd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	int ret=epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev);
	if(-1==ret)
	{
		perror("epoll_ctl error");
		exit(EXIT_FAILURE);
	}
}
//预览数据
inline size_t recvPeek(int sockfd,void *buf,size_t len)
{
	int nread;
	do
	{
		nread=::recv(sockfd,buf,len,MSG_PEEK);
	}while(nread==-1&&errno==EINTR);
	return nread;
}

//通过预览数据判断conn是否关闭
inline bool isConnectionClosed(int sockfd)
{
	char buf[1024];
	int nread=recvPeek(sockfd,buf,sizeof(buf));
	if(-1==nread)
	{
		perror("recvPeek:");
		return true;
	}
	return (0==nread);
}
}
#endif

