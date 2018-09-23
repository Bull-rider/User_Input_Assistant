 ///
 /// @file    Configuration.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 19:20:07
 ///
 
#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__

#include <string>
#include <map>

class Configuration
{
public:
	std::map<std::string,std::string> &getMap(){return _map;}
	bool init(const std::string &filename);
	void show();
private:
	std::map<std::string,std::string> _map;//传入的文件所在路径
};

#endif
