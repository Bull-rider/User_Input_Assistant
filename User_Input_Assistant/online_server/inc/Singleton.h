 ///
 /// @file    Singleton.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-07 21:47:45
 ///
 
#ifndef SINGLETON_H
#define SINGLETON_H
template <typename T>
class Singleton
{
	class AutoRelease
	{
	public:
		AutoRelease(){}
		~AutoRelease()
		{
			if(_pInstance)
			{
				delete _pInstance;
			}
		}
	};
public:
	template<typename... Args>
	static T *geInstance(Args... args)
	{
		if(_pInstance==nullptr)
		{
			_autoRelease;
			_pInstance=new T(args...);
		}
		return _pInstance;
	}
	static T *getInstance()
	{
		if(_pInstance==nullptr)
		{
			_autoRelease;
			_pInstance=new T();
		}
		return _pInstance;
	}
private:
	Singleton(){}
	~Singleton(){}
private:
	static T *_pInstance;
	static AutoRelease _autoRelease;
};
template <typename T>
T Singleton<T>::_pInstance=NULL;
class Singleton<T>::AutoRelease Singleton<T>::_autoRelease;
#endif
