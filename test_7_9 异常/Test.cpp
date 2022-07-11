#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <time.h>
#include <thread>
using namespace std;

//double Division(int a, int b)
//{
//	// ��b == 0ʱ�׳��쳣
//	if (b == 0)
//	{
//		throw "Division by zero condition!";
//	}
//	return (double)a / (double)b;
//}
//void Func()
//{
//	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
//	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
//	// �����׳�ȥ��
//	int* array = new int[10];
//	try
//	{
//		int len, time;
//		cin >> len >> time;
//		cout << Division(len, time) << endl;
//	}
//	catch (...)
//	{
//		cout << "delete []" << array << endl;
//		delete[] array;
//		//���²���
//		throw;
//	}
//	// ...
//	cout << "delete []" << array << endl;
//	delete[] array;
//}
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	return 0;
//}

// ������������ͨ��ʹ�õ��쳣�̳���ϵ
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		,_id(id)
	{}

	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _id;
};

class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}

	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;

		return str;
	}
private:
	const string _sql;
};

class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}

	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};

class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		,_type(type)
	{}

	virtual string what() const 
	{
		string str = "HttpServerException, ";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};

void SQLMgr()
{
	srand((unsigned int)time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("Ȩ�޲���", 101, "select * from name = '����'");
	}

}

void CacheMgr()
{
	srand((unsigned int)time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("���ݲ�����", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("Ȩ�޲���", 101);
	}
	SQLMgr();
}

void HttpServer()
{
	srand((unsigned int)time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("������Դ������", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("Ȩ�޲���", 101, "post");
	}
	CacheMgr();
}

void ServerStart()
{
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(1));
		try
		{
			HttpServer();
		}
		catch (const Exception& e) // ���ﲶ�������Ϳ���
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
}

int main()
{
	ServerStart();
	return 0;
}