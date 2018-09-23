 ///
 /// @file    CppJieba.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 20:28:50
 ///

#ifndef _CPPJIEBA_H
#define _CPPJIEBA_H

#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"

#include <string>
#include <vector>
#include <map>
//定义分词工具。
class Configuration;
class CppJieba:public SplitTool
{
public:
	CppJieba(std::map<std::string,std::string> &path);//要给分词工具传递一个文件的路径，路径存放在容器中
	~CppJieba(){}

	std::vector<std::string> cut(const std::string &sentence);
private:
	cppjieba::Jieba _jieba;
};
#endif
