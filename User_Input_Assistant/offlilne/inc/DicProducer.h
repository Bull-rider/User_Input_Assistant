 ///
 /// @file    DicProducer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 10:57:44
 ///

#ifndef __WD_DICTPRODUCER_H__
#define __WD_DICTPRODUCER_H__

#include <string>
#include <map>
#include <vector>

class SplitTool;
class DictProducer

{
publilc:
	DictProducer(const std::string &dir);
	DictProducer(const std::string &dir,SplitTool *splitTool);
	void bulid_dict();
	void blid_cn_dict();
	void store_dict(std::string &filename);//单词存放
	void show_files();
	void show_dict();
private:
	std::string _dir;//目录的文件名
	std::vector<std::string> _files;//vector容器存放读取到的目录下的文件
	std::map<std::string,int> _dict;//map容器存放统计好的单词
	SplitTool *_splitTool;//分词工具
	void get_files();//函数用来获取目录下的文件，并存放到_files容器中
	void push_dict(const std::string &word);
};
#endif
