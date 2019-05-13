/**
 * @File : TwoSum.cpp
 * @Author : zhangqianyi
 * @Date : 2016/7/5
 * @Description : 
	Given an array of integers, return indices of the two numbers such that they add up to a specific target.
	You may assume that each input would have exactly one solution.

	Example:
	Given nums = [2, 7, 11, 15], target = 9, Because nums[0] + nums[1] = 2 + 7 = 9,
	return [0, 1]. 
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		//Key is the number and value is its index in the vector.
		unordered_map<int, int> hash;
		vector<int> result;
		for (unsigned int i = 0; i < numbers.size(); i++) {
			int numberToFind = target - numbers[i];

			//if numberToFind is found in map, return them
			if (hash.find(numberToFind) != hash.end()) {
				//+1 because indices are NOT zero based
				result.push_back(hash[numberToFind]);
				result.push_back(i);
				return result;
			}

			//number was not found. Put it in the map.
			hash[numbers[i]] = i;
		}
		return result;
	}
}

int main(int argc, char const *argv[])
{
	vector<int> result;
	vector<int> numbers;
	numbers.push_back(2);
	numbers.push_back(7);
	numbers.push_back(8);
	numbers.push_back(11);
	int target = 18;

	Solution sol = new Solution;

	result = sol.twoSum(numbers, target);

	cout << result[0] << " and " << result[1] <<  endl;
	
	return 0;
}
