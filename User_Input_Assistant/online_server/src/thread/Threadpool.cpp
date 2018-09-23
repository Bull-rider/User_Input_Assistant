 ///
 /// @file    Threadpool.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 21:32:41
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace wd;

void Threadpool::start()
{
	for(size_t idx=0;idx<_threadNum;++idx)
	{
		share_ptr<Thread> pThread(new Thread(std::bind(&Threadpool::threadFunc,this),idx));
		_threads.push_back(std::move(pThread));
	}
	for(auto &pThread:_threads)
	{
		pThread->start();
	}
}
void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_taskQue.empty())
		{
			::sleep(1);
			cout<<">>> Threadpool sleep 1 s"<<endl;
		}
		_isExit=true;
		cout<<">>> Threadpool->stop: _isExit="<<_isExit<<endl;
		_taskQue.wakeup();
		for(auto &pthread:_threads)
		{
			pthread->join();
		}
	}
	_threads.clear();
}
Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

//向任务队列中添加任务
void Threadpool::addTask(Task &&task)
{
	_taskQue.push(std::move(task));
}
//从任务队列中取任务
Task Threadpool::getTask()
{
	return _taskQue.pop();
}
//子线程要做的事
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task=getTask();
		if(task)
		{
			task();
		}
	}
}
