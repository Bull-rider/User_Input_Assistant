 ///
 /// @file    MutexLock.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 19:16:54
 ///
 //定义一个锁的类，锁的操作
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>
namespace wd
{
class MutexLock:public Noncopyable
{
public:
	MutexLock()
	{
		pthread_mutex_init(&_mutex,NULL);
	}
	~MutexLock()
	{
		pthread_mutex_destroy(&_mutex);
	}
	void lock()
	{
		pthread_mutex_lock(&_mutex);
	}
	void unlock()
	{
		pthread_mutex_unlock(&_mutex);
	}
	pthread_mutex_t *getMutexLockPtr()
	{
		return &_mutex;
	}
private:
	pthread_mutex_t _mutex;
};
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock &mutex)
	:_mutex(mutex)
	{
		_mutex.lock();
	}
	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLock &_mutex;
};
}
#endif
