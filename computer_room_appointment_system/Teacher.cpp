#include "Teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： ";

}

void Teacher::showAllOrder()
{
	Order od;
	if (od.order_size == 0)
	{
		cout << "当前没有预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < od.order_size; i++)
	{
		Order of = od;
		cout << "预约日期： 周" << of.m_order_data[i]["oday"];
		cout << " 时段：" << (of.m_order_data[i]["otime"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_order_data[i]["stuid"];
		cout << " 姓名：" << of.m_order_data[i]["stuname"];
		cout << " 机房：" << of.m_order_data[i]["roomid"];
		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_order_data[i]["state"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_order_data[i]["state"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_order_data[i]["state"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	Order of;
	if (of.order_size == 0)
	{
		cout << "当前没有预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	// 用于标记操作记录的文件index
	vector<int> vindex;
	for (int i = 0; i < of.order_size; i++)
	{
		if (of.m_order_data[i]["state"] == "1")
		{
			vindex.push_back(i);	// 将操作的行号放进去
			cout << vindex.size() << "、";
			cout << "预约日期： 周" << of.m_order_data[i]["oday"];
			cout << " 学号：" << of.m_order_data[i]["stuid"];
			cout << " 姓名：" << of.m_order_data[i]["stuname"];
			cout << " 时段：" << (of.m_order_data[i]["otime"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_order_data[i]["roomid"];
			string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			if (of.m_order_data[i]["state"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_order_data[i]["state"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_order_data[i]["state"] == "-1")
			{
				status += "审核未通过，预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	cout << "请输入要操作的记录号（输入0取消）：";
	int choose;
	cin >> choose;
	if (choose == 0)
	{
		cout << "操作取消！" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (choose >= 0 && choose <= vindex.size())
	{
		cout << "请输入审核结果（1.通过，其他拒绝）：";
		int choose_2;
		cin >> choose_2;
		if (choose_2 == 1)
		{
			// 修改对应记录
			of.m_order_data[vindex[choose - 1]]["state"] = "2";
			of.updateOrder();
		}
		else
		{
			// 修改对应记录
			of.m_order_data[vindex[choose - 1]]["state"] = "-1";
			of.updateOrder();
		}
		cout << "审核完毕！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入有误，请重新操作！" << endl;
		system("pause");
		system("cls");
	}
}