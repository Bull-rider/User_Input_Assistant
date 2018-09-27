 ///
 /// @file    MyTask.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 21:13:27
 ///
 
#ifndef _MYTASK_H
#define _MYTASK_H

#include "MyResult.h"
#include "TcpConnection.h"

#include <string>
#include <queue>
#include <vector>
#include <set>

class MyCompare//对结果进行处理,MyResult类中存放的是每一个候选子的属性
{
public:
	bool operator()(const MyResult &lhs,const MyResult &rhs)
	{
		if(lhs._iDist>rhs._iDist)
		{
			return true;
		}
		else if(lhs._iDist==rhs._iDist&&lhs._iFreq<rhs.iFreq)
		{
			return true;
		}
		else if(lhs._iDist==rhs._iDist&&lhs._iFreq==rhs._iFreq&&lhs._word>rhs._word)
		{
			return true;
		}
		else
			return false;
	}
};

class Cache;//Cache缓存
class MyTask
{
	public:
	MyTask(const std::string &queryWord,const wd::TcpConnectionPtr &conn);
	int min();
	void execute();
private:
	std::string _queryWord;//客户端输入的数据
	wd::TcpConnectionPtr _conn;
	std::priority_queue<MyResult,std::vector<MyResult>.MyCompare> _resultQue;
	bool *_bit_array;

	void queryIndexTable();//索引表

	void statistic(std::set<int> &iset);

	int distance(const std::string &rhs);//最小编辑距离

	void response(Cache &cache);

	std::vector<std::string> getChar(const std::string &word);
};
#endif
