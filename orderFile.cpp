#include"orderFile.h"

// 先定义一个全局分割函数-下面默认构造函数在截取预约信息时用
pair<string,string> segData(string & data) {
	// 用来暂存键和值的变量
	string key;
	string val;

	// 以冒号为标志将信息风格用变量保存
	// 如：date:1	分割为key=date,val=1
	int pos = data.find(":");
	key = data.substr(0, pos);
	val = data.substr(pos + 1, data.size() - pos - 1);
	return make_pair(key, val);
}

// 默认构造函数
OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	// 暂存预约信息的变量
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	// 初始化信息条数为0
	this->m_size = 0;

	// 读取预约信息
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status) {
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl; 
		//cout << status << endl;

		// 解析读取的字符串
		//(如变量date读取的信息为date：1，我们需要将1分割出来)
		// 解析好的信息用map容器保存
		map<string, string>m;
		// 截取日期
		m.insert(segData(date));
		// 截取时间段
		m.insert(segData(interval));
		// 截取学生id
		m.insert(segData(stuId));
		// 截取学生姓名
		m.insert(segData(stuName));
		// 截取机房号
		m.insert(segData(roomId));
		// 截取预约状态
		m.insert(segData(status));

		// 将小的map容器m放入大的map容器m_orderData中
		this->m_orderData.insert(make_pair(this->m_size, m));
		this->m_size++;
		
	}
	ifs.close();

	// 测试map容器m_orderData
	//for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++) {
	//	cout << "第" << it->first <<"条预约信息内容为：" << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++) {
	//		cout << " key:" << mit->first << " value:" << mit->second << endl;
	//	}
	//}
}

// 更新预约记录的函数
void OrderFile::updateOrder() {
	// 一条记录都没有，不更新
	if (!this->m_size) return;
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_size; i++) {
		// 从容器中读取最新的预约数据
		ofs << "date:" << m_orderData[i]["date"] << " ";
		ofs << "interval:" << m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << m_orderData[i]["roomId"] << " ";
		ofs << "status:" << m_orderData[i]["status"] << endl;
	}
	ofs.close();
}