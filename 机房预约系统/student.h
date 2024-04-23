#pragma once 
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Identity.h"
#include"globalFile.h"
#include"computerRoom.h"
#include"orderFile.h"
using namespace std;

class Student :public Identity {
public:
	// 默认构造函数
	Student();

	// 有参构造函数
	Student(int id, string name, string pwd);

	// 重写基类中的openMenu函数-打开学生对应的窗口
	virtual void operMenu();

	// 学生功能一：申请预约
	void applyOrder();

	// 学生功能二：查看我的预约
	void showMyOrder();

	// 学生功能三：查看所有的预约
	void showAllOrder();

	// 学生功能四：取消预约
	void cancelOrder();

	// 学生学号
	int m_Id;

	// 机房容器
	vector<ComputerRoom>vCom;

	// 机房容器初始化
	void initvCom();

};