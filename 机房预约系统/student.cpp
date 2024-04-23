#include"student.h"

// 默认构造函数
Student::Student() {

}

// 有参构造函数
Student::Student(int id, string name, string pwd) {
	// 初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	// 初始化机房容器-用于预约
	this->initvCom();
}

// 重写基类中的openMenu函数-打开学生对应的窗口
void Student::operMenu() {
	cout << "欢迎学生" << this->m_Name << "登录！" << endl;
	cout << "\t\t-----------------------------------------\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             1.申请预约                |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             2.查看我的预约            |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             3.查看所有预约            |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             4.取消预约                |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|             0.注销登录                |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t-----------------------------------------\n";
	cout << "请选择您的操作：";
}

// 学生功能一：申请预约
void Student::applyOrder() {
	int date = 0; // 申请的日期
	int interval = 0; // 申请的时间段
	int room = 0; // 申请的机房

	// 确定申请预约的日期
	cout << "机房开放时间为周一到周五！" << endl;
	cout << "请选择你要预约的时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "你的输入有误，请重新输入！" << endl;
	}

	// 确认申请预约的时间段
	cout << "请输入你想要申请的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;

	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "你的输入有误，请重新输入！" << endl;
	}

	//确认申请预约的机房
	cout << "请选择机房：" << endl;
	cout << "1号机房容量：" << vCom[0].m_MaxNum << endl;
	cout << "2号机房容量：" << vCom[1].m_MaxNum << endl;
	cout << "3号机房容量：" << vCom[2].m_MaxNum << endl;

	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "你的输入有误，请重新输入！" << endl;
	}

	// 所有信息均输入正确后显示预约成功
	cout << "预约成功！审核中！" << endl;

	// 将预约信息写入order.txt中
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");

}

// 学生功能二：查看我的预约
void Student::showMyOrder() {
	// 实例化OrderFile对象，方便对预约数据进行操作
	OrderFile of; 
	if (!of.m_size) {
		cout << "无预约记录。" << endl;
		system("pause");
		system("cls");
		return;
	}

	// 变量容器找到与this学生的id匹配的记录
	for (int i = 0; i < of.m_size; i++) {
		// .cstr()方法可以将string强转为const char*类型
		// atoi()方法可以将char*强转为int类型
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id){
			cout << "预约时间：星期" << of.m_orderData[i]["date"] << " ";
			string interval = "下午";
			if (of.m_orderData[i]["interval"] == "1") {
				interval = "上午";
			}
			cout << "预约时间段：" << interval << " ";
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
	}
	system("pause");
	system("cls");

}

// 学生功能三：查看所有的预约
void Student::showAllOrder() {
	// 实例化OrderFile对象，方便对预约数据进行操作
	OrderFile of;
	if (!of.m_size) {
		cout << "无预约记录。" << endl;
		system("pause");
		system("cls");
		return;
	}

	// 变量容器找到与this学生的id匹配的记录
	for (int i = 0; i < of.m_size; i++) {
		cout << i << ".";
		cout << "预约时间：星期" << of.m_orderData[i]["date"] << " ";
		cout << "预约时间段：" << (of.m_orderData[i]["interval"] == "1"?"上午":"下午") << " ";
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

// 学生功能四：取消预约
void Student::cancelOrder() {
	// 实例化OrderFile对象，方便对预约数据进行操作
	OrderFile of;
	if (!of.m_size) {
		cout << "无预约记录。" << endl;
		system("pause");
		system("cls");
		return;
	}

	// 用于记录可操作的信息的条数的变量
	int index = 1;
	// 用于保存可操作信息在map中的条数的容器
	vector<int>v;

	cout << "可以取消的预约如下：" << endl;
	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				// 获取该信息在map中的条数
				v.push_back(i);

				// 提示是第几条可以操作的信息
				cout << index++ << ".";
				cout << "预约时间：星期" << of.m_orderData[i]["date"] << " ";
				cout << "预约时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
				cout << "预约机房：" << of.m_orderData[i]["roomId"] << " ";
				string status = "状态：";
				if (of.m_orderData[i]["status"] == "1") {
					status += "审核中···";
				}
				if (of.m_orderData[i]["status"] == "2") {
					status += "审核通过，预约成功！";
				}
				cout << status << endl;
			}
		}
	}
	
	// 只有审核中和审核通过的预约是可以取消的
	cout << "请输入要取消的预约，输入0代表返回" << endl;
	int select = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (!select) break;
			else{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约！" << endl;
				break;
			}
		}
		else {
			cout << "输入有误，请重新输入：" << endl;
		}
	}
	system("pause");
	system("cls");

}

// 机房容器初始化
void Student::initvCom() {
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in); 

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum) {
		vCom.push_back(c);
	}
	ifs.close();
}
