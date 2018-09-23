 ///
 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 20:37:05
 ///
 
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>

namespace wd
{
typedef std::function<void()> Task;
class TaskQueue
{
public:
	TaskQueue(size_t queSize)
	:_queSize(queSize)
	,_mutex()
	,_notFull(_mutex)
	,_notEmpty(_mutex)
	,_flag(true)
	{}
	void push(Task &&task);//把任务放入队列
	Task pop();
	bool empty() const
	{return _que.size()==0;}
	bool full() const
	{return _que.size()==_queSize;}
	void wakeup()
	{
		_flag=false;
		_notEmpty.notifyAll();//唤醒所有等待的线程
	}
private:
	 size_t			_queSize;
	 std::queue<Task> _que;
	 MutexLock		_mutex;
	 Condition		_notFull;
	 Condition		_notEmpty;//定义了两个条件变量
	 bool			_flag;
};
}
#endif
