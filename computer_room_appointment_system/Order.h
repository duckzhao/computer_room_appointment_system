#pragma once
#include<string>
#include<iostream>
#include<map>
#include<string>
#include "globalFile.h"
#include<fstream>
using namespace std;

class Order
{
public:
	Order();

	// 记录预约的容器,map中的一个元素表示一条预约记录
	map<int, map<string, string>> m_order_data;
	int order_size = 0;

	// 教师可能会修改初始化的order容器中的内容，即审批状态，我们需要把修改后的容器内容再写入
	// order.txt文件中，用以记录
	void updateOrder();
private:

};