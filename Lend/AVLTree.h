#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
#include <iomanip>
#include <string>
#include "AVLTreeNode.h"
using namespace std;
class AVLTree
{
public:
	AVLTree();
	~AVLTree(); //析构函数
	AVLTreeNode *root;

	void insert(AVLTreeNode *n); //插入

	void inOrder(ofstream & fs); //中序遍历修改文件
	void inOrderAux(ofstream & fs, AVLTreeNode *subtree);//中序遍历
	AVLTreeNode* find(UserInfo target); //查找元素
	void remove(UserInfo key); //删除元素
	void ClearTree(AVLTreeNode *n);//清除所有元素,用于析构函数
	void graph();//图形输出界面
	void graphAux(AVLTreeNode *subtree, int a);//图形输出
	
	//左右旋，插入删除时共用的函数
	void rotateLeft(AVLTreeNode *n);//左旋
	void rotateRight(AVLTreeNode *n);//右旋

	//辅助的函数
	void searchCur(const UserInfo &data, bool &found, AVLTreeNode *&x, AVLTreeNode*&parent);//remove辅助函数
	void restoreAVLDelete(AVLTreeNode *start, bool left);//删除节点后的调整函数
	void restoreAVLInsert(AVLTreeNode *ancestor, AVLTreeNode *newNode);//添加节点后的调整函数
	void adjustBalanceFactors(AVLTreeNode *end, AVLTreeNode *start);//调整平衡因子
};
#endif