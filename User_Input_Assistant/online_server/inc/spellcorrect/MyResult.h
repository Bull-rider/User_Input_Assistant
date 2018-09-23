 ///
 /// @file    MyResult.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-05 20:48:45
 ///
 
#ifndef _MYRESULT_H
#define _MYRESULT_H
#include <string>

class MyResult
{
	friend class MyCompare;
	friend class MyTask;
public:
	MyResult(std::string word,int iFreq,int iDist)
	:_word(word)
	,_iFreq(iFreq)
	,_iDist(iSist)
	{}
private:
	std::string _word;
	int _iFreq;
	int _iDist;
};
#endif
