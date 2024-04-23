#include"teacher.h"

// 默认构造函数
Teacher::Teacher() {

}

// 有参构造函数
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

// 重写基类的openMenu方法-获取老师对应的窗口
void Teacher::operMenu() {
	cout << "欢迎老师" << this->m_Name << "登录！" << endl;
	cout << "\t\t-----------------------------------------\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             1.查看所有预约            |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             2.审核预约                |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             0.注销登录                |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t-----------------------------------------\n";
	cout << "请选择您的操作：";
}

// 教师功能一：查看所有预约
void Teacher::showAllOrder() {
	OrderFile of;
	if (!of.m_size) {
		cout << "无预约记录。" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		cout << i + 1 << ".";
		cout << "预约时间：星期" << of.m_orderData[i]["date"] << " ";
		cout << "预约时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "预约学生学号：" << of.m_orderData[i]["stuId"] << " ";
		cout << "预约学生姓名：" << of.m_orderData[i]["stuName"] << " ";
		cout << "预约机房：" << of.m_orderData[i]["roomId"] << "号机房 ";
		string status = "状态：";

		// 1-审核中	2-审核通过	-1-审核不通过	0-用户已取消预约
		if (of.m_orderData[i]["status"] == "1") {
			status += "审核中···";
		}
		if (of.m_orderData[i]["status"] == "2") {
			status += "审核通过，预约成功！";
		}
		if (of.m_orderData[i]["status"] == "-1") {
			status += "审核未通过，预约失败！";
		}
		if (of.m_orderData[i]["status"] == "0") {
			status += "用户已取消预约";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

// 教师功能二：审核预约
void Teacher::validOrder() {
	// 实例化OrderFile对象，方便对预约数据进行操作
	OrderFile of;
	if (!of.m_size) {
		cout << "无预约记录。" << endl;
		system("pause");
		system("cls");
		return;
	}

	// 用于记录可操作的信息的条数的变量
	int index = 0;
	// 用于保存可操作信息在map中的条数的容器
	vector<int>v;

	cout << "可以审核的预约如下：" << endl;
	for (int i = 0; i < of.m_size; i++) {
		if (of.m_orderData[i]["status"]=="1") {
			v.push_back(i);
			cout << ++index << ".";
			cout << "预约时间：星期" << of.m_orderData[i]["date"] << " ";
			cout << "预约时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
			cout << "学生学号：" << of.m_orderData[i]["stuId"] << " ";
			cout << "学生姓名：" << of.m_orderData[i]["stuName"] << " ";
			cout << "预约机房：" << of.m_orderData[i]["roomId"] << " ";
			cout << "状态：审核中" << endl;
		}
	}

	cout << "请选择要审核的预约记录，输入0代表返回" << endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) break;
			else {
				cout << "请输入审核结果：" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else if (ret == 2) {
					of.m_orderData[v[select-1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		else {
			cout << "输入有误，请重新输入！" << endl;
		}
	}
	system("pause");
	system("cls");

}