 ///
 /// @file    DicProducer.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 11:09:00
 ///

#include "DicProducer.h"
#include "CppJieba.h"

#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <ctype.h>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::get;
using std::vector;
using std::transform;

DicProducer::DicProducer(const std::string &dir)
:_dir(dir)
{
	get_files();
	bulid_dict();
}
DictProducer::DictProducer(const string &dir,SplitTool *splitTool)//处理汉语时用到分词工具
:_dir(dir)
,_splitTool(splitTool)
{
	get_files();
	bulid_cn_dict();
}
//特殊单词处理
void DictProducer::bulid_dict()
{
	for(auto filename:_files)
	{
		ifstream ifs(filename);
		if(!ifs)
		{
			cout<<"ifstream open error!"<<endl;
			exit(-1);
		}
		string line;
		string word;
		while(getline(ifs,line))
		{
			//for循环内对单词大小写处理，以及特殊字符处理
			for(size_t i=0;i<line.length();++i)
			{
				if(!isalpha(line[i]))
				{
					continue;
				}
				while(i<line.length()&&isalpha(line[i]))
				{
					word+=(line[i]>='A'&&line[i]<='Z')?(line[i]+32:line[i]);
					++i;
				}
				//如果最后一个字符是连接符
				if(line[i]=='-')
				{
					char tmp;
					if(i==line.length()-1)
					{
						while(ifs>>tmp)
						{
							if(isalpha(tmp))
								word+=tmp;
							else
								break;
						}
						++i;
					}
					else
					{
						if(isalpha(line[i+1]))
						{
							word+=line[i++];
							while(i<line.length()&&isalpha(line[i]))
							{
								word+=(line[i]>'A'&&line[i]<'Z')?(line[i]+32:line[i]);
								++i
							}
						}
					}
				}
				push_dict(word);//把处理过的单词放入容器
				word.clear();
			}
		}
		ifs.close();
	}
	return;
}
void DictProducer::bulid_cn_dict()
{
	for(auto filename:_files)
	{
		ifstream ifs(filename);
		if(!ifs)
		{
			cout<<"ifstream open error!"<<endl;
			exit(-1);
		}
		string line;
		string lines;
		vector<string> words;//容器暂时存放分词结果
		while(getline(ifs,line))
		{
			lines.append(line);//存放将篇内容,这样没有\n产生
		}
		words=_splitTool->cut(lines);//分词后存储
		for(auto word:words)
		{
			transform(word.begin(),word.end(),word.begin(),::tolower);
			push_dict(word);
		}
		ifs.close();
	}
	return;
}
//获取要处理的文件名，读取目录下的文件
void DictProducer::get_files()
{
	DIR *Dir;
	struct dirent *ptr;
	Dir=opendir(_dir.c_str());//
	string path(_dir+"/");
	while((ptr=readdir(Dir))!=NULL)
	{
		if(!strcmp(ptr->d_name,".")||!strcmp(ptr->d_name,".."))
			continue;
		_files.push_back(path+ptr->d_name);
	}
	closedir(Dir);
	return;
}
//显示文件
void DictProducer::show_files()
{
	for(auto file:_files)
	{
		cout<<file<<endl;
	}
	return;
}
//单词添加到容器中
void DictProducer::push_dict(const std::string &word)
{
	_dict[word]++;
	return;
}
//把统计好的单词从容器输出到文件
void DictProducer::dict_store(const std::string *filename)
{
	ofstream ofs(filename);
	if(!ofs)
	{
		cout<<"input"<<filename<<"error"<<ednl;
		exit(-1);
	}
	for(auto pairs:_dict)
	{
		ofs<<pairs.first<<"\t"<<pairs.second<<endl;
	}
	ofs.close();
	return;
}
//显示词典
void DictProducer::show_dict()
{
	for(auto it=_dict.begin();it!=_dict.end();++it)
	{
		cout<<it->first<<"\t"<<it->second<<endl;
	}
	return;
}
