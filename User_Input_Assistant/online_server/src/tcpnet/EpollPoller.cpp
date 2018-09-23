 ///
 /// @file    EpollPoller.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 21:08:16
 ///
 
#include "EpollPoller.h"
#include "SocketUtil.h"
#include "Acceptor.h"
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
EpollPoller::EpollPoller(const Acceptor &acceptor)
:_acceptor(acceptor)
,_epollfd(createEpollFd())//createEpollFd()和createEventFd()在SocketUtil.h中实现
,_eventfd(createEventFd())
,_listenfd(_acceptor.fd())
,_isLooping(false)
,_eventList(1024)
{
	addEpollFdRead(_epollfd,_listenfd);//
	addEpollFdTead(_epollfd,_eventfd);
}
EpollPoller::~EpollPoller()//析构函数回收资源
{
	::close(_epollfd);
}
void EpollPoller::loop()
{
	_isLooping=true;
	while(_isLooping)
	{
		waitEpollfd();//执行epool_wait()
	}
}
void EpollPoller::unloop()
{
	if(_isLooping)
		_isLooping=false;
}
void EpollPoller::setConnectionCallback(EpollCallback cb)
{
	_onConnectionCb=cb;
}
void EpollPoller::setMessageCallback(EpollCallback cb)
{
	_onMessageCb=cb;
}
void EpollPoller::setCloseCallback(EpollCallback cb)
{
	_onClosed=cb;
}
//当我们初始化的存放的客户端的文件描述符的空间不足时，要重新申请
void EpollPoller::waitEpollfd()
{
	int nready;
	do
	{
		nready=::epoll_wait(_epollfd,&(*_eventsList.begin()),_eventsList.size(),5000);
	}while(nready==-1&&errno==EINTR);
	if(nready==-1)
	{
		perror("epoll_wait error\n");
		exit(EXIT_FAILURE);
	}
	else if(nready==0)
	{
		printf("epoll_wait timeout\n");
	}
	else//空间不足，要扩容
	{
		if(nready==static_cast<int>(_eventsList.size()))
		{
			_eventsList.resize(_eventsList.size()*2);//分配2倍的空间
		}
		//遍历每一个激活的文件描述符
		for(int idx=0;idx!=nready;++idx)
		{
			if(_eventsList[idx].data.fd==_listenfd)
			{
				if(_eventsList[idx].events&EPOLLIN)
				{
					handleConnection();
				}
			}
			else if(_eventsList[idx].data.fd==_eventfd)
			{
				handleRead();
				doPendingFunctors();
			}
			else
			{
				if(_evensList[idx].events&EPOLLIN)
				{
					handleMessage(_eventsList[idx].data.fd);
				}
			}
		}
	}
}
void EpollPoller::handleConnection()
{
	int peerfd=_acceptor.accept();
	addEpollFdRead(_epollfd,peerfd);
	
	TcpConnectionPtr conn(new TcpConnection(peerfd,this));
	conn->setConnectionCallback(_onConnectionCb);
	conn->setMessageCallback(_onMessageCb);
	conn->setCloseCallback(_onCloseCb);

	std::pair<ConnectionMap::iterator,bool> ret;
	ret=_connMap.insert(std::make_pair(peerfd,conn));
	assert(ret.second==true);
	(void)ret;
	conn->handleConnectionCallback();
}
void EpollPoller::handleMessage(int peerfd)
{
	bool isClose=isConnectionClosed(peerfd);
	ConnectionMap::iterator it=_connMap.find(peerfd);
	assert(it!=_connMap.end());
	if(isClosed)
	{
		it->second->handleCloseCallback();
		delEpollReadFd(_epollfd,peerfd);
		_connMap.erase(it);
	}
	else
	{
		it->second->handleMessageCallback();
	}
}

void EpollPoller::runInLoop(const Functor &&cb)
{
	{
		MutexLockGuard mlg(_mutex);
		_pendingFunctors.push_back(std::move(cb));//右值引用
	}
	wakeup();
}
void EpollPoller::doPendingFunctors()
{
	std::vector<Functor> tmp;
	{
		MutexLockGuard mlg(_mutex);
		tmp.swap(_pendingFunctors);
	}
	for(auto&functor:tmp)
	{
		functor();
	}
}
void EpollPoller::handleRead()
{
	uint64_t howmany;
	int ret=::read(_eventfd,&howmany,sizeof(howmany));
	if(ret!=sizeof(howmany))
	{
		perror("read error");
	}
}
void EpollPoller::wakeup()
{
	uint64_t one=1;
	int ret=::write(_eventfd,&one,sizeof(one));
	if(ret!=sizeof(one))
	{
		perror("write error");
	}
}

}
