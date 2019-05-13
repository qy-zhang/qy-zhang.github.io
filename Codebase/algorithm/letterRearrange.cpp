/**
 * @File : letterRearrange.cpp
 * @Author : zhangqianyi
 * @Date : 2016/10/26
 * @Description :
输入一个字典（用******结尾），然后再输入若干单词。每输入一个单词w，你都需要在字典中找出所有可以用w的字母重排后得到的单词，
并按照字典序从小到大的顺序在一行中输出（如果不存在，输出:( )。

样例输入：
tap given score refound only trap work earn course pepper part
******
resco nfudre aptr sett oresuc
样例输出：
score refund part trap :( course

思路，如何判断两个单词是否可以通过重排得到呢？我们可以把单词的每个字母排序，然后直接比较即可。

 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// template <typename T>
int Partition(string & s, int low, int high)
{
	int pivotkey = s[low];
	while (low < high)
	{
		while (low < high && s[high] >= pivotkey) --high;
		s[low] = s[high];
		while (low < high && s[low] <= pivotkey) ++low;
		s[high] = s[low];
	}
	s[low] = pivotkey;
	return low;
}
// template <typename T>
void QSort(string & s, int low, int high)
{
	if (low < high)
	{
		int pivotloc = Partition(s, low, high);
		QSort(s, low, pivotloc - 1);
		QSort(s, pivotloc + 1, high);
	}
}


int main(int argc, char const *argv[])
{
	vector<string> strArray;

	// 输入单词，直到输入的第一个单词开头为*结束
	cout << "--------Input letter, end with '*' : --------" << endl;
	while (1) {
		string tmp;
		cin >> tmp;
		strArray.push_back(tmp);
		if (tmp[0] == '*') break;
	}
	cout << "--------Letter : --------" << endl;
	for (string::size_type i = 0; i < strArray.size(); ++i)
	{
		cout << strArray[i] << endl;
	}
	cout << "--------Rearrange : --------" << endl;
	// 给每一个单词排序
	for (string::size_type i = 0; i < strArray.size(); ++i)
	{
		QSort(strArray[i], 0, strArray[i].size() - 1);
		cout << strArray[i] << endl;
	}

	// 任意输入乱序的单词，与上述排完序之后的字典逐个字符进行比较
	int found = 1;
	string strInput;
	cout << "--------Input a unordered string : --------" << endl;
	cin >> strInput;
	QSort(strInput, 0, strInput.size() - 1);
	for (string::size_type i = 0; i < strArray.size(); ++i)
	{
		found = 1;
		for (string::size_type j = 0; j < strInput.size(); ++j)
		{
			if (strArray[i][j] != strInput[j])
			{
				found = 0;
				break;
			}
		}
		if (found == 1)
		{
			cout << "found string in dictionary : " << strArray[i] << endl;
			break;
		}
	}
	if (found == 0)
	{
		cout << "cannot found string in dictionary ! :(" << endl;
	}

	return 0;
}