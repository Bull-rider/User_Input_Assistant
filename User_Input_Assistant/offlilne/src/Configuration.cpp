 ///
 /// @file    Configuration.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 10:33:55
 ///
#include "Configuration.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using std::string;
using std::map;
using std::cout;
using std::ifstream;
using std::istringstream;

Configuration::Configuration(const string &filepath)
:_filepath(filepath)
{
	ifstream ifs(_filepath);
	if(!ifs)
	{
		perror("fopen error!");
		exit();
	}
	string line,word,path;
	while(getline(line,ifs))
	{
		istringstream is(line);
		is>>key;
		is>>path;
		_configMap.insert(std::make_pair(key,path));
	}
	map<string,string> &Configuration::getCongigMap()
	{
		return _configMap;
	}
}
