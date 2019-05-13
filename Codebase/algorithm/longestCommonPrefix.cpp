/*!
 * \file longestCommonPrefix.cpp
 *
 * \author zhangqianyi
 * \date 九月 2016
 *
 * \discription 
	Write a function to find the longest common prefix string amongst an array of strings.

 */


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.empty()) return "";
		
		string str1 = strs[0];
		if (str1 == "") return "";
		
		for (unsigned int i = 1; i < strs.size(); ++i) {
			string str2 = strs[i];
			if (str2 == "") return "";

			int ind = 0;
			while (str1[ind] == str2[ind]) ind++;
			str1 = str1.substr(0, ind);
		}
		return str1;
	}
};

int main()
{
	vector<string> strs(4);
	strs[0] = "hello";
	strs[1] = "hellen";
	strs[2] = "hevector";
	strs[3] = "hematlab";

	Solution sol;
	string prefix = "";
	prefix = sol.longestCommonPrefix(strs);
	cout << prefix << endl;
}
