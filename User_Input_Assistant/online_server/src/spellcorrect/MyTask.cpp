 ///
 /// @file    MyTask.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 21:56:53
 ///
 
#include "MyTask.h"
#include "CacheManager.h"
#include "Cache.h"
#include "Singleton.h"
#include "Mydict.h"
#include "Thread.h"

#include "json/json.h"

#include <string.h>
using std::set;
using std::string;
using std::vector;
using std::sprintf;

#include <unordered_map>
using std::unordered_map;

#include <iostream>
using std::cout;
using std::endl;

MyTask::MyTask(const string &queryWord,const wd::TcpConnectionPtr &conn)
:_queryWord(queryWord)
,_conn(conn)
{
	//通过单例模式创建一个Mydict类型的对象,并获得词典
	auto dict=Singleton<Mydict>::getInstance()->getDict();
	int bit_len=dict.size();
	_bit_array=new bool[bit_len];
	memset(_bit_array,0,bit_len);
}
void MyTask::execute()
{
	Cache &cache=CacheManager::getCache(wd::thread_index);
	string ret=cache.query(_queryWord);
	if(ret!=string())
	{
		_conn->sendInLoop(ret);
		cout<<"cache query success!"<<endl;
		return;
	}
	//index查找
	queryIndexTable();
	//反馈给客户端
	response(cache);
}
//处理从客户端接收到的数据，这里还是按照UTF-8的编码规则进行处理的
vector<string> MyTask::getChar(const string &word)
{
	size_t it=0;
	vector<string> ret;
	while(it<word.length())
	{
		if(word[it]&0x80)
		{
			int i;
			for(i=6;i>=2;--i)
			{
				if(word[it]&(1<<i))
					continue;
				else
					break;
			}
			ret.push_back(word.substr(it,8-i));
			it+=8-i;
		}
		else
		{
			ret.push_back(word.substr(it,1));
			++it;
		}
	}
	return ret;
}

//在索引表中查询
void MyTask::queryIndexTable()
{
	//通过单例对象创建Mydict类型的对象并拿到索引表
	unordered_map<string,set<int>> index_table=Singleton<Mydict>::getInstance()->getIndexTable();
	//得到一个字符作为key
	vector<string> char_list=getChar(_queryWord);//getChar()函数
	for(auto ch:char_list)
	{
		if(index_table.count(ch))
		{
			statistic(index_table[ch]);//这里其实是拿到与某个单词关联的set<int>类型的容器
		}								//或说是链表
	}
	return;
}
//上面拿到的是与字符相关联单词在容器中的下标，我们通过下标从词典中拿到单词
void MyTask::statistic(set<int> &iset)
{
	//set中存放的是单词在容器中的下标
	auto dict=Singleton<Mydict>::getInstance()->getDict();//得到存放词典的容器
	for(auto idx:iset)
	{
		string candidata=dict[idx].first;//拿到单词
		if(_bit_array[idx])
			continue;
		else
			_bit_array[idx]=true;
		int iDist=distance(candidata);//筛选，最小编辑距离小于3的放到候选队列中
		if(iDist<3)
		{
			_resultQue.push(MyResult(candidata,dict[idx].second,iDist));//这里的iDist
		}													//是自定义排序
	}
	return;
}
//计算最小编辑距离
int MyTask::distance(const string &rhs)
{
	vector<string> querry=getChar(_queryWord);//查询词经过UTF-8编码处理
	vector<string> candidata=getChar(rhs);//候选词也通过UTF-8编码处理
	int len1,len2;
	len1=querry.size();
	len2=candidata.size();
	//分配内存
	int **d=new int *[len1+1];
	for(int 1=0;i<=len1;++i)
	{
		d[i]=new int[len2];
	}
	//初始化
	for(int i=0;i<=len1;++i)
	{d[i][0]=i;}
	for(int j=0;j<=len2;++j)
	{d[0][j]=j;}
	//判断
	for(int i=1;i<=len1;++i)
	{
		for(j=1;j<=len2;++j)
		{
			int cost=querry[i-1]==candidata[j-1]?0:1;
			int deletion=d[i-1][j]+1;
			int insertion=d[i][j-1]+1;
			int substitution=d[i-1][j-1]+cost;
			d[i][j]=min(deletion,insertion,substitution);
		}
	}
	return d[len1][len2];
	for(int i=0;i<+len1;++i)
	{
		delete [] d[i];
	}
	delete [] d;
}

int MyTask::min(int a,int b,int c)
{
	int temp=a<b?a:b;
	return temp<c?temp:c;
}
//这里用Cache缓存存储了返回给客户端的数据，而且设置了只返回3个候选词给客户端；
//下次再搜索是先在Cache中搜索，加快检索速度
void MyTask::response(Cache &cache)
{
	if(_resultQue.empty())//如果结果队列为空，返回空
	{
		string result=" ";
		_conn->sendInLoop(result);
	}
	else//结果队列非空，把结果封装成Json类型返回给用户
	{
		Json::FastWrite writer;
		Json::Value array;
		for(int i=0;i<3&&!_resultQue.empty();++i)
		{
			string candidata=resultQue.top()._word;
			Json::Value new_item;
			char tmp[20]={0};
			sprintf(tmp,"%s%d","candidate",i);
			new_item[tmp]=canditate;
			_resultQue.pop();
			array.append(new_item);
		}
		string jsonstr=writer.write(array);
		_conn->sendInLoop(jsonstr);
		cache.addElement(_queryWord,jsonstr);
		cout<<"cache add"<<endl;
	}
	cout<<"reponse"<<endl;
	return;
}
