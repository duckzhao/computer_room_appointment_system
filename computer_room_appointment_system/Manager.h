#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
#include<vector>
#include "Student.h"
#include "Teacher.h"
#include "computerRoom.h"
using namespace std;

class Manager : public Identity
{
public:
	Manager();
	Manager(string name, string pwd);
	virtual void operMenu();
	void addUser();
	void showUser();
	void showComputer();
	void clearFile();
	// 初始化存放老师和学生信息的容器
	void initVector();
	vector<Student> stus;
	vector<Teacher> tchs;
	vector<computerRoom> comps;
	// 检测id是否重复
	bool checkRepeat(int id, int type);
private:

};