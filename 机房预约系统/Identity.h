#pragma once // 防止头文件重复
#include<iostream>
#include<string>
using namespace std;

// 抽象类-Identity身份类-用于作为三个身份的基类-包含三个类的共性
class Identity {
public:

	// 每个身份都有各自的身份菜单
	virtual void operMenu() = 0;

	// 每个身份都有自己的用户名和密码
	string m_Name;
	string m_Pwd;
};