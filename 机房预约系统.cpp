#include<iostream>
#include<string>
#include<fstream>
#include"Identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
using namespace std;

// 全局函数-用于管理员调用自己的窗口
void managerMenu(Identity*& manager) {
	while (true) {
		// 打开管理员窗口(调用父类公共接口打印子类信息，发生多态)
		manager->operMenu();

		// 将manager转化为Manager类下的对象，否则无法调用子类成员对象和方法
		Manager* man = (Manager*)manager;

		// 定义选择变量
		int select = 0;
		cin >> select;

		// 进行管理员操作一：添加账号
		if (select == 1) {
			// cout << "添加账号" << endl;
			man->addPerson();
		}

		// 进行管理员操作二：查看账号
		else if (select == 2) {
			// cout << "查看账号" << endl;
			man->showPerson();

		}

		// 进行管理员操作三：查看机房
		else if (select == 3) {
			// cout << "查看机房" << endl;
			man->showComputer();
		}

		// 进行管理员操作四：清空预约
		else if (select == 4) {
			// cout << "清空预约" << endl;
			man->cleanFile();
		}

		// 注销登录
		else {
			// 从LoginIn函数传入的指针指向的内容是在堆区开辟的
			// 注销之后要释放堆区
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

// 全局函数-用于学生调用自己的窗口
void studentMenu(Identity*& student) {
	while (true) {
		// 打开学生窗口(调用父类公共接口打印子类信息，发生多态)
		student->operMenu();

		// 将student转化为Student类下的对象，否则无法调用子类成员对象和方法
		Student* man = (Student*)student;

		// 定义选择变量
		int select = 0;
		cin >> select;

		// 进行学生操作一：申请预约
		if (select == 1) {
			man->applyOrder();
		}

		// 进行学生操作二：查看自身预约
		else if (select == 2) {
			man->showMyOrder();

		}

		// 进行学生操作三：查看所有预约
		else if (select == 3) {
			man->showAllOrder();
		}

		// 进行学生操作四：取消预约
		else if (select == 4) {
			// cout << "清空预约" << endl;
			man->cancelOrder();
		}

		// 注销登录
		else {
			// 从LoginIn函数传入的指针指向的内容是在堆区开辟的
			// 注销之后要释放堆区
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

// 全局函数-用于老师调用自己的窗口
void teacherMenu(Identity*& teacher) {
	while (true) {
		// 打开学生窗口(调用父类公共接口打印子类信息，发生多态)
		teacher->operMenu();

		// 将student转化为Student类下的对象，否则无法调用子类成员对象和方法
		Teacher* man = (Teacher*)teacher;

		// 定义选择变量
		int select = 0;
		cin >> select;

		// 进行老师操作一：查看所有预约信息
		if (select == 1) {
			man->showAllOrder();
		}

		// 进行老师操作二：审核预约
		else if (select == 2) {
			man->validOrder();

		}

		// 注销登录
		else {
			// 从LoginIn函数传入的指针指向的内容是在堆区开辟的
			// 注销之后要释放堆区
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

// 定义全局函数LoginIn用于用户的登录操作
void LoginIn(string fileName, int type) {
	// filename:指定用户对应的TXT文件，以查询用户是不是存在
	// type：指明用户类型

	// 创建一个基类指针，因为最开始不知道用户类型
	Identity* person = NULL;

	// 读取指定的文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	// 判断文件是否存在
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	// 定义用于存放用户输入信息的变量
	int id = 0;
	string name;
	string pwd;

	// 根据输入的type来判断身份
	if (type == 1) { // 学生登录
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) { // 教师身份
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}
	// 管理员不需要判断

	// 用户使用账号密码登录
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	// 用户身份认证
	if (type == 1) { // 学生身份认证
		int fId;
		string fName;
		string fPwd;
		// ifs逐条读取student.txt的信息
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");

				// 确认用户信息存在后利用基类指针创建用户对象
				person = new Student(id, name, pwd);

				// 进入学生的子菜单
				studentMenu(person);

				return;

			}
		}
	}

	else if (type == 2) { // 教师身份认证
		int fId;
		string fName;
		string fPwd;
		// ifs逐条读取teacher.txt的信息
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");

				// 确认用户信息存在后利用基类指针创建用户对象
				person = new Teacher(id, name, pwd);

				// 进入教师的子菜单
				teacherMenu(person);

				return;

			}
		}
	}

	else if (type == 3) { // 管理员身份认证
		string fName;
		string fPwd;
		// ifs逐条读取admin.txt的信息
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");

				// 确认用户信息存在后利用基类指针创建用户对象
				person = new Manager(name, pwd);

				// 进入管理员的子菜单
				managerMenu(person);

				return;

			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}


int main() {
	// 用于判断选择的变量
	int select = 0;
	while (true) {
		// 预约系统主界面
		cout << "========================== 欢迎进入机房预约系统 ==========================" << endl;
		cout << endl << "请输入您的身份：" << endl;
		cout << "\t\t-----------------------------------------\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|              1.学生代表               |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|              2.老    师               |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|              3.管 理 员               |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|              0.退    出               |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t-----------------------------------------\n";
		cout << "输入您的选择：";

		// 获取用户操作
		cin >> select;
		switch (select) {
		case(1): //学生登录
			LoginIn(STUDENT_FILE, 1);
			break;
		case(2): //老师登录
			LoginIn(TEACHER_FILE, 2);
			break;
		case(3): //管理员登录
			LoginIn(ADMIN_FILE, 3);
			break;
		case(0): //退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls"); // 清空控制台屏幕
			break;
		}

	}
	system("pause");
	return 0;
}