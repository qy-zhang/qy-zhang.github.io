/**
 * @File : classFunction.cpp
 * @Author : zhangqianyi
 * @Date : 2017/4/26 9:27
 * @Description :
c++中类的四个函数：构造函数、析构函数、拷贝构造函数、operator=
四个函数的实现
 */
#include <iostream>
#include <cstring>

using namespace std;

class MyString {
public:
	explicit MyString(const char* str = "");
	~MyString();
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	void print() { cout << m_data << endl; }
private:
	char* m_data;
};

MyString::MyString(const char* str) {
	if (str == NULL) {
		m_data = new char[1];
		m_data[0] = '\0';
	} else {
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
}

MyString::~MyString() {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
}

MyString::MyString(const MyString& other) {
	// 深拷贝，复制了指针指向的内容
	m_data = new char[strlen(other.m_data)+1];
	strcpy(m_data, other.m_data);

	// 下面的方式是浅拷贝
	// m_data = other.m_data;
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		// 先申请空间将other的内容拷贝到一个临时变量，防止申请空间失败连原有的空间都没了
		char* temp = new char[strlen(other.m_data)+1];
		strcpy(temp, other.m_data);
		delete[] m_data;
		m_data = NULL;
		m_data = temp;
	}
	return *this;
}

int main(int argc, char const *argv[])
{
	MyString a("a");
	MyString b("b");
	MyString c(a);
	c.print();
	c = b;
	c.print();

    return 0;
}