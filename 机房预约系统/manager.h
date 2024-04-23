#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
using namespace std;

class Manager:public Identity {
public:
	// 默认构造函数
	Manager();

	// 有参构造函数
	Manager(string name, string pwd);

	// 重写基类的openMenu函数-打开管理员对应的窗口
	virtual void operMenu();

	// 管理员功能一：添加账号
	void addPerson();

	// 管理员功能二：查看账号
	void showPerson();

	// 管理员功能三：查看机房信息
	void showComputer();

	// 管理员功能四：清空预约
	void cleanFile();

	// 初始化容器
	void initVector();

	// 学生容器(用于保存学生信息-防止管理员添加学生账号时出现学生编号重复)
	vector<Student>vStu;

	// 教师容器(用于保存教师信息-防止管理员添加学生账号时出现学生编号重复)
	vector<Teacher>vTea;

	// 方法checkRepeat用于检测是否有重复id的用户信息
	bool checkRepeat(int id,int type);

	// 机房容器(用于保存机房信息)
	vector<ComputerRoom>vCom;

	// 获取机房信息函数
	void initComputerRoom();
};