 ///
 /// @file    main.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-07 21:36:29
 ///
 
#include "Configuration.h"
#include "SpellCorrectServer.h"
#include "CacheManager.h"
#include "Singleton.h"
#include "Mydict.h"

using std::stoi;

int  main()
{
	//这里的初始化及其重要，没有它什么都没有
	Singleton<Configuration>::getInstance()->init("../conf/config");
	Singleton<Mydict>::getInstance()->init(
			Singleton<Configuration>::getInstance()->getMap()["dict"],
			Singleton<Configuration>::getInstance()->getMap()["cn_dict"],
			Singleton<Configuration>::getInstance()->getMap()["index"]);
	CacheManager::initCache(stoi(Singleton<Configuration>::getInstance()->getMap()["thread_num"]),
			Singleton<Configuration>::getInstance()->getMap()["cache"]);
	SpellCorrectServer server;
	server.start();
	return 0;
}
