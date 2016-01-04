
#ifndef UserInfo_H
#define UserInfo_H

#include <string>
#include <iostream>
using namespace std;
class UserInfo
{
public:
	UserInfo(){} //默认构造函数
	//带形参的构造函数
	//缺省的密码和账号相同
	UserInfo(string  name, string pass);
	UserInfo(string  name);

	UserInfo(const UserInfo &b);//复制构造函数

	//各种运算符重载，balabala
	friend bool operator <(const UserInfo &a, const UserInfo &b);
	friend bool operator >(const UserInfo &a, const UserInfo &b);
	bool operator == (const UserInfo &b);
	friend ostream& operator <<(ostream &output, const UserInfo &b);

	//声明友元类
	friend class Interface;
	friend class AVLTree;

private:
	string  username;//用户名
	string password;//密码
};
#endif