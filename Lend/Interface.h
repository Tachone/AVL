
#ifndef Interface_H
#define Interface_H
#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
using namespace std;
class Interface
{
public:
	Interface();//���캯������ȡ�ļ���������
	~Interface();//������Ϣ���ļ���������
	void mainFace();
	void logIn();
	void addUser();
	void removeUser();
	void update();
	void test();
private:
	AVLTree *data; //���ڵ�
};
#endif