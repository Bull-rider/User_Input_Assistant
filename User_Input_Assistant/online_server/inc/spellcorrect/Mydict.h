 ///
 /// @file    Mydict.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 19:37:31
 ///
// 获取词典和索引
#ifndef __MYDICT_H__
#define __MYDICT_H__

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
class Mydict
{
public:
	void read_Dict(const std::string &dictpath);
	void init(const std::string &dictEnPath,const std::string &dictCnPath,
			const std::string &indexPath);//通过中英文词典文件路径初始化词典
	std::vector<std::pair<std::string,int> > &getDict();
	std::unordered_map<std::string,std::set<int>> &getIndexTable();
private:
	std::vector<std::pair<std::string,int>> _dict;//存放词典
	std::unordered_map<std::string,std:;set<int>> _index_table;//存放索引
};
#endif
