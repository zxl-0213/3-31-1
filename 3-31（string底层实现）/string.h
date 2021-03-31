#define _CRT_SECURE_NO_WARNINGS 1;

#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
#include<stdio.h>
//简单的string实现；包括构造函数、析构函数、拷贝构造函数。

namespace zxl //自己开辟一块命名空间，因为c++库中有string变量，自己开命名空间方便区分
{
	class string
	{
	public:
		/*string()
			:_str(new char[1])
		{
			_str[0] = '\0';
		}
		string(const char* str)
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}*/

		//构造函数  
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])//加1是因为要留一个位置给\0；
		{
			strcpy(_str, str);
		}

		//拷贝构造,深拷贝。
		string(const string& s)
			:_str(new char[strlen(s._str)+1])//深拷贝原理：拷贝一块一样的空间，然后指针指向就可以了
		{
			strcpy(_str, s._str);
		}

		//赋值运算符重载,也是利用深拷贝。
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[strlen(s._str) + 1];
				delete[]_str;
				strcpy(tmp,s._str);
				_str = tmp;
			}
			return *this;
		}

		//析构函数
		~string()
		{
			delete[]_str;
			_str = nullptr;
		}
		int size()
		{
			return strlen(_str);
		}
		char& operator[](size_t i)
		{
			return _str[i];
		}

		//以c语言形式输出
		char* c_str()
		{
			return _str;
		}
	private:
		char* _str;
	};
	void string_text1()
	{
		string s1("hello");
		string s2;
		for (size_t i = 0; i < s1.size(); ++i)
		{
			s1[i] += 1;
			cout << s1[i] << " ";
		}
		cout << endl;
		for (size_t i = 0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i] << " ";
		}
		cout << endl;
	}

	void string_text2()
	{
		string s1("hello");
		string s2(s1);
		string s3;
		s3 = s1;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;
	}
}


//增删改查
namespace zxl2
{
	class string
	{
	public:
		string(const char* str = "")
		{
			_str = new char[strlen(str) + 1];
			_size = strlen(str);
			_capacity = _size;
			strcpy(_str, str);
		}

		string(const string& s)
			:_str(new char[s._size+1])
		{
			_size = s._size;
			_capacity = s._capacity;
			strcpy(_str, s._str);
		}

		~string()
		{
			delete[]_str;
			_str = nullptr;
			_capacity = _size = 0;
		}

		size_t size()const //==size_t size(char* str)
		{
			return _size;
		}
		size_t capacity()
		{
			return _capacity;
		}
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const
		{
			assert(i < _size);
			return _str[i];
		}
		char* c_str()
		{
			return _str;
		}
		string& operator=(const string& s)
		{
			char* tmp = new char[s._size + 1];
			strcpy(tmp, s._str);
			delete[]_str;
			_size = s._size;
			_capacity = s._capacity;
			_str = tmp;
			return *this;
		}
		//迭代器
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		void reserve(const size_t n)
		{
			if (n > _capacity)
			{
				char* newstr = new char[n + 1];
				strcpy(newstr, _str);
				delete[]_str;
				_str = newstr;
				_capacity = n;
			}
		}
		void push_back(const char ch)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';//插入后的数组应该有\0结束。
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				size_t newcapacity = _size + len;
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}

		string& operator+=(const char ch)
		{
			this->push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i=0; i < s.size(); ++i)
		{
			
			cout << s[i];
		}
		return out;
	}

	//三种遍历
	void string_text1()
	{
		string s1("hello");
		string s2(s1);
		string s3;
		s3 = s1;
		cout << s3 << endl;
		//第一种遍历
		for (size_t i=0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i]<<" ";
		}
		cout << endl;
		//第二种遍历
		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			*it -= 1;
			cout << *it << " ";
			it++;
		}
		cout << endl;
		//范围for
		for (auto e : s2)
		{
			e += 3;
			cout << e << " ";
		}
	}
	void string_text2()
	{
		string s1;
		string s2("hello");
		s2.push_back(' ');
		s2.push_back('w');
		s2.push_back('o');
		cout << s2 <<endl;

		s2.append("rld****");
		cout << s2 << endl;

		s1 += "hello";
		s1 += ' ';
		s1 += "world";
		cout << s1 << endl;

	}
	
}