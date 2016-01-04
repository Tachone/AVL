#include"AVLTree.h"
#include <fstream>

AVLTree::AVLTree()//���캯��
{
	root = NULL; 
}

AVLTree::~AVLTree()//��������
{

	ClearTree(root);
}

void AVLTree::ClearTree(AVLTreeNode *n)
{
	if (n != NULL)
	{
		ClearTree(n->left);//�ͷ�������
		ClearTree(n->right);//�ͷ�������
		delete n;
	}
}
//������ĺ���
void AVLTree::insert(AVLTreeNode *newNode)
{
	AVLTreeNode *temp, *back, *ancestor;
	temp = root;
	back = NULL;
	ancestor = NULL;
	// �ǿ����Ļ�ֱ����Ϊ���ڵ�
	if (root == NULL)
	{
		root = newNode;
		return;
	}

	while (temp != NULL) // ����������ֱ��NULL
	{
		back = temp;//back�ǲ�����ĸ��ڵ�
			// ����ancestor��ancestor Ϊ����������Ĳ�ƽ��Ľڵ㣨ƽ�����Ӳ���"E"��
			// �½ڵ㱻����
		if (temp->nodemark != 'E')
			ancestor = temp;
		if (newNode->key < temp->key)
			temp = temp->left;
		else if (newNode->key > temp->key)
			temp = temp->right;
		else
		{
			return;//��ȵĽ���ǲ������
		}
	}
	// temp�Ѿ�Ϊ��
	// back Ϊ�²���ڵ�ĸ���
	newNode->parent = back; // ����backָ��������
	if (newNode->key < back->key) // ����������
	{
		back->left = newNode;
	}
	else // ����������
	{
		back->right = newNode;
	}
	// ����restoreAVLInsert��Ա��������ƽ�����
	restoreAVLInsert(ancestor, newNode);
}
//��������ƽ����
void AVLTree::restoreAVLInsert(AVLTreeNode *ancestor, AVLTreeNode *newNode)
{
     //���벻Ӱ��ƽ����
	if (ancestor == NULL)
	{
		if (newNode->key < root->key) // ��������ƽ������
			root->nodemark = 'L';
		else
			root->nodemark = 'R';
		// ����ƽ������
		adjustBalanceFactors(root, newNode);
	}

	//  ancestor ���ڣ�����Ӱ��ƽ���Ե����
	// ancestor.balanceFactor = 'L' ���²������뵽������  ����

	// ancestor.balanceFactor = 'R' ���²������뵽������

	else if (((ancestor->nodemark == 'L') && (newNode->key > ancestor->key)) ||
		((ancestor->nodemark == 'R') && (newNode->key < ancestor->key)))
	 {
		ancestor->nodemark = 'E';
		// ����ƽ������
		adjustBalanceFactors(ancestor, newNode);
	 } 
	//RR�Ͳ�ƽ�⣬��Ҫ����
	else if ((ancestor->nodemark == 'R') && (newNode->key > ancestor->right->key))
	{
		adjustBalanceFactors(ancestor, newNode);// ����ƽ������
		ancestor->nodemark = 'E'; // ����ancestorƽ������
		ancestor->right->nodemark = 'E';//����ancestor����ƽ������
		rotateLeft(ancestor); // ����
	}
	//LL�Ͳ�ƽ�⣬��Ҫ����
	else if ((ancestor->nodemark == 'L') && (newNode->key < ancestor->left->key))
	{
		adjustBalanceFactors(ancestor, newNode);// ����ƽ������
		ancestor->nodemark = 'E'; // ����ancestorƽ������
		ancestor->left->nodemark = 'E';//����ancestor����ƽ������
		rotateRight(ancestor); // ����
	}
	//LR�ͣ���Ҫ������
	else if ((ancestor->nodemark == 'L') && (newNode->key > ancestor->left->key))
	{
		adjustBalanceFactors(ancestor, newNode);// ����ƽ������
		//����Ϊ����3���ڵ��ƽ������
		if (newNode->key == ancestor->left->right->key)//������ancestorֻ��һ�����
		{
			newNode->nodemark = 'E';
			ancestor->nodemark = 'E';
			ancestor->left->nodemark = 'E';
		}
		else if (newNode->key < ancestor->left->right->key)
		{
			ancestor->left->right->nodemark = 'E';
			ancestor->nodemark = 'R';
			ancestor->left->nodemark = 'E';
		}
		else
		{
			ancestor->left->right->nodemark = 'E';
			ancestor->nodemark = 'E';
			ancestor->left->nodemark = 'L';
		}
		// ����ancestor������������������ancestor����
		rotateLeft(ancestor->left);
		rotateRight(ancestor);
	}
	//RL�ͣ�������
	else
	{
		adjustBalanceFactors(ancestor, newNode);// ����ƽ������
		//����Ϊ����3���ڵ��ƽ������
		if (newNode->key == ancestor->right->left->key)//������ancestorֻ��һ�����
		{
			newNode->nodemark = 'E';
			ancestor->nodemark = 'E';
			ancestor->right->nodemark = 'E';
		}
		else if (newNode->key < ancestor->right->left->key)
		{
			ancestor->right->left->nodemark = 'E';
			ancestor->nodemark = 'E';
			ancestor->right->nodemark = 'R';
		}
		else
		{
			ancestor->right->left->nodemark = 'E';
			ancestor->nodemark = 'L';
			ancestor->right->nodemark = 'E';
		}
		// ����ancestor������������������ancestor����
		rotateRight(ancestor->right);
		rotateLeft(ancestor);
	}
}

