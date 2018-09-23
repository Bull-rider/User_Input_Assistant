 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-02 16:12:10
 ///
 //这个类的作用就是复制构造函数和赋值运算符函数设置位私有的防止复制,其他类继承时就
 //不能复制了。
#ifndef _WD_NONCOPYABLE_H__
#define _WD_NONCOPYABLE_H__
namespace wd
class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable() {}
private:
	Noncopyable(const Noncopyable &);
	Noncopyable &operator=(const Noncopyable &);
};
#endif
