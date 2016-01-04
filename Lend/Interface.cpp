#include"Interface.h"

//���캯������ȡ�ļ�������
Interface::Interface()
{
	//���ļ��ж�ȡ��Ϣ
	ifstream openfile("database.txt", ios::in);
	if (!openfile)
	{
		cerr << "�޷����ļ�������\n";
		return;
	}
	//new��һ�����ڵ�
	data = new AVLTree();//rootΪnull
	string name;
	string  pass,s;
	openfile >> s >> pass;
	while (openfile >> name >> pass)
	{
		UserInfo info(name, pass);
		AVLTreeNode *node = new AVLTreeNode(info);//����һ���µĽ��
		data->insert(node);//���µĽ�����AVL����
	}
	data->graph();
	mainFace();//����
}
void Interface::mainFace()
{
	while (true)
	{
		system("color 71");
		cout << "\t\t----------------------------------------\n";
		cout << "\t\t\t\t1.��½��֤\n";
		cout << "\t\t\t\t2.����û�\n";
		cout << "\t\t\t\t3.ɾ���û�\n";
		cout << "\t\t\t\t4.�޸�����\n";
		cout << "\t\t\t\t0.�˳�\n";
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
			cout << "��ӭ����ʹ��!"<<endl;
			return;
			break;
		default:
			cerr << "���벻��ȷ������������\n";
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
		cout << "�������˺ţ�\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		
		cout << "----------------------------------------\n";
		cout << "��������λ���룺  ��0 0�����ϼ���\n";
		cout << "----------------------------------------\n";
		char c;
		//����ı����ԣ��õ���_getch()����
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
			cerr << "�û���������,����������\n";
			system("pause");
			system("cls");
		}
		else if (nodeFound->key.password != temp.password)
		{
			cerr << "�������,����������\n";
			system("pause");
			system("cls");
		}
		else
		{
			cout << "��½�ɹ���\n";
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
		cout << "������Ҫ��ӵ��˺ţ�\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		cout << "----------------------------------------\n";
		cout << "������Ҫ��ӵ���λ���룺 (0 0 �����ϼ�)\n";
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
			cerr << "���˺��Ѵ��ڣ�����������\n";
			system("pause");
			system("cls");
			continue;
		}
		else
		{
			AVLTreeNode* tempNode = new AVLTreeNode(temp);
			data->insert(tempNode);
			cout << "��ӳɹ��������������\n";
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
		cout << "������Ҫɾ�����˺ţ�\n";
		cout << "----------------------------------------\n";
		UserInfo temp;
		cin >> temp.username;
		cout << "----------------------------------------\n";
		cout << "������Ҫɾ���˺ŵ���λ���룺 ��0 0�����ϼ���\n";
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
			cerr << "�û���������,����������\n";
			system("pause");
			system("cls");
		}
		else if (nodeFound->key.password != temp.password)
		{
			cerr << "�������,����������\n";
			system("pause");
			system("cls");
		}
		else
		{
			data->remove(temp);
			cout << "ɾ���ɹ���\n";
			system("pause");
			system("cls");
			return;
		}
	}
}
void Interface::update()
{
	cout << "----------------------------------------\n";
	cout << "������Ҫ���µ��˺ţ�\n";
	cout << "----------------------------------------\n";
	UserInfo temp;
	cin >> temp.username;
	cout << "----------------------------------------\n";
	cout << "������ɵ����룺\n";
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
		cerr << "�û���������,����������\n";
		system("pause");
		system("cls");
	}
	else if (nodeFound->key.password != temp.password)
	{
		cerr << "�������,����������\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "�������µ���λ����\n";
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
		cout << "�޸ĳɹ���\n";
		system("pause");
		system("cls");
		return;
	}
}
Interface::~Interface()
{
	//���޸ĺ����Ϣ������ļ��У��ر��ļ�
	ofstream closefile("database.txt",ios::out);
	closefile << "�˺� " <<"����"<< endl;
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