//���¶��ϵ���ƽ�����ӣ�������������һ��
// end :Ϊ����������Ĳ�ƽ��Ľڵ㣨ƽ�����Ӳ���"E"��
// start :�²���Ľڵ�

void AVLTree::adjustBalanceFactors(AVLTreeNode *end, AVLTreeNode *start)//���¶��ϵĵ���ƽ�����ӣ�QAQ�鷳��
{
	AVLTreeNode *temp = start->parent; // tempָ��start�ĸ���
	while (temp != end)
	{
		if (start->key < temp->key)
			temp->nodemark = 'L';
		else
			temp->nodemark = 'R';
		temp = temp->parent;
	}
}

// rotateLeft(),����
// n��Ϊ��ƽ��ڵ�
void AVLTree::rotateLeft(AVLTreeNode *n)
{
	 AVLTreeNode *temp = n->right; //ָ��n��������
	 n->right = temp->left; // n������ָ��temp������
	 if (temp->left != NULL) // ���temp����������
		temp->left->parent = n;// �͸������ĸ�ָ��
	if (n->parent == NULL) // ���n������
	{
		root = temp; // temp�ͳ����µ�����
		
	}
	//����n���и��׵����
	else if (n->parent->left == n) // ���n�������׵�����
		n->parent->left = temp; // temp�ͳ�������
	else // ���n�������׵��Һ���
		n->parent->right = temp; // temp�ͳ����Һ���
	temp->parent = n->parent; //����temp�ĸ�ָ��
	temp->left = n; // n��Ϊtemp������
	n->parent = temp; //temp��Ϊn�ĸ���
}

// rotateRight(),������nΪ��ƽ����
void AVLTree::rotateRight(AVLTreeNode *n)
{
	AVLTreeNode *temp = n->left;
	n->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = n;
	if (n->parent == NULL)
	{
		root = temp;
	}
	else if (n->parent->left == n)
		n->parent->left = temp;
	else
		n->parent->right = temp;
	temp->parent = n->parent;
	temp->right = n;
	n->parent = temp;
}

//����ת90�����ͼ��
void AVLTree::graph()
{
	cout << "----------------------------------------\n";
	graphAux(root, 0);
	cout << "----------------------------------------\n";
}

void AVLTree::graphAux(AVLTreeNode *subtree, int a)
{
	if (NULL != subtree)
	{

		graphAux(subtree->right, a + 8);
		cout << setw(a) << " " << subtree->key << endl;
		//cout << setw(a) << " " << subtree->key << " " << subtree->balanceFactor << endl;
		//                                                                                                                                                                                              cout << setw(a) << " " << subtree->key;
		//if (subtree->parent != 0)
		//	cout <<"("<<subtree->parent->key<<")"<< endl;
		graphAux(subtree->left, a + 8);
	}
}

//�������
void AVLTree::inOrder(ofstream & fs)
{
	inOrderAux(fs, root);
}


void AVLTree::inOrderAux(ofstream & fs, AVLTreeNode *subtree)
{
	if (0 != subtree)
	{
		inOrderAux(fs, subtree->left);
		fs << subtree->key.username << " " << subtree->key.password << endl;
		inOrderAux(fs, subtree->right);
	}
}
//����Ԫ�أ����ص�ַ��������NULL
AVLTreeNode* AVLTree::find(UserInfo target)
{
	AVLTreeNode *cur = root;
	while (cur != 0)
	{
		if (target < cur->key)
			cur = cur->left;
		else if (target > cur->key)
			cur = cur->right;
		else
		{
			return cur;
		}
	}
	return cur;
}
//�ҵ�ɾ������λ�ú����ĸ���
//data:��ɾ�����ݣ� found:�Ƿ��ҵ�
//x:����dataλ�ã� parent:x����
void AVLTree::searchCur(const UserInfo &node, bool &found, AVLTreeNode *&x, AVLTreeNode*&parent)//remove��������
{
	while (!found && x != 0)//�ҵ����ߵ�Ҷ�Ӿ�ֹͣ
	{
		if (node < x->key)
		{
			parent = x;
			x = x->left;
		}
		else if (node > x->key)
		{
			parent = x;
			x = x->right;
		}
		
		else
		{
			found = true;
		}
	}
}

