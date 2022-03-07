#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

//class MyString
//{
//public:
//	MyString(const char* str = "")
//		:_str(new char[strlen(str) + 1])
//	{
//		strcpy(_str, str);
//	}
//
//	//现代写法，复用
//	MyString(const MyString& s)
//		:_str(nullptr)
//	{
//		MyString tmp(s._str);
//		swap(_str, tmp._str);
//		
//	}
//
//	MyString& operator=(MyString s)
//	{
//		swap(_str, s._str);
//		return *this;
//	}
//
//	~MyString()
//	{
//		delete[] _str;
//		_str = nullptr;
//	}
//private:
//	char* _str;
//};

class MyString
{
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin() const
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	void swap(MyString& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	MyString(const char* str = "")
		:_size(strlen(str))
		,_capacity(_size)
	{
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	//s2(s1)
	MyString(const MyString& s)
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		MyString tmp(s._str);
		swap(tmp);
	}

	//s3 = s1
	MyString& operator=(MyString s)
	{
		swap(s);
		return *this;
	}

	~MyString()
	{
		delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	const char* c_str() const
	{
		return _str;
	}

	size_t size() const
	{
		return _size;
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	void resize(size_t n, char ch = '\0')
	{
		if (n <= _size)
		{
			_size = n;
			_str[_size] = '\0';
		}
		else
		{
			if (n > _capacity)
			{
				reserve(n);
			}
			for (size_t i = _size; i < n; ++i)
			{
				_str[i] = ch;
			}
			_size = n;
			_str[_size] = '\0';
		}
	}

	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;

			_capacity = n;
		}
	}

	void push_back(char ch)
	{
		/*if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2*_capacity);
		}

		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';*/

		insert(_size, ch);
	}

	void append(const char* str)
	{
		/*size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;*/

		insert(_size, str);
	}

	MyString& operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	MyString& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	void clear()
	{
		_str[0] = '\0';
		_size = 0;
	}

	size_t find(char ch, size_t pos = 0)
	{
		if (pos >= _size)
		{
			return npos;
		}

		for (size_t i = pos; i < _size; ++i)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;
	}

	size_t find(const char* s, size_t pos = 0)
	{
		if (pos >= _size)
		{
			return npos;
		}
		char* tmp = strstr(_str + pos, s);
		if (tmp == nullptr)
		{
			return npos;
		}
		else
		{
			return tmp - _str;
		}

	}

	MyString& insert(size_t pos, char ch)
	{
		assert(pos <= _size);

		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}

		size_t end = _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos] = ch;
		++_size;
		return *this;
	}

	MyString& insert(size_t pos, const char* s)
	{
		assert(pos <= _size);

		size_t len = strlen(s);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}

		size_t end = _size + len;
		while (end >= pos + len)
		{
			_str[end] = _str[end - len];
			--end;
		}
		strncpy(_str + pos, s, len);
		_size += len;
		return *this;
	}

	MyString& erase(size_t pos = 0, size_t len = npos)
	{
		assert(pos < _size);

		if (len == npos || pos + len >= _size)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}
		return *this;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;

	static const size_t npos;
};

const size_t MyString::npos = -1;

bool operator<(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.c_str(), s2.c_str()) < 0;
}

bool operator==(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.c_str(), s2.c_str()) == 0;
}


bool operator<=(const MyString& s1, const MyString& s2)
{
	return s1 < s2 || s1 == s2;
}

bool operator>(const MyString& s1, const MyString& s2)
{
	return !(s1 <= s2);
}

bool operator>=(const MyString& s1, const MyString& s2)
{
	return !(s1 < s2);
}


bool operator!=(const MyString& s1, const MyString& s2)
{
	return !(s1 == s2);
}

ostream& operator<<(ostream& out, MyString& s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		out << s[i];
	}
	return out;
}

istream& operator>>(istream& in, MyString& s)
{
	s.clear();

	char ch = in.get();
	while (ch != ' ' && ch != '\n')
	{
		s += ch;
		ch = in.get();
	}
	return in;
}