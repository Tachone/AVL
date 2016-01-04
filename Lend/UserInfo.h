
#ifndef UserInfo_H
#define UserInfo_H

#include <string>
#include <iostream>
using namespace std;
class UserInfo
{
public:
	UserInfo(){} //Ĭ�Ϲ��캯��
	//���βεĹ��캯��
	//ȱʡ��������˺���ͬ
	UserInfo(string  name, string pass);
	UserInfo(string  name);

	UserInfo(const UserInfo &b);//���ƹ��캯��

	//������������أ�balabala
	friend bool operator <(const UserInfo &a, const UserInfo &b);
	friend bool operator >(const UserInfo &a, const UserInfo &b);
	bool operator == (const UserInfo &b);
	friend ostream& operator <<(ostream &output, const UserInfo &b);

	//������Ԫ��
	friend class Interface;
	friend class AVLTree;

private:
	string  username;//�û���
	string password;//����
};
#endif