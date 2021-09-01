#include "Manager.h"
#include<fstream>
#include "globalFile.h"
#include<algorithm>

void printStus(Student& stu);
void printTchs(Teacher& tch);

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
}

void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： ";
}

void Manager::addUser()
{
	cout << "请输入你要添加账号的类型（1.学生，2.教师）：";
	int temp_choose = 0;
	cin >> temp_choose;
	if (temp_choose == 1)
	{
		int id;
		string name;
		string pwd;
		while (true)
		{
			cout << "请输入学生id：";
			cin >> id;
			if (!checkRepeat(id, temp_choose))
			{
				break;
			}
			cout << "学生id重复，请重新输入！" << endl;
		}
		cout << "请输入学生账号：";
		cin >> name;
		cout << "请输入学生密码：";
		cin >> pwd;
		// 追加写入到教师文件中
		ofstream ofs;
		// 指定追加写入方式
		ofs.open(STUDENT_FILE, ios::out | ios::app);
		ofs << id << ' ' << name << ' ' << pwd << endl;
		cout << "学生 " << name << " 添加成功！" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	else if (temp_choose == 2)
	{
		int id;
		string name;
		string pwd;
		while (true)
		{
			cout << "请输入教师编号：";
			cin >> id;
			if (!checkRepeat(id, temp_choose))
			{
				break;
			}
			cout << "教师编号重复，请重新输入！" << endl;
		}
		cout << "请输入教师账号：";
		cin >> name;
		cout << "请输入教师密码：";
		cin >> pwd;
		ofstream ofs;
		// 指定追加写入方式
		ofs.open(TEACHER_FILE, ios::out | ios::app);
		ofs << id << ' ' << name << ' ' << pwd << endl;
		cout << "教师 " << name << " 添加成功！" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入有误，请重新输入！" << endl;
		system("pause");
		system("cls");
	}
	// 每次添加完用户后，更新容器
	this->initVector();
}

void Manager::showUser()
{
	cout << "请选择要展示的对象（1.学生，2.老师）：";
	int choose;
	cin >> choose;
	if (choose == 1)
	{
		cout << "当前的学生数量是：" << stus.size() << endl;
		for_each(stus.begin(), stus.end(), printStus);
	}
	else
	{
		cout << "当前的老师数量是：" << tchs.size() << endl;
		for_each(tchs.begin(), tchs.end(), printTchs);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "机房的数量为：" << comps.size() << endl;
	for (int i = 0; i < comps.size(); i++)
	{
		cout << "机房编号为：" << comps[i].m_id << "\t机房的容量为：" << comps[i].m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "预约记录清空成功！" << endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	// 读取老师文件
	ifstream ifs;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << TEACHER_FILE << "文件不存在" << endl;
		return;
	}
	// 每次读取前先清空容器中内容
	tchs.clear();
	Teacher tch;
	while ((ifs >> tch.m_id) && (ifs >> tch.m_Name) && (ifs >> tch.m_Pwd))
	{
		// push_back时调用 Teacher的拷贝构造，传进去的是一个全新的变量
		tchs.push_back(tch);
	}
	ifs.close();

	// 读取学生文件
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << STUDENT_FILE << "文件不存在" << endl;
		return;
	}
	// 每次读取前先清空容器中内容
	stus.clear();
	Student stu;
	while ((ifs >> stu.m_id) && (ifs >> stu.m_Name) && (ifs >> stu.m_Pwd))
	{
		// push_back时调用 Teacher的拷贝构造，传进去的是一个全新的变量
		stus.push_back(stu);
	}
	ifs.close();

	// 读取机房信息
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << COMPUTER_FILE << "文件不存在" << endl;
		return;
	}
	comps.clear();
	computerRoom comp;
	while ((ifs >> comp.m_id) && (ifs >> comp.m_maxNum))
	{
		comps.push_back(comp);
	}
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	// 老师
	if (type == 2)
	{
		for (vector<Teacher>::iterator it = this->tchs.begin(); it != this->tchs.end(); it++)
		{
			if (it->m_id == id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Student>::iterator it = this->stus.begin(); it != this->stus.end(); it++)
		{
			if (it->m_id == id)
			{
				return true;
			}
		}
	}
	return false;
}

void printStus(Student& stu)
{
	cout << "学生的id是：" << stu.m_id << "\t账号是：" << stu.m_Name << "\t密码是：" << stu.m_Pwd << endl;
}

void printTchs(Teacher& tch)
{
	cout << "教师的编号是：" << tch.m_id << "\t账号是：" << tch.m_Name << "\t密码是：" << tch.m_Pwd << endl;
}