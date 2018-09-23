 ///
 /// @file    Timer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 22:01:06
 ///
 //Timer这个类是干什么的，为子线程执行任务计时的
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__

#include <functional>

namespace wd
{
class Timer
{
public:
	using TimerCallback=std::function<void()>;
	Timer(int initialTime,int intervalTime,TimerCallback &&cb);
	~Timer();
	void start();
	void stop();
private:
	int createTimerFd();
	void setTimerfd(int initialTime,int intervalTime);
	void handleRead();
private:
	int _fd;
	int _initialTime;
	int _intervalTime;
	TimerCallback _cb;
	bool _isStarted;
};
}
#endif

