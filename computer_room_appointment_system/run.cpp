#include<iostream>
#include<string>
#include<fstream>
#include "Identity.h"
#include "globalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "Manager.h"
using namespace std;

void login(string file_name, int type);
void managerMenu(Identity*& manager);
void studentMenu(Identity*& student);
void teacherMenu(Identity*& teacher);

void show_menu()
{
	cout << "======================  欢迎来到机房预约系统  ====================="
		<< endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.学生代表           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.老    师           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.管 理 员           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.退    出           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "输入您的选择: ";
}

// 用户选择
void select_user()
{
	int choose;
	cin >> choose;
	switch (choose)
	{
	case 1:
		login(STUDENT_FILE, 1);
		break;
	case 2:
		login(TEACHER_FILE, 2);
		break;
	case 3:
		login(MANAGER_FILE, 3);
		break;
	case 0:
	{
		cout << "即将退出系统！" << endl;
		system("pause");
		system("cls");
		exit(0); 
	}
		break;
	default:
		cout << "输入有误，请重新选择！" << endl;
		break;
	}

}

// 执行登录
void login(string file_name, int type)
{
	// 实例化父类指针，指向登录成功后的不同子类对象
	Identity* person = NULL;
	// 根据filename查看对应账号密码文件是否存在
	ifstream ifs;
	ifs.open(file_name, ios::in);
	if (!ifs.is_open())
	{
		cout << file_name << "文件不存在!" << endl;
		ifs.close();
		return;
	}
	int id;
	string name;
	string pwd;
	// 读取用户文件中的账号密码
	int fid;
	string fname;
	string fpwd;
	int flag = 0;
	switch (type)
	{
	case 1:
	{
		cout << "请输入学生id：";
		cin >> id;
		cout << "请输入账号：";
		cin >> name;
		cout << "请输入密码：";
		cin >> pwd;
		// 判断登陆是否成功
		// 从ifs中读数据，循环一次读一行，空格标志一列数据结束
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if ((fid == id) && (fname == name) && (fpwd == pwd))
			{
				cout << "学生 " << name << " 登陆成功！" << endl;
				flag = 1;
				system("pause");
				system("cls");
				// 将当前登录对象开辟到堆区，将返回的指针传给父类的person对象
				person = new Student(id, name, pwd);
				// 进入学生用户操作界面，以当前学生身份进行操作
				studentMenu(person);
				// 当学生用户退出登录，返回到主菜单界面
				delete person;
				return;
			}
		}
		if (flag == 0)
		{
			cout << "账号密码错误，请重新输入！" << endl;
		}
	}
	break;
	case 2:
	{
		cout << "请输入教师编号：";
		cin >> id;
		cout << "请输入账号：";
		cin >> name;
		cout << "请输入密码：";
		cin >> pwd;
		// 判断登陆是否成功
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if ((fid == id) && (fname == name) && (fpwd == pwd))
			{
				cout << "教师 " << name << " 登陆成功！" << endl;
				system("pause");
				system("cls");
				// 将当前登录对象开辟到堆区，将返回的指针传给父类的person对象
				person = new Teacher(id, name, pwd);
				// 进入教师用户操作界面，以当前教师身份进行操作
				teacherMenu(person);
				// 当教师用户退出登录，返回到主菜单界面
				delete person;
				return;
			}
		}
		if (flag == 0)
		{
			cout << "账号密码错误，请重新输入！" << endl;
		}
	}
	break;
	case 3:
	{
		cout << "请输入管理员账号：";
		cin >> name;
		cout << "请输入管理员密码：";
		cin >> pwd;
		// 判断登陆是否成功
		while (ifs >> fname && ifs >> fpwd)
		{
			if ((fname == name) && (fpwd == pwd))
			{
				cout << "管理员 " << name << " 登陆成功！" << endl;
				system("pause");
				system("cls");
				// 将当前登录对象开辟到堆区，将返回的指针传给父类的person对象
				person = new Manager(name, pwd);
				// 进入管理员用户操作界面，以当前管理员身份进行操作
				managerMenu(person);
				// 当管理员用户退出登录，返回到主菜单界面
				// 手动释放堆区变量
				delete person;
				return;
			}
			else
			{
				cout << "账号密码错误，请重新输入！" << endl;
			}
		}
		if (flag == 0)
		{
			cout << "账号密码错误，请重新输入！" << endl;
		}
	}
	break;
	default:
		break;
	}
}

// 添加管理员登录成功后操作界面的全局函数
// 传入一个父类的指针引用
void managerMenu(Identity*& manager)
{
	while (true)
	{
		// 展示manager菜单
		manager->operMenu();
		int choose;
		cin >> choose;
		// 强转父类指针指向的子类对象为子类指针，否则该指针只能调用父类方法，强转后可调用子类独有方法
		Manager* mag = (Manager*)manager;
		switch (choose)
		{
		case 1:
			mag->addUser();
			break;
		case 2:
			mag->showUser();
			break;
		case 3:
			mag->showComputer();
			break;
		case 4:
			mag->clearFile();
			break;
		case 0:
			cout << "即将退出登录！" << endl;
			return;
		default:
			break;
		}
	}
}


void studentMenu(Identity*& student)
{
	while (true)
	{
		student->operMenu();
		int choose;
		cin >> choose;
		Student* stu = (Student*)student;
		switch (choose)
		{
		case 1:
			stu->applyOrder();
			break;
		case 2:
			stu->showMyOrder();
			break;
		case 3:
			stu->showAllOrder();
			break;
		case 4:
			stu->cancleOrder();
			break;
		case 0:
			cout << "即将退出登录！" << endl;
			return;
		default:
			break;
		}
	}
}

void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();
		int choose;
		cin >> choose;
		Teacher* tea = (Teacher*)teacher;
		switch (choose)
		{
		case 1:
			tea->showAllOrder();
			break;
		case 2:
			tea->validOrder();
			break;
		case 0:
			cout << "即将退出登录！" << endl;
			return;
		default:
			break;
		}
	}
}


int main() {
	while (true)
	{
		show_menu();
		select_user();
		system("pause");
		system("cls");
	}
	return 0;
}