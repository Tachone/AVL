#include "UserInfo.h"
//���ֹ��캯����ʵ��
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

UserInfo::UserInfo(const UserInfo &b)//���ƹ��캯��
{
	username = b.username;
	password = b.password;
}
//���������������
bool operator <(const UserInfo &a, const UserInfo &b)
{
	return a.username < b.username;
}
bool operator >(const UserInfo &a, const UserInfo &b)
{
	return a.username > b.username;
}
bool UserInfo::operator == (const UserInfo &b)//�뱾��Ƚ�
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