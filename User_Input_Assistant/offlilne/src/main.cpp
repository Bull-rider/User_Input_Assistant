 ///
 /// @file    main.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-29 16:42:55
 ///


#include "DictProducer.h"
#include "Index.h"
#include "Configuration.h"
#include "CppJieba.h"
#include <iostream>
using namespace std;

int  main()
{
	string config_file_path;
	config_file_path="../config/yuliao";
	cout<<config_file_path<<endl;

	map<string,string> data_dir(Configuration(config_file_path).getConfigMap());
	string en_store_path=data_dir["data_dir:"]+"/";
	//英文
	DictProducer en_dictproducer(data_dir["en_dir:"]);
	en_dictproducer.show_files();
	en_dictproducer.store_dict(en_store_path.append("english.dat"));

	//汉语
	cout<<"pls input cppjieba_config_file path:";
	config_file_path="../config/cppjieba_config";
	cout<<config_file_path<<endl;
	CppJieba jieba(Configuration(config_file_path).getConfigMap());
	DictProducer cn_dictproducer(data_dir["cn_dir:"],&jieba);
	string cn_store_path=data_dir["data_dir:"]+"/";
	cn_dictproducer.show_files();
	cn_dictproducer.store_dict(cn_store_path.append("chinese.dat"));//存放字典

	string index_store_path=data_dir["data_dir:"]+"/";
	Index index_table;
	index_table.init(file1,file2);
	index_table.store_index_table(index_store_path.append("index.dat"));
											//append函数在字符串后面添加字符串
	return 0;
}
