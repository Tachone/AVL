
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
	Interface();//构造函数，读取文件，并建树
	~Interface();//保存信息到文件，销毁树
	void mainFace();
	void logIn();
	void addUser();
	void removeUser();
	void update();
	void test();
private:
	AVLTree *data; //根节点
};
#endif