 ///
 /// @file    Condition.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 19:39:51
 ///
 //条件变量中需要一把锁，我们要传进来一把锁，所以就定义一个锁的类
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"
#include "MutexLock.h"

#include <pthread.h>
namespace wd
{
class Condition:Noncopyable
{
public:
	Condition(MutexLock &mutex)
	:_mutex(mutex)
	{
		pthread_cond_init(&_cond,NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&_cond);
	}
	void wait()
	{
		pthread_cond_wait(&_cond,_mutex.getMutexLockPtr());
	}
	void notify()
	{
		pthread_cond_signal(&_cond);
	}
	void notifyAll()
	{
		pthread_cond_broadcast(&_cond);
	}
private:
	pthread_cond_t _cond;
	MutexLock &_mutex;//这里引用一个类，就是为了拿到MutexLock.h中创建的锁
};
}
#endif