//ɾ��Ԫ��
void AVLTree::remove(UserInfo key)
{
	bool found = false;
	AVLTreeNode *x = root;//����Ҫɾ��Ԫ��λ��
	AVLTreeNode *parent = 0;//x�ĸ���
	searchCur(key, found, x, parent);//��λҪɾ��Ԫ��,�Ҳ�����foundΪfalse
	if (!found)
	{
		cerr << "�޴�Ԫ��" << key << "����ɾ��\n";
		return;
	}
	//���������ӵ����
	if (x->left != 0 && x->right != 0)
	{
		parent = x;
		AVLTreeNode *Lmin = x->right;//Ѱ��x������������С��һ��
		while (Lmin->left != 0)//����ֱ���ж�xSucc�Ƿ�Ϊ��
		{
			parent = Lmin;//���׽�������
			Lmin = Lmin->left;
		}
		x->key = Lmin->key;//���ҵ����������е���Сֵ����x
		x = Lmin;//Ȼ��ɾ�������ת��
	}
	//Ҫɾ��Ԫ���޻�ֻ��һ�����ӵ����
	AVLTreeNode *subtree = x->left;//x������
	bool left = false;//�ж�ɾ����������������������
	if (x->left == 0)
	{
		subtree = x->right;
	}
	if (parent == 0)//����ɾ��
	{
		root = subtree;
	}
	else if (parent->left == x)
	{
		parent->left = subtree;
		left = true;
	}
	else
	{
		parent->right = subtree;
	}
	delete x;//��Ҫ����ɾ�����
	restoreAVLDelete(parent, left);
}

//���Ҳ�ƽ��㣬����ƽ�����ӣ�������ת
//start:��start���ϲ��Ҳ�ƽ���
//left :bool�ͣ����start���������򷵻�true

void AVLTree::restoreAVLDelete(AVLTreeNode *start, bool left)
{
	//�ѵ�����
	if (start == 0)
		return;
	//ԭ��ƽ������Ϊ0����Ӱ��ǰ��ƽ����
	else if (start->nodemark == 'E')
	{
		if (left)
			start->nodemark = 'R';
		else
			start->nodemark = 'L';
	}
	//������ƽ����������ʱ��Ҫ�����Ҳ�ƽ���
	else if ((left && start->nodemark == 'L') || (!left && start->nodemark == 'R'))
	{
		start->nodemark = 'E';
		if (start->parent != 0 && start->parent->left == start)
			left = true;
		else
			left = false;
		restoreAVLDelete(start->parent, left);
	}
	//start��ƽ������Ϊ-1�����
	else if (start->nodemark == 'R')
	{
		if (start->right->nodemark == 'E')
		{
			rotateLeft(start);
		}
		else if (start->right->nodemark == 'R')
		{
			start->nodemark = 'E';
			rotateLeft(start);
			if (start->parent->parent != 0 && start->parent->parent->left == start)
				left = true;
			else
				left = false;
			restoreAVLDelete(start->parent, left);
		}
		else
		{
			AVLTreeNode *temp = start->right->left;
			//����Ϊ��תǰ���������ڵ��ƽ������
			if (temp->nodemark == 'E')
				start->nodemark = start->right->nodemark = 'E';
			else if (temp->nodemark == 'L')
			{
				start->nodemark = 'E';
				start->right->nodemark = 'R';
			}
			else
			{
				start->nodemark = 'L';
				start->right->nodemark = 'E';
			}
			rotateRight(start->right);
			rotateLeft(start);
			if (temp->parent != 0 && temp->parent->left == start)
				left = true;
			else
				left = false;
			restoreAVLDelete(temp->parent, left);//��������Ѱ�Ҳ�ƽ��
		}
	}
	//start��ƽ������Ϊ1�����
	else
	{
		if (start->left->nodemark == 'E')
		{
			rotateRight(start);
		}
		else if (start->left->nodemark == 'L')
		{
			start->nodemark = 'E';
			rotateRight(start);
			if (start->parent->parent != 0 && start->parent->parent->left == start)
				left = true;
			else
				left = false;
			restoreAVLDelete(start->parent, left);
		}
		else
		{
			AVLTreeNode *temp = start->left->right;
			//����Ϊ��תǰ���������ڵ��ƽ������
			if (temp->nodemark == 'E')
				start->nodemark = start->right->nodemark = 'E';
			else if (temp->nodemark == 'L')
			{
				start->nodemark = 'R';
				start->left->nodemark = 'E';
			}
			else
			{
				start->nodemark = 'E';
				start->left->nodemark = 'L';
			}
			rotateLeft(start->left);
			rotateRight(start);
			if (temp->parent != 0 && temp->parent->left == start)
				left = true;
			else
				left = false;
			restoreAVLDelete(temp->parent, left);//��������Ѱ�Ҳ�ƽ��
		}
	}
}