 ///
 /// @file    SpellCorrectServer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 21:00:54
 ///
 
#ifndef _SPELLCORRECTSERVER_H
#define _SPELLCORRECTSERVER_H
#include "TcpConnection.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "TimerThread.h"
#include "Configuration.h"

#include <string>

class SpellCorrectServer
{
public:
	SpellCorrectServer();
	void start();

	void onConnection(wd::TcpConnectionPtr conn);

	void onMessage(wd::TcpConnectionPtr conn);

	void onClose(wd::TcpConnectionPtr conn)
private:
	wd::TcpServer _tcpserver;
	Configuration _conf;
	wd::Threadpool _threadpool;
	wd::TimerThread _timer;
};
#endif
