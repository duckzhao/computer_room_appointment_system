#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
#include "computerRoom.h"
#include<vector>
#include<fstream>
#include "globalFile.h"
#include "Order.h"
using namespace std;

class Student : public Identity
{
public:
	// 默认构造
	Student();
	// 有参构造
	Student(int id, string name, string pwd);
	// 菜单界面
	virtual void operMenu();
	// 申请预约
	void applyOrder();
	// 查看我的预约
	void showMyOrder();
	// 查看所有预约
	void showAllOrder();
	// 取消预约
	void cancleOrder();

	// 学生id，抽象类中没有，自己定义
	int m_id;
	
	// 因为学生预约机房时候需要知道当前机房信息，所以需要有一个机房属性在这里
	vector<computerRoom> comps;
private:

};