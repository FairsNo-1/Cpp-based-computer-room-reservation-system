#include<algorithm>
#include"manager.h"
#include"globalFile.h"

// 默认构造函数
Manager::Manager() {

}

// 有参构造函数
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;

	// 初始化容器
	this->initVector();

	// 初始化机房信息
	this->initComputerRoom();
}

// 重写基类的openMenu函数-打开管理员对应的窗口
void Manager::operMenu() {
	cout << "欢迎管理员" << this->m_Name << "登录！" << endl;
	cout << "\t\t-----------------------------------------\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|              1.添加账号               |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|              2.查看账号               |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|              3.查看机房               |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|              4.清空预约               |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t|              0.注销登录               |\n";
	cout << "\t\t|                                       |\n";
	cout << "\t\t-----------------------------------------\n";
	cout << "请选择您的操作：";

}

// 管理员功能一：添加账号
void Manager::addPerson() {
	// 提示信息
	cout << "请输入想要添加的账号的类型：" << endl;
	cout << "1.添加学生账号" << endl;
	cout << "2.添加老师账号" << endl;

	string tip; // 提示信息
	string errorTip;
	string filename;  // 根据输入序号选择文件
	ofstream ofs; 

	int select = 0;
	cin >> select;
	if (select == 1) {
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入！";
		filename = STUDENT_FILE;
	}
	else if (select == 2) {
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入！";
		filename = TEACHER_FILE;
	}
	else {
		cout << "你输入的序号有误，请重新输入：" << endl;
		system("pause");
		system("cls");
		return;
	}

	// 打开文件以追加(append)的方式写(out)文件
	ofs.open(filename, ios::out | ios::app);

	// 定义变量暂存想要添加的账号
	int id;
	string name;
	string pwd;

	cout << tip;


	// 检测id是否已经重复
	while (true) {
		cin >> id;
		if (this->checkRepeat(id, select)) {
			cout << errorTip << endl;
			cout << tip << endl;
		}
		else {
			break;
		}
	}

	cout << "请输入用户名：";
	cin >> name;

	cout << "请输入密码：";
	cin >> pwd;

	// 添加操作
	ofs << id << " " << name << " " << pwd << " " << endl; 
	cout << "添加账号成功！";

	system("pause");
	system("cls");

	ofs.close();

	// 防止一次性添加多个用户信息时检测不到重复-每添加一个用户信息就刷新一下容器
	this->initVector();
}

// 管理员功能二：查看账号

// 打印学生信息-为showPerson服务
void printStudent(Student& s) {
	cout << "学号：" << s.m_Id << "姓名：" << s.m_Name << "密码：" << s.m_Pwd << endl;
}
// 打印教师信息-为showPerson服务
void printTeacher(Teacher& t) {
	cout << "职工号：" << t.m_EmpId << "姓名：" << t.m_Name << "密码：" << t.m_Pwd << endl;
}

void Manager::showPerson() {
	cout << "请选择查看对象：" << endl;
	cout << "1.查看学生信息" << endl;
	cout << "2.查看老师信息" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "学生的信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2) {
		cout << "老师的信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	else {
		cout << "你输入的需要有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}


// 管理员功能三：查看机房信息
void Manager::showComputer() {
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
		cout << "机房id：" << it->m_ComId << "机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

// 管理员功能四：清空预约
void Manager::cleanFile() {
	ofstream ofs;
	// trunc的方式打开-文件存在则清除重新创建
	ofs.open(ORDER_FILE, ios::trunc);

	cout << "清除成功！" << endl;
	ofs.close();
	system("pause");
	system("cls");
}

// 初始化容器
void Manager::initVector() {
	// 清空学生和教师容器
	vStu.clear();
	vTea.clear();

	// 读取学生文件中的信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "打开文件失败!" << endl;
		return;
	}

	// 读取文件中的学生信息并写入容器
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生的数量为：" << vStu.size() << endl;
	ifs.close();

	// 读取老师文件中的信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "打开文件失败!" << endl;
		return;
	}

	// 读取文件中的老师信息并写入容器
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前老师的数量为：" << vTea.size() << endl;
	ifs.close();

}

// 方法checkRepeat用于检测是否有重复id的用户信息
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else if (type == 2) {
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_EmpId) {
				return true;
			}
		}
	}
	return false;
}

// 初始化机房信息函数
void Manager::initComputerRoom() {
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum) {
		vCom.push_back(c);
	}
	ifs.close();
	cout << "机房的数量为：" << vCom.size() << endl;
}