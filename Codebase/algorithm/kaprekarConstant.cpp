/**
* @File : kaprekarConstant.cpp
* @Author : zhangqianyi
* @Date :
* @Description : introduce
假设你有一个各位数字互不相同的四位数，把所有数字从大到小排序后得到a, 从小到大排序后得到b,然后用a - b替换原来这个数，并且继续操作。
例如，从1234出发，依次可以得到4321-1234=3087、8730-378=8352、8532-2358=6174。有趣的是，7641-1467=6174,回到了它自己。

输入一个n位数，输出操作序列，直到出现循环（即新得到的数曾经得到过）。
输入保证在循环之前最多只会产生1000个整数。
样例输入：1234
样例输出：1234 -> 3087 -> 8352 -> 6174 -> 6174
*/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// 字符串作为函数参数传递的时候，如果要更改字符串的内容要使用字符串的引用！
void sortString(string &s)
{
	for (unsigned int i = 0; i < s.size() - 1; ++i) // 循环结束条件为s的长度减一，因为字符串s的长度加上了尾部的'\n'
	{
		for (unsigned int j = i + 1; j < s.size() - 1; ++j)
		{
			if (s[i] > s[j])
			{
				char t = s[i];
				s[i] = s[j];
				s[j] = t;
			}
		}
	}
}

int getNextNum(int x)
{
	int maxX, minX;
	// 整型转字符串
	ostringstream oStream;
	oStream << x << endl;
	string s1 = oStream.str();

	// 对字符串中的数字排序
	sortString(s1);
	// 字符串转数字
	istringstream iStream;
	iStream.str(s1);
	iStream >> minX;

	// 将字符串反转
	reverse(s1.begin(), s1.end());
	iStream.str(s1);
	iStream >> maxX;

	return maxX - minX;
}

int main(int argc, char const *argv[])
{
	int num[2000] = { 0 };
	num[0] = 1234;
	int count = 1;

	cout << num[0];
	while (1)
	{
		num[count] = getNextNum(num[count - 1]);
		cout << " -> " << num[count];

		int found = 0;
		for (int i = 0; i < count; ++i)
		{
			if (num[i] == num[count])
			{
				found = 1;
				break;
			}
		}
		if (found) break;
		count++;
	}
	cout << endl;

	return 0;
}