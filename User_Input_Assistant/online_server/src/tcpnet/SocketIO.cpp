 ///
 /// @file    SocketIO.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 17:07:17
 ///
 
#include "SocketIO.h"
#include "SocketUtil.h"

namespace wd
{
SocketIO::SocketIO(int sockfd)
:_sockfd(sockfd)
{}
//buf的大小不确定，可能比数据小，故循环读取
size_t SocketIO::readn(char *buf,size_t count)
{
	size_t nleft=count;
	char *pbuf=buf;
	while(nleft>0)
	{
		int nread=::read(_sockfd,pbuf,nleft);
		if(-1==nread)
		{
			if(errno==EINTR)
				continue;
			return EXIT_FAILURE;
		}
		else if(nread==0)
		{
			break;
		}
		pbuf+=nread;//指针一项读取的最后一个字符的下一个位置
		nleft-=nread;//每次读取后剩余的
	}
	return (count-nleft);
}
size_t SocketIO::writen(const char *buf,size_t count)
{
	size_t nleft=count;
	const char *pbuf=buf;
	while(nleft>0)
	{
		int nwrite=::write(_sockfd,buf,nleft);
		if(nwrite==-1)
		{
			if(errno==EINTR)
			{
				continue;
			}
			return EXIT_FAILURE;
		}
		nleft-=nwrite;
		pbuf+=nwrite;
	}
	return (count-nleft);
}
size_t SocketIO::recv_peek(char *buf,size_t count)
{
	int nread;
	do
	{
		nread=::recv(_sockfd,buf,count,MSG_PEEK);
	}while(nread==-1&&errno==EINTR);
	return nread;
}

size_t SocketIO::readline(char *buf,size_t maxlen)
{
	size_t nleft=maxlen-1;
	char *pbuf=buf;
	size_t total=0;
	while(nleft>0)
	{
		int nread=recv_peek(pbuf,nleft);
		if(nread<=0)
			return nread;
		for(size_t idx=0;idx!=nread;++idx)
		{
			if(pbuf[idx]=='\n')
			{
				size_t nsize=idx+1;
				if(readn(pbuf,nsize)!=nsize)
					return EXIT_FAILURE;
				pbuf+=nsize;
				total+=nsize;
				*pbuf=0;
				return total;
			}
		}
		if(readn(pbuf,nread)!=nread)
			return EXIT_FAILURE;
		pbuf+=nread;
		nleft-=nread;
		total+=nread;
	}
	*pbuf=0;
	return maxlen-1;
}
}
