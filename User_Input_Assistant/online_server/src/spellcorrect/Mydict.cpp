 ///
 /// @file    Mydict.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 19:37:05
 ///
 
#include "Mydict.h"
#include <fstream>
using std::ifstream;

#include <iostream>
using std::cout;
using std::endl;

#include <sstream>
using std::stringstream;

using std::string;
using std::unordered_map;
using std::vector;
using std::set;
using std::pair;
using std::getline;

void Mydict::read_Dict(cosnt std::string &dictpath)//从给定的路径下读取词典并存放在vector容器
{
	ifstream ifs(dictpath);
	if(!ifs)
	{
		cout<<"open "<<dictpath<<"error!"<<endl;
		exit(-1);
	}
	string line;
	while(getline(ifs,line))
	{
		stringstream is(line);
		string key;
		int value;
		is>>key>>value;
		_dict.push_back(std::make_pair(key,value));
	}
	ifs.close();
	return true;
}

void Mydict::init(const std::string &dictEnPath,const std::string &dictCnPath
		const std::string &idexPath)//建立索引
{
	read_Dict(dictEnPath);
	read_Dict(dictCnPath);
	ifstream ifs(indexPath);
	if(!ifs)
	{
		cout<<"open "<<indexPath<<"error!"<<endl;
		exit(-1);
	}
	string line;
	while(getline(ifs,line))
	{
		stringstream ss(line);
		string key;
		ss>>key;
		int index;
		while(ss>>index)
		{
			_index_table[key].insert(index);
		}
	}
	ifs.close();
	return;
}
vector<pair<string,int>> &Mydict::getDict()
{
	return _dict;
}

unordered_map<string,set<int> > &Mydict::getIndexTable()
{
	return _index_table;
}
