/*!
 * \file threeSum.cpp
 *
 * \author zhangqianyi
 * \date 九月 2016
 *
 * \description 

 Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

 Note: The solution set must not contain duplicate triplets.

 For example, given array S = [-1, 0, 1, 2, -1, -4],

 A solution set is:
 [
 [-1, 0, 1],
 [-1, -1, 2]
 ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> ans;
		if (nums.size() < 3) return ans;
		sort(nums.begin(), nums.end());

		for (unsigned int i = 0; i < nums.size() - 2; ++i) {
			if (i > 0 && nums[i] == nums[i - 1]) continue; // in case of duplicate solutions

			int a = nums[i];
			int lf = i + 1;
			int rt = nums.size() - 1;

			while (lf < rt) {
				int b = nums[lf];
				int c = nums[rt];
				if (a + b + c == 0) {
					ans.push_back(vector<int>{a, b, c});
					while (lf < nums.size() && nums[lf] == b) lf++;
					while (rt >= 0 && nums[rt] == c) rt--;
				}
				else if (a + b + c > 0) rt--;
				else lf++;
			}
		}
		return ans;
	}
};


int main()
{
	int arr[] = {-1, 0, 1, 2, -1, -4};
	vector<int> nums(arr, arr + 6);
	Solution sol;

	vector<vector<int>> ans = sol.threeSum(nums);

    

	for (unsigned int i = 0; i < ans.size(); ++i) {
		cout << ans[i][0] << '\t';
		cout << ans[i][1] << '\t';
		cout << ans[i][2] << endl;
	}

	return 0;
}
