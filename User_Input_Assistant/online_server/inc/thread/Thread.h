 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 19:56:57
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
using std::function;

namespace wd
{
extern __thread int thread_index;//当指定为extern时，可以在整个程序中访问
class Thread:Noncopyable
{
	using ThreadCallback=function<void()>;
public:
	Thread(ThreadCallback &&cb,int);
	Thread(ThreadCallback &&cb);
	~Thread();

	void start();
	void join();
	bool isRunning()const
	{return _isRunning;}
private:
	static void *threadFunc(void *);
private:
	pthread_t _pthread;//线程Id
	bool _isRunning;//线程状态
	ThreadCallback _cb;
	int _index;
};
}
