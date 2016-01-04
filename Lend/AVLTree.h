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
	~AVLTree(); //��������
	AVLTreeNode *root;

	void insert(AVLTreeNode *n); //����

	void inOrder(ofstream & fs); //��������޸��ļ�
	void inOrderAux(ofstream & fs, AVLTreeNode *subtree);//�������
	AVLTreeNode* find(UserInfo target); //����Ԫ��
	void remove(UserInfo key); //ɾ��Ԫ��
	void ClearTree(AVLTreeNode *n);//�������Ԫ��,������������
	void graph();//ͼ���������
	void graphAux(AVLTreeNode *subtree, int a);//ͼ�����
	
	//������������ɾ��ʱ���õĺ���
	void rotateLeft(AVLTreeNode *n);//����
	void rotateRight(AVLTreeNode *n);//����

	//�����ĺ���
	void searchCur(const UserInfo &data, bool &found, AVLTreeNode *&x, AVLTreeNode*&parent);//remove��������
	void restoreAVLDelete(AVLTreeNode *start, bool left);//ɾ���ڵ��ĵ�������
	void restoreAVLInsert(AVLTreeNode *ancestor, AVLTreeNode *newNode);//��ӽڵ��ĵ�������
	void adjustBalanceFactors(AVLTreeNode *end, AVLTreeNode *start);//����ƽ������
};
#endif