 ///
 /// @file    CacheManager.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-06 23:39:06
 ///
 
#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

#include <iostream>
#include <string>
#include <vector>

class Cache;
class TimerThread;//定时器，设置定时更新Cache
class CacheManager
{
public:
	static void initCache(std::size_t,const std::string &filename);

	static Cache &getCache(std::size_t idx);

	static void periodicUpdateCaches();
private:
	static std::vector<Cache> _cacheList;
};
#endif
