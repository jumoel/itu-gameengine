#ifndef ITUENGINE_TSINGLETON_H
#define ITUENGINE_TSINGLETON_H

template <class T> 
class TSingleton
{
public:

	static T * Instance()
	{
		static T obj;
		return &obj;
	}

private:
	TSingleton() {}
	~TSingleton() {}

};

#define SINGLETON(T) protected:friend class TSingleton< T >;T(){};  
#define SINGLETONINSTANCE(T) TSingleton< T >::Instance()

#endif