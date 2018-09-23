 ///
 /// @file    TaskQueue.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 20:50:57
 ///
 
#include "TaskQueue.h"
using namespace wd;
void TaskQueue::push(Task &&task)
{
	MutexLockGuard autoLock(_mutex);//生产者生产时如果满了，就被阻塞，等待；
	while(full())					//如果未满，放进去，就唤醒一个消费者，
	{
		_notFull.wait();
	}
	_que.push(std::move(task));
	_notEmpty.notify();//唤醒消费者线程
}
Task TaskQueue::pop()
{
	MutexLockGuard autoLock(_mutex);//消费者取任务时，如果队列空,就阻塞，等待
	while(_flag&&empty())			//如果队列不空，就取出任务，并唤醒一个生产者
	{
		_notEmpty.wait();
	}
	if(_flag)
	{
		Task task=_que.front();
		_que.pop();
		_notFull.notify();//唤醒生产者线程
		return task;
	}else
		return NULL;
}
