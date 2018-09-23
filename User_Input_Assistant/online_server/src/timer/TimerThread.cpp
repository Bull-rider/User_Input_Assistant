 ///
 /// @file    TimerThread.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-03 23:11:25
 ///
 
#include "TimerThread.h"
using namespace wd;
TimerThread::TimerThread(int initialTime,int intervalTime,TimerCallback &&cb )
:_timer(initialTime,intervalTime,std::move(cb))
,_subThread(std::bind(&Timer::start,&_timer))
,_isStarted(false)
{}

void TimerThread::start()
{
	_subThread.start();
	_isStarted=true;
}

void TimerThread::stop()
{
	if(_isStarted)
	{
		_timer.stop();
		_subThread.join();
		_isStarted=false;
	}
}

TimerThread::~TimerThread()
{
	if(_isStarted)
		stop();
}
