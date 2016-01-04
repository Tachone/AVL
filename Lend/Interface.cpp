#include"Interface.h"

//构造函数，读取文件，建树
Interface::Interface()
{
	//从文件中读取信息
	ifstream openfile("database.txt", ios::in);
	if (!openfile)
	{
		cerr << "无法打开文件，请检查\n";
		return;
	}
	//new出一个根节点
	data = new AVLTree();//root为null
	string name;
	string  pass,s;
	openfile >> s >> pass;
	while (openfile >> name >> pass)
	{
		UserInfo info(name, pass);
		AVLTreeNode *node = new AVLTreeNode(info);//创建一个新的结点
		data->insert(node);//将新的结点插入AVL树中
	}
	data->graph();
	mainFace();//界面
}
void Interface::mainFace()
{
	while (true)
	{
		system("color 71");
		cout << "\t\t----------------------------------------\n";
		cout << "\t\t\t\t1.登陆验证\n";
		cout << "\t\t\t\t2.添加用户\n";
		cout << "\t\t\t\t3.删除用户\n";
		cout << "\t\t\t\t4.修改密码\n";
		cout << "\t\t\t\t0.退出\n";
		cout << "\t\t----------------------------------------\n";
		
		int choose;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:logIn();
			break;
		case 2:addUser();
			data->graph();
			break;
		case 3:removeUser();
			data->graph();
			break;
		case 4:update();
			break;
		case 0:
			cout << "欢迎您的使用!"<<endl;
			return;
			break;
		default:
			cerr << "输入不正确，请重新输入\n";
			system("pause");
			system("cls");
			break;
		}
	}
}
void Interface::logIn()
{
	while (true)
	{
		cout << "----------------------------------------\n";
		cout << "请输入账号：\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		
		cout << "----------------------------------------\n";
		cout << "请输入六位密码：  （0 0返回上级）\n";
		cout << "----------------------------------------\n";
		char c;
		//密码的保密性，用到了_getch()函数
		for (int i = 0; i <= 5; i++)
		{
			c = _getch();
			cout << "*";
			temp.password += c;
		}
		system("cls");
		if (temp.username == "0" && temp.password == "0")
			return;
		AVLTreeNode *nodeFound = 0;
		nodeFound = data->find(temp);
		if (nodeFound == 0)
		{
			cerr << "用户名不存在,请重新输入\n";
			system("pause");
			system("cls");
		}
		else if (nodeFound->key.password != temp.password)
		{
			cerr << "密码错误,请重新输入\n";
			system("pause");
			system("cls");
		}
		else
		{
			cout << "登陆成功！\n";
			system("pause");
				system("cls");
			return;
		}
	}
}
void Interface::addUser()
{
	while (true)
	{
		cout << "----------------------------------------\n";
		cout << "请输入要添加的账号：\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		cout << "----------------------------------------\n";
		cout << "请输入要添加的六位密码： (0 0 返回上级)\n";
		cout << "----------------------------------------\n";
		char c;
		for (int i = 0; i <= 5; i++)
		{
			c = _getch();
			cout << "*";
			temp.password += c;
		}
		system("cls");
		if (temp.username == "0" && temp.password == "0")
			return;
		if (data->find(temp) != 0)
		{
			cerr << "此账号已存在，请重新输入\n";
			system("pause");
			system("cls");
			continue;
		}
		else
		{
			AVLTreeNode* tempNode = new AVLTreeNode(temp);
			data->insert(tempNode);
			cout << "添加成功！按任意键返回\n";
			system("pause");
			system("cls");
			return;
		}
	}
}
void Interface::removeUser()
{
	while (true)
	{
		cout << "----------------------------------------\n";
		cout << "请输入要删除的账号：\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		cout << "----------------------------------------\n";
		cout << "请输入要删除账号的六位密码： （0 0返回上级）\n";
		cout << "----------------------------------------\n";
		char c;
		for (int i = 0; i <= 5; i++)
		{
			c = _getch();
			cout << "*";
			temp.password += c;
		}
		system("cls");
		if (temp.username == "0" && temp.password == "0")
			return;
		AVLTreeNode *nodeFound = 0;
		nodeFound = data->find(temp);
		if (nodeFound == 0)
		{
			cerr << "用户名不存在,请重新输入\n";
			system("pause");
			system("cls");
		}
		else if (nodeFound->key.password != temp.password)
		{
			cerr << "密码错误,请重新输入\n";
			system("pause");
			system("cls");
		}
		else
		{
			data->remove(temp);
			cout << "删除成功！\n";
			system("pause");
			system("cls");
			return;
		}
	}
}
void Interface::update()
{
	cout << "----------------------------------------\n";
	cout << "请输入要更新的账号：\n";
	cout << "----------------------------------------\n";
	UserInfo temp;
	cin >> temp.username;
	cout << "----------------------------------------\n";
	cout << "请输入旧的密码：\n";
	cout << "----------------------------------------\n";
	char c;
	for (int i = 0; i <= 5; i++)
	{
		c = _getch();
		cout << "*";
		temp.password += c;
	}
	system("cls");
	if (temp.username == "0" && temp.password == "0")
		return;
	AVLTreeNode *nodeFound = 0;
	nodeFound = data->find(temp);
	if (nodeFound == 0)
	{
		cerr << "用户名不存在,请重新输入\n";
		system("pause");
		system("cls");
	}
	else if (nodeFound->key.password != temp.password)
	{
		cerr << "密码错误,请重新输入\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入新的六位密码\n";
		string newTemp;
		char c;
		for (int i = 0; i <= 5; i++)
		{
			c = _getch();
			cout << "*";
			newTemp += c;
		}
		nodeFound->key.password = newTemp;
		cout << endl;
		cout << "修改成功！\n";
		system("pause");
		system("cls");
		return;
	}
}
Interface::~Interface()
{
	//将修改后的信息保存进文件中，关闭文件
	ofstream closefile("database.txt",ios::out);
	closefile << "账号 " <<"密码"<< endl;
	data->inOrder(closefile);
	closefile.close();
}


/*void Interface::test()
{
	AVLTreeNode* temp;
	AVLTree a;
	long long int n[20];
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		n[i] = rand() % 1000;
		temp = new AVLTreeNode(UserInfo(n[i]));
		a.insert(temp);
	}
	a.graph();
}*/