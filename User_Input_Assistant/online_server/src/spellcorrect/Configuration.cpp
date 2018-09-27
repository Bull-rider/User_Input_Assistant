 ///
 /// @file    Confifuration.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 19:25:38
 ///
 
#include "Configuration.h"
#include <fstream>
#include <iostream>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::map;
using std::cout;
using std::endl;
using std::string;
using std::getline;

bool Configuration::init(std::string &filename)//这里传进去的路径，我们在主函数中传递
{
	ifstream ifs(filename.c_str());
	if(!ifs)
	{
		cout<<"open "<<filename <<"error!"<<endl;
		return false;
	}
	string line;
	while(getline(ifs,line))
	{
		istringstream is(line);
		string key,value;
		is>>key>>value;
		_map.insert(make_pair(key,value));
	}
	ifs.close();
	return true;
}
void Configuration::show()
{
	for(auto it=_map.begin();it!=_map.end();++it)
	{
		cout<<it->first<<"\t"<<it->second<<endl;
	}
}

