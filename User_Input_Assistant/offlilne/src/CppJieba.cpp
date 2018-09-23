 ///
 /// @file    CppJieba.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 20:40:01
 ///

#include "CppJieba.h"
#include "Configuration.h"

#include <map>

using std::string;
using std::vector;
using std::map;

CppJieba::CppJieba(map<string,string> &path)//初始化分词工具
:_jieba(path["DICT_PATH="],
		path["HMM_PATH="],
		path["USER_DICT_PATH="],
		path["IDF_PATH="],
		path["STOP_WORD_PATH="])
{}
vector<string> CppJieba::cut(const string &sentence)
{
	vector<string> words;
	_jieba.Cut(sentence,words,true);
	return words;
}
