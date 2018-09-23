 ///
 /// @file    Configuration.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 10:29:50
 ///
#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__

#include <string>
#include <map>

class Configuration
{
public:
	Configuration(const std::string &filepath);
	std::map<std::string,std::string> &getConfigMap();
private:
	std::string _filepath;
	std::map<std::string,std::string> _configMap;
};
#endif
