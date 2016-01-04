#include"AVLTree.h"
#include <fstream>

AVLTree::AVLTree()//构造函数
{
	root = NULL; 
}

AVLTree::~AVLTree()//析构函数
{

	ClearTree(root);
}

void AVLTree::ClearTree(AVLTreeNode *n)
{
	if (n != NULL)
	{
		ClearTree(n->left);//释放左子树
		ClearTree(n->right);//释放右子树
		delete n;
	}
}
//插入结点的函数
void AVLTree::insert(AVLTreeNode *newNode)
{
	AVLTreeNode *temp, *back, *ancestor;
	temp = root;
	back = NULL;
	ancestor = NULL;
	// 是空树的话直接设为根节点
	if (root == NULL)
	{
		root = newNode;
		return;
	}

	while (temp != NULL) // 从树根遍历直至NULL
	{
		back = temp;//back是插入结点的父节点
			// 查找ancestor，ancestor 为离插入点最近的不平衡的节点（平衡因子不是"E"）
			// 新节点被插入
		if (temp->nodemark != 'E')
			ancestor = temp;
		if (newNode->key < temp->key)
			temp = temp->left;
		else if (newNode->key > temp->key)
			temp = temp->right;
		else
		{
			return;//相等的结点是不插入的
		}
	}
	// temp已经为空
	// back 为新插入节点的父亲
	newNode->parent = back; // 先让back指向它父亲
	if (newNode->key < back->key) // 插入左子树
	{
		back->left = newNode;
	}
	else // 插入右子树
	{
		back->right = newNode;
	}
	// 调用restoreAVLInsert成员函数重新平衡该树
	restoreAVLInsert(ancestor, newNode);
}
//插入后调整平衡性
void AVLTree::restoreAVLInsert(AVLTreeNode *ancestor, AVLTreeNode *newNode)
{
     //插入不影响平衡性
	if (ancestor == NULL)
	{
		if (newNode->key < root->key) // 调整根的平衡因子
			root->nodemark = 'L';
		else
			root->nodemark = 'R';
		// 调整平衡因子
		adjustBalanceFactors(root, newNode);
	}

	//  ancestor 存在，但不影响平衡性的情况
	// ancestor.balanceFactor = 'L' 且新插入点插入到右子树  或者

	// ancestor.balanceFactor = 'R' 且新插入点插入到左子树

	else if (((ancestor->nodemark == 'L') && (newNode->key > ancestor->key)) ||
		((ancestor->nodemark == 'R') && (newNode->key < ancestor->key)))
	 {
		ancestor->nodemark = 'E';
		// 调整平衡因子
		adjustBalanceFactors(ancestor, newNode);
	 } 
	//RR型不平衡，需要左旋
	else if ((ancestor->nodemark == 'R') && (newNode->key > ancestor->right->key))
	{
		adjustBalanceFactors(ancestor, newNode);// 调整平衡因子
		ancestor->nodemark = 'E'; // 重设ancestor平衡因子
		ancestor->right->nodemark = 'E';//重设ancestor右子平衡因子
		rotateLeft(ancestor); // 左旋
	}
	//LL型不平衡，需要右旋
	else if ((ancestor->nodemark == 'L') && (newNode->key < ancestor->left->key))
	{
		adjustBalanceFactors(ancestor, newNode);// 调整平衡因子
		ancestor->nodemark = 'E'; // 重设ancestor平衡因子
		ancestor->left->nodemark = 'E';//重设ancestor左子平衡因子
		rotateRight(ancestor); // 右旋
	}
	//LR型，需要左右旋
	else if ((ancestor->nodemark == 'L') && (newNode->key > ancestor->left->key))
	{
		adjustBalanceFactors(ancestor, newNode);// 调整平衡因子
		//以下为调整3个节点的平衡因子
		if (newNode->key == ancestor->left->right->key)//插入点和ancestor只有一个间隔
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
		// 先让ancestor的左子树左旋，再让ancestor右旋
		rotateLeft(ancestor->left);
		rotateRight(ancestor);
	}
	//RL型，右左旋
	else
	{
		adjustBalanceFactors(ancestor, newNode);// 调整平衡因子
		//以下为调整3个节点的平衡因子
		if (newNode->key == ancestor->right->left->key)//插入点和ancestor只有一个间隔
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
		// 先让ancestor的右子树右旋，再让ancestor右旋
		rotateRight(ancestor->right);
		rotateLeft(ancestor);
	}
}

