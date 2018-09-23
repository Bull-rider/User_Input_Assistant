 ///
 /// @file    Cache.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-06 23:06:43
 ///
 
#ifndef _CACHE_H
#define _CACHE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

class Cache
{
public:
	void addElement(const std::string &key,const std::string &value);

	void readFromFile(const std::string &filename);

	void writeToFile(const std::string &filename);

	void updata(const Cache &rhs);

	std::string query(const std::string &query);
private:
	std::unordered_map<std::string,std::string> _hashMap;
};
#endif
