#ifndef AVLTreeNode_H
#define AVLTreeNode_H

#include"UserInfo.h"
class AVLTreeNode
{
public:
	UserInfo key;//����
	AVLTreeNode *left;
	AVLTreeNode *right;
	AVLTreeNode *parent;//����ָ��
	char nodemark;//ƽ������

	//Ĭ�Ϲ��캯��
	AVLTreeNode(){
		left = 0;
		right = 0;
		parent = 0;
		nodemark = 'E';
	}
	//���û���Ϣ�����Ĺ��캯��
	AVLTreeNode(UserInfo s){
		key = s;
		left = 0;
		right = 0;
		parent = 0;
		nodemark = 'E';
	}
};
#endif