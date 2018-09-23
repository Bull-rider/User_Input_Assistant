 ///
 /// @file    EpollPoller.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 20:25:21
 ///
 
#ifndef __WD_EPOLLPOLLER_H__
#define __WD_EPOLLPOLLER_H__

#include "Noncopyable.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>
namespace wd
{
class Acceptor;
class EpollPoller:Noncopyable
{
public:
	typedef TcpConnection::TcpConnectionCallback EpollCallback;
	typedef std::function<void()> Functor;
	EpollPoller(Acceptor &acceptor);//把客户端的文件描述符添加到epoll兴趣列表中
	~EpollPoller();
	void loop();
	void unloop();
	void runInLoop(const Functor &&cb);
	void doPendingFunctors();
	void wakeup();

	void setConnectionCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);
private:
	Acceptor &_acceptor;
	int _epollfd;
	int _eventfd;
	int _listenfd;
	bool isLooping;
	MutexLock _mutex;
	std::vector<Functor> _pendingFunctors;
	//定义一个vector类型的容器存放epoll列表中的成员
	typedef std::vector<struct epoll_event> EventList;
	EventList _eventsList;
	typedef std::map<int,TcpConnectionPtr> ConnectionMap;
	ConnectionMap _connMap;

	EpollCallback _onConnectionCb;
	EpollCallback _onMessageCb;
	EpollCallback _onCloseCb;
};
}
#endif

