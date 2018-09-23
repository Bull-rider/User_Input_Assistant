 ///
 /// @file    SplitTool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 20:20:24
 ///

#ifndef __SPLITTOOL_H
#define __SPLITTOOL_H
#include <vector>
#include <string>
class SplitTool
{
public:
	SplitTool(){}
	virtual std::vector<std::string> cut(const std::string &sentence)=0;
	virtual ~SplitTool(){}
};
#endif
//分词的头文件，在设计最小编辑距离时会用到。
