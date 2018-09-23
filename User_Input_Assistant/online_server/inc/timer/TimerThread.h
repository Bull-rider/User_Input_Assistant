 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 23:06:24
 ///
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__
#include "Timer.h"
#include "Thread.h"
#include <functional>
namespace wd
{
class TimerThread
{
public:
	using TimerCallback=std::function<void()>;
	TimerThread(int,int,TimerCallback &&cb);
	void start();
	void stop();

	~TimerThread();
private:
	Timer _timer;
	Thread _subThread;
	bool _isStarted;
};
}
#endif
