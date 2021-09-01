#include "Student.h"

Student::Student()
{

}


Student::Student(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	// 在学生构造函数中初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom comp;
	while ((ifs >> comp.m_id) && (ifs >> comp.m_maxNum))
	{
		this->comps.push_back(comp);
	}	
}

void Student::operMenu()
{
	cout << "欢迎学生：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： ";
}

void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int oday = 0;
	while (true)
	{
		cout << "请输入申请预约的日期：";
		cin >> oday;
		if ((oday >= 1) && (oday <= 5))
		{
			break;
		}
		cout << "预约日期有误，请重新输入！" << endl;
	}
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	int otime;
	while (true)
	{
		cout << "请输入申请预约的时间：";
		cin >> otime;
		if ((otime == 1) || (otime == 2))
		{
			break;
		}
		cout << "预约时间有误，请重新输入！" << endl;
	}
	cout << "1号机房容量：" << comps[0].m_maxNum << endl;
	cout << "2号机房容量：" << comps[1].m_maxNum << endl;
	cout << "3号机房容量：" << comps[2].m_maxNum << endl;
	int oroom;
	while (true)
	{
		cout << "请输入申请预约的机房：";
		cin >> oroom;
		if ((otime == 1) || (otime == 2) || (otime == 3))
		{
			break;
		}
		cout << "预约机房有误，请重新输入！" << endl;
	}
	cout << "预约成功，等待教师审核中！" << endl;
	// 将预约信息写入order文件中
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "data:" << oday << ' ';
	ofs << "interval:" << otime << ' ';
	ofs << "stuid:" << this->m_id << ' ';
	ofs << "name:" << this->m_Name << ' ';
	ofs << "roomid:" << oroom << ' ';
	ofs << "state:" << 1 << ' ' << endl;
	ofs.close();
	system("pause");
	system("cls");
}

void Student::showMyOrder()
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
		// 将字符串强转为数字
		if (atoi(od.m_order_data[i]["stuid"].c_str()) == this->m_id)
		{
			Order of = od;
			cout << "预约日期： 周" << of.m_order_data[i]["oday"];
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
	system("pause");
	system("cls");
}

void Student::showAllOrder()
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

void Student::cancleOrder()
{
	Order of;
	if (of.order_size == 0)
	{
		cout << "当前没有可供取消的记录！" << endl;
	}
	// 用于标记操作记录的文件index
	vector<int> vindex;
	for (int i = 0; i < of.order_size; i++)
	{
		// 筛选属于自己的记录
		if (atoi(of.m_order_data[i]["stuid"].c_str()) == this->m_id)
		{
			if (of.m_order_data[i]["state"] == "1" || of.m_order_data[i]["state"] == "2")
			{
				vindex.push_back(i);	// 将操作的行号放进去
				cout << vindex.size() << "、";
				cout << "预约日期： 周" << of.m_order_data[i]["oday"];
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
		// 修改对应记录
		of.m_order_data[vindex[choose - 1]]["state"] = "0";
		of.updateOrder();
		cout << "已成功取消预约！" << endl;
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