#pragma once
#include<iostream>
#include<string>
using namespace std;

// 抽象类，只有头文件即可，不需要实现代码，用子类实现，管理系统中的三种身份抽象出来的
class Identity
{
public:
	// 纯虚函数
	virtual void operMenu() = 0;
	string m_Name;
	string m_Pwd;

private:

};