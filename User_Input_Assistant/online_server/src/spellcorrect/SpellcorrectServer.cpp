///
/// @file    SpellcorrectServer.cpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2018-09-06 20:07:45
///
#include "SpellCorrectServer.h"
#include "Singleton.h"
#include "Mydict.h"
#include "MyTask.h"
#include "CacheManager.h"

using std::string;
using namespace wd;
using std::stoi;

#include <iostream>
using std::endl;
using std::cout;

#include <sstream>
#include <functional>
using std::bind;
using namespace std::placeholders;

SpellCorrectServer::SpellCorrectServer()
:_tcpserver(Singleton<Configuration>::getInstance()->getMap()["ip"],
			stoi(Singleton<Configuration>::getInstance()->getMap()["port"]))
		, _threadpool(stoi(Singleton<Configuration>::getInstance()->getMap()["thread_num"]),
				stoi(Singleton<Configuration>::getInstance()->getMap()["task_size"]))
		,_timer(stoi(Singleton<Configuration>::getInstance()->getMap()["init_time"]),
				stoi(Singleton<Configuration>::getInstance()->getMap()["inval_time"]),
				std::bind(&CacheManager::periodicUpdateCaches))
{}

void SpellCorrectServer::start() {
	_threadpool.start();
	_timer.start(); //定时更新cache
	_tcpserver.setConnectionCallback(
			bind(&SpellCorrectServer::onConnection, this, _1));
	_tcpserver.setMessageCallback(
			bind(&SpellCorrectServer::onMessage, this, _1));
	_tcpserver.setCloseCallback(
			bind(&SpellCorrectServer::onClose, this, _1));
	_tcpserver.start();
	return;
}

void SpellCorrectServer::onConnection(TcpConnectionPtr conn) {
	cout<<endl;
	cout<<"\t"<<conn->toString()<<" connected."<<endl;
	string connect_string(" welcome to SpellCorrect_Server!\n");
	conn->send(connect_string);
	return;
}

void SpellCorrectServer::onMessage(TcpConnectionPtr conn) {
	string msg = conn->receive();//从客户端接收数据
	cout << "receive: "<<msg << endl;
	MyTask task(msg, conn);//传到队列中，在索引中查找和数据相似的结果，
	_threadpool.addTask(std::bind(&MyTask::execute, task));
	return;
}
//关闭
void SpellCorrectServer::onClose(TcpConnectionPtr conn) {
	cout <<endl<< "\t"<<conn->toString() << " closed!" << endl;
	return;
}
