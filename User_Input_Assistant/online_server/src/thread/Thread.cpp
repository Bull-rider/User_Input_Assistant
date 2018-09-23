 ///
 /// @file    Thread.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 20:07:10
 ///
 
#include "Thread.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
__thread int thread_index=0;
Thread::Thread(ThreadCallback &&cb,int index)
:_pthid(0)
,_isRunning(false)
,_cb(std::move(cb))
,_index(index)
{}
Thread::Thread(ThreadCallback &&cb)
:_pthid(0)
,_isRunning(false)
,_cb(std::move(cb))
{}
//其实创建线程就是为了让线程做任务，所以创建线程时也要定义任务函数，
void Thread::start()
{
	pthread_create(&_pthid,NULL,threadFunc,this);
	_isRunning=true;
}
void *Thread::threadFunc(void *arg)
{
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread)
	{
		wd::thread_index=pthread->_index;
		pthread->_cb()
	}
	return NULL;
}
void Thread::join()
{
	pthread_join(_pthid,NULL);
	_isRunning=false;
}
Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_delete(_pthid);
		_isRunning=false;
	}
}
}
