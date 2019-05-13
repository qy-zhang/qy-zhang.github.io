/**
 * @File : readFile.cpp
 * @Author : zhangqianyi
 * @Date : 2017/5/16 14:18
 * @Description :
C++读取文件数据，文件中每一行有多个double型数据，用tab制表符隔开
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<vector<double> > getDoubleInFile(const string& filePath) {
    vector<vector<double> > data;
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cout << "Error opening file" << endl;
        exit(-1);
    }

    while (fileStream) {
        string strLine = "";
        getline(fileStream, strLine);

        // 从string中解析出数字
        istringstream iss(strLine);
        vector<double> numLine;
        // 使用istringstream来读入一个数字
        for (double d; iss >> d; numLine.push_back(d)) {}
        data.push_back(numLine);
    }

    fileStream.close();

    return data;
}

void splitString(const string& s, vector<string>& v, const string& c) {
    string::size_type pos1, pos2;
    pos1 = 0;
    pos2 = s.find(c);
    while (string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length()) {
        v.push_back(s.substr(pos1));
    }
}

vector<vector<string> > getStringInFile(const string& filePath) {
    vector<vector<string> > data;
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cout << "Error opening file" << endl;
        exit(-1);
    }

    while (fileStream) {
        string strLine = "";
        getline(fileStream, strLine);

        // 从整个字符串中解析出以空格为划分的单个字符串
        string c = " ";
        vector<string> v;
        splitString(strLine, v, c);
        data.push_back(v);
    }

    fileStream.close();

    return data;
}

int main()
{

	reutrn 0;
}