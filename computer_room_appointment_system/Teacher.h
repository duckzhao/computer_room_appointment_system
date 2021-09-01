#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
#include "Order.h"
#include<vector>
using namespace std;

class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);
	virtual void operMenu();
	void showAllOrder();
	void validOrder();
	int m_id;

private:

};