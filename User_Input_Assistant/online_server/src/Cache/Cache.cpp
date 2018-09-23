 ///
 /// @file    Cache.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-06 23:13:08
 ///
 
#include "Cache.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

using std::string;
using std::getline;

#include <iostream>
using std::cout;
using std::endl;

//把发送给客户端的数据添加到Cache缓存中，
void Cache::addElement(const string &key,const string &value)
{
	_hashMap.insert(std::make_pair(key,value));
	return;
}


//从文件中读取内容，生成hash索引作为cache缓存
void Cache::readFromFile(const string &filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout<<"open"<<filename<<"error"<<endl;
		exit(-1);
	}
	string query,candidate;
	while(ifs>>query>>candidate)
	{
		_hashMap.insert(std::make_pair(query,candidate));
	}
	ifs.close();
	return;
}

//把hash中的内容写入文件
void Cache::writeToFile(const string &filename)
{
	ofstream ofs(filename);
	if(!ofs)
	{
		cout<<"open"<<filename<<"error"<<endl;
		eixt(-1);
	}
	for(auto iter=_hashMap.begin();iter!=_hashMap.end();++iter)
	{
		ofs<<iter->first<<"\t"<<iter->second<<endl;
	}
	ofs.close();
	return;
}
//更新每一个Cache缓存
void Cache::updata(const Cache &rhs)
{
	for(auto &pair:rhs._hashMap)
	{
		auto it=_hashMap.find(pair.first);
		if(it==_hashMap.end())
		{
			_hashMap.insert(std::move(pair));
		}
	}
	return;
}

string Cache::query(const string &query)
{
	auto it=_hashMap.find(query);
	if(it!=_hashMap.end())
		return it->second;
	else
		return string();
}
