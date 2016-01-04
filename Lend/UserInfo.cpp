#include "UserInfo.h"
//各种构造函数的实现
UserInfo::UserInfo(string name, string pass)
{
	username = name;
	password = "123456";
}
UserInfo::UserInfo(string  name)
{
	username = name;
	password = "123456";
}

UserInfo::UserInfo(const UserInfo &b)//复制构造函数
{
	username = b.username;
	password = b.password;
}
//各种运算符的重载
bool operator <(const UserInfo &a, const UserInfo &b)
{
	return a.username < b.username;
}
bool operator >(const UserInfo &a, const UserInfo &b)
{
	return a.username > b.username;
}
bool UserInfo::operator == (const UserInfo &b)//与本类比较
{
	if (this->username == b.username)
		return true;
	else
		return false;
}
ostream& operator <<(ostream &output, const UserInfo &b)
{
	output << b.username;
	return output;
}