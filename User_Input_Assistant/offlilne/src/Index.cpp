 ///
 /// @file    Index.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 14:07:31
 ///

#include "Index.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

using std::ifstream;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::getline;
using std::set;
using std::vector;
using std::unordered_map
//首先读取词典，存放到一个vector类型的容器中
void Index::read_Dict(const string &dictpath)
{
	ifstream ifs(dictpath);
	if(!ifs)
	{
		cout<<"open error!"<<endl;
		exit(-1);
	}
	string word,line;
	while(getline(ifs,line))
	{
		stringstream ss(line);
		string key;
		int value;
		ss>>key>>value
		_dict.push_back(std::make_pair(key,value));
	}
	ifs.close();
}
void Index::init(const std::string &dictEnPath,const std::string &dictCnPath)
{
	read_Dict(dictEnPath);
	read_Dict(dictCnPath);
	for(size_t idx=0;idx!=_dict.size();++idx )
	{
		create_index_table(idx);//创建词典索引
	}
}
void Index::create_index_table(int index)
{
	//English word
	string key;//我们虽然定义的key是字符串，但在计算机中却是以0101的形式存储的
	string word=_dict[index].first;//拿到一个单词
	//对于英文:具有相同字母的单词都有一个共同的key,一个单词可以有多个key
	//具有相同键值的数据我们存放在链表中
	for(std::size_t idx=0;idx!=word.size();++idx)
	{
		char ch=word[idx];
		//中文
		if(ch&(1<<7))//如果编码大于127，则为多字节编码
		{
			//两个字节编码的第一个字节以110开头
			//第一个字节可能以110 0XXXX或110 1XXXX
			if((ch&0xF0)==0xC0||(ch&0xF0)==0xD0)
			{
				key=word.substr(idx,2);
				++idx;
			}
			//3个字节编码的以1110开头
			else if((ch&0xF0)==0xE0)
			{
				key=word.substr(idx,3);
				idx+=2;
			}
			//4个字节编码的以11110开头 
			else if((ch&0x0xFF)>=0xF0&&(ch&0xFF)<=0xF7)
			{
				key=word.substr(idx,4);
				idx+=3;
			}
			//5个字节编码的以111110开头
			else if((ch&0xFF)>=0xF8&&(ch&0xFF)<=0xFB)
			{
				key=word.substr(idx,5);
				idx+=4;
			}
			//6个字节编码的以1111110开头
			else if((ch&0xFF)==0xFC)
			{
				key=word.substr(idx,6);
				idx+=5;
			}
		}
		//英文
		else
		{
			key=word.substr(idx,1);
		}
		_dict_table[key].insert(index);//把单词的下标插入对应键值的set容器中
	}
}
//输出索引到文件
void Index::store_idex_table(const std::string &idex_Path)
{
	ofstream ofs(idex_Path);
	if(!ofs)
	{
		cout<<"error open!"<<endl;
		exit(-1);
	}
	//first是键值也就是一个桶，second是桶中元素
	for(auto it=_dict_table.begin();it!=_dict_table.end();++it)
	{
		cout<<it->first<<"\t";
		for(auto set_it:it->second)//这里输出的是含有这个字母的单词的下标
		{
			cout<<set_it<<" ";
		}
		ofs<<endl;
	}
	ofs.close();
}