//自下而上调整平衡因子，但不包括最上一个
// end :为离插入点最近的不平衡的节点（平衡因子不是"E"）
// start :新插入的节点

void AVLTree::adjustBalanceFactors(AVLTreeNode *end, AVLTreeNode *start)//自下而上的调整平衡因子，QAQ麻烦啊
{
	AVLTreeNode *temp = start->parent; // temp指向start的父亲
	while (temp != end)
	{
		if (start->key < temp->key)
			temp->nodemark = 'L';
		else
			temp->nodemark = 'R';
		temp = temp->parent;
	}
}

// rotateLeft(),左旋
// n：为不平衡节点
void AVLTree::rotateLeft(AVLTreeNode *n)
{
	 AVLTreeNode *temp = n->right; //指向n的右子树
	 n->right = temp->left; // n右子树指向temp左子树
	 if (temp->left != NULL) // 如果temp左子树存在
		temp->left->parent = n;// 就更新它的父指针
	if (n->parent == NULL) // 如果n是树根
	{
		root = temp; // temp就成了新的树根
		
	}
	//处理n还有父亲的情况
	else if (n->parent->left == n) // 如果n是它父亲的左孩子
		n->parent->left = temp; // temp就成了左孩子
	else // 如果n是它父亲的右孩子
		n->parent->right = temp; // temp就成了右孩子
	temp->parent = n->parent; //更新temp的父指针
	temp->left = n; // n成为temp的左孩子
	n->parent = temp; //temp成为n的父亲
}

// rotateRight(),右旋，n为不平衡结点
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

//左旋转90度输出图形
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

//中序遍历
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
//查找元素，返回地址，否则是NULL
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
//找到删除结点的位置和他的父亲
//data:待删除数据， found:是否找到
//x:返回data位置， parent:x父亲
void AVLTree::searchCur(const UserInfo &node, bool &found, AVLTreeNode *&x, AVLTreeNode*&parent)//remove辅助函数
{
	while (!found && x != 0)//找到或者到叶子就停止
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

//删除元素
void AVLTree::remove(UserInfo key)
{
	bool found = false;
	AVLTreeNode *x = root;//保存要删除元素位置
	AVLTreeNode *parent = 0;//x的父亲
	searchCur(key, found, x, parent);//定位要删除元素,找不到则found为false
	if (!found)
	{
		cerr << "无此元素" << key << "不能删除\n";
		return;
	}
	//有两个孩子的情况
	if (x->left != 0 && x->right != 0)
	{
		parent = x;
		AVLTreeNode *Lmin = x->right;//寻找x的右子树中最小的一个
		while (Lmin->left != 0)//不能直接判断xSucc是否为空
		{
			parent = Lmin;//父亲紧跟儿子
			Lmin = Lmin->left;
		}
		x->key = Lmin->key;//把找到的右子树中的最小值赋给x
		x = Lmin;//然后删除右最大，转化
	}
	//要删除元素无或只有一个儿子的情况
	AVLTreeNode *subtree = x->left;//x的子树
	bool left = false;//判断删除的是左子树还是右子树
	if (x->left == 0)
	{
		subtree = x->right;
	}
	if (parent == 0)//根被删除
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
	delete x;//不要忘记删除结点
	restoreAVLDelete(parent, left);
}

//查找不平衡点，更新平衡因子，并且旋转
//start:从start向上查找不平衡点
//left :bool型，如果start是左子树则返回true

void AVLTree::restoreAVLDelete(AVLTreeNode *start, bool left)
{
	//已到根部
	if (start == 0)
		return;
	//原来平衡因子为0，不影响前面平衡性
	else if (start->nodemark == 'E')
	{
		if (left)
			start->nodemark = 'R';
		else
			start->nodemark = 'L';
	}
	//又正好平衡的情况，此时还要向上找不平衡点
	else if ((left && start->nodemark == 'L') || (!left && start->nodemark == 'R'))
	{
		start->nodemark = 'E';
		if (start->parent != 0 && start->parent->left == start)
			left = true;
		else
			left = false;
		restoreAVLDelete(start->parent, left);
	}
	//start的平衡因子为-1的情况
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
			//下面为旋转前调整三个节点的平衡因子
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
			restoreAVLDelete(temp->parent, left);//继续向上寻找不平衡
		}
	}
	//start的平衡因子为1的情况
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
			//下面为旋转前调整三个节点的平衡因子
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
			restoreAVLDelete(temp->parent, left);//继续向上寻找不平衡
		}
	}
}