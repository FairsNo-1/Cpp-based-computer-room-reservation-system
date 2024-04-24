#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include"Identity.h"
#include"orderFile.h"
using namespace std;

class Teacher :public Identity {
public:
	// 默认构造函数
	Teacher();

	// 有参构造函数
	Teacher(int empId, string name, string pwd);

	// 重写基类的openMenu方法-获取老师对应的窗口
	virtual void operMenu();

	// 教师功能一：查看所有预约
	void showAllOrder();

	// 教师功能二：审核预约
	void validOrder();

	// 教师编号
	int m_EmpId;

};