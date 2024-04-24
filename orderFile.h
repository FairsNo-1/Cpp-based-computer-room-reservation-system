#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include"globalFile.h"
using namespace std;

class OrderFile {
public:
	// 默认构造函数
	OrderFile();

	// 更新预约记录的函数
	void updateOrder();

	// 记录预约条数
	int m_size;

	// 记录预约信息的容器
	// (这里使用map容器进行嵌套-内层map容器用于保存特定一条预约信息，外层map容器用于组织所有的预约信息)
	map<int, map<string, string>>m_orderData;
	//   |          |       |
	//   |          |       |
	//记录条数  每条中具体的键值信息(如stuName,张三)
};