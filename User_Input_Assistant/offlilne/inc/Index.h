 ///
 /// @file    Index.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 14:01:23
 ///

#ifndef __WD_INDEX_H__
#define __WD_INDEX_H__
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

class Index
{
public:
	void init(const sd::string &dictEnPath,const std::string &dictCnPath)
	void read_Dict(const std::string &path);
	void create_index_table(int inidex);
	void store_index_table(const std::string &index_Path);
private:
	std::vector<std::pair<std::string,int>> _dict;
	std::unordered_map<std::string,std::set<int>> _index_table;//注意第二个参数
	//是一个容器，我们就是用它来存放相同键值的数据，也就是容器_dict中的下标
};
#endif
