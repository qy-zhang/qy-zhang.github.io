#include <iostream>

using namespace std;

/*!
* \brief 返回子串T在主串S中第pos个字符之后的位置，若不存在则函数返回值为0
*
* \Author : zhangqianyi
* \Date : Sun Sep 18 20:46:07 2016
*
* \param string s 主串
* \param string t 子串
* \param unsigned int pos 从主串开始位置开始匹配
* \return 返回子串在主串中匹配到的位置-1
*/
int stringIndex(string s, string t, int pos) {
	int i = pos, j = 0;
	int s_size = s.size(), t_size = t.size();
	while (i < s_size && j < t_size) {
		if (s[i] == t[j]) { ++i; ++j; }
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= t_size) return i - t.size();
	if (i >= s_size) return -1;
}

void getNext(string t, int next[])
{
	int i = 0, j = -1;
	int t_size = t.size();
	next[0] = j;

	while (i < t_size) {
		if (j == -1 || t[i] == t[j]) { //j==-1证明已经与t[0]不匹配了，此时next[i+1]=0
			++i; ++j;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

int stringIndexKMP(string s, string t, int pos)
{
	int i = pos;
	int j = 0;

	int s_size = s.size(), t_size = t.size();

	int* next = new int[t.size() + 1];
	getNext(t, next);

	while (i < s_size && j < t_size) {
		if (j == -1 || s[i] == t[j]) {
			++i; ++j;
		}
		else {
			j = next[j];
		}
	}

	delete[] next;

	if (j >= t_size) return i - t.size();
	if (i >= s_size) return 0;
}

int main()
{
	string s = "aaacababaababaedabeds";
	string t = "ababaabab";
	int pos = 0;

	// int resultOfIndex = stringIndex(s, t, pos);
	int resultOfKMP = stringIndexKMP(s, t, pos);

	// cout << resultOfIndex << endl;
	cout << resultOfKMP << endl;

	return 0;
}
