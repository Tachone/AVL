#ifndef AVLTreeNode_H
#define AVLTreeNode_H

#include"UserInfo.h"
class AVLTreeNode
{
public:
	UserInfo key;//内容
	AVLTreeNode *left;
	AVLTreeNode *right;
	AVLTreeNode *parent;//父亲指针
	char nodemark;//平衡因子

	//默认构造函数
	AVLTreeNode(){
		left = 0;
		right = 0;
		parent = 0;
		nodemark = 'E';
	}
	//带用户信息参数的构造函数
	AVLTreeNode(UserInfo s){
		key = s;
		left = 0;
		right = 0;
		parent = 0;
		nodemark = 'E';
	}
};
#endif