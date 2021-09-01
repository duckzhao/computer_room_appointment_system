#include "Order.h"

Order::Order()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string oday;
	string otime;
	string stuid;
	string stuname;
	string roomid;
	string state;
	int num = 0;
	int index;
	while (ifs >> oday && ifs >> otime && ifs >> stuid && ifs >> stuname && ifs >> roomid && ifs >> state)
	{
		map<string, string> m;
		// 分割读到的数据
		index = oday.find(':');
		oday = oday.substr(index + 1, oday.size() - index -1);
		m.insert(make_pair("oday", oday));

		index = otime.find(':');
		otime = otime.substr(index + 1, otime.size() - index - 1);
		m.insert(make_pair("otime", otime));

		index = stuid.find(':');
		stuid = stuid.substr(index + 1, stuid.size() - index - 1);
		m.insert(make_pair("stuid", stuid));

		index = stuname.find(':');
		stuname = stuname.substr(index + 1, stuname.size() - index - 1);
		m.insert(make_pair("stuname", stuname));

		index = roomid.find(':');
		roomid = roomid.substr(index + 1, roomid.size() - index - 1);
		m.insert(make_pair("roomid", roomid));

		index = state.find(':');
		state = state.substr(index + 1, state.size() - index - 1);
		m.insert(make_pair("state", state));

		this->m_order_data.insert(make_pair(num, m));
		num++;
	}
	ifs.close();
	this->order_size = num;
}

void Order::updateOrder()
{
	// 如果没有预约信息，则不需要重新写入
	if (this->order_size == 0)
	{
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	for (int i = 0; i < this->order_size; i++)
	{
		ofs << "data:" << this->m_order_data[i]["oday"] << " ";
		ofs << "interval:" << this->m_order_data[i]["otime"] << " ";
		ofs << "stuid:" << this->m_order_data[i]["stuid"] << " ";
		ofs << "name:" << this->m_order_data[i]["stuname"] << " ";
		ofs << "roomid:" << this->m_order_data[i]["roomid"] << " ";
		ofs << "state:" << this->m_order_data[i]["state"] << endl;
	}
	ofs.close();
}