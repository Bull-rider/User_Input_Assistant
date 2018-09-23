 ///
 /// @file    CacheManager.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-06 23:45:19
 ///
 
#include "CacheManager.h"
#include "Cache.h"
#include "Singleton.h"
#include "Configuration.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

vector<Cache> CacheManager::_cacheList;//注意静态数据成员只能在类外初始化


//创建新的Cache缓存
void CacheManager::initCache(size_t list_num,const string &filename)
{
	Cache cache;
	cache.readFromFile(filename);
	for(size_t i=0;i<list_num;++i)
	{
		_cacheList.push_back(chche);
	}
	return;
}

Cache &CacheManager::getCache(size_t idx)
{
	return _cacheList[idx];
}

void CacheManager::periodicUpdateCaches()
{
	auto cache0_iter=_cacheList.begin();
	for(auto iter=cache0_iter+1;iter!=_cacheList.end();++iter)
	{
		cache0_iter->update(*iter);
	}
	for(auto iter=cache0_iter+1;iter!=_cacheList.end();++iter)
	{
		iter->update(*cache0_iter);
	}
	cache0_iter->writeToFile(Singleton<Configuration>::getInstance()->getMap()["Cache"]);
	cout<<"Cache update!"<<endl;
	return
}
