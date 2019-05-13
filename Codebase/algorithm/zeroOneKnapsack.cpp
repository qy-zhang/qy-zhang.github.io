/**
 * @File : zeroOneKnapsack.cpp
 * @Author : zhangqianyi
 * @Date : 2016/11/22 20:46
 * @Description :
"01背包问题"
有n种重量和价值分别为Wi和Vi的物品。从这些物品中挑选出总重量不超过w的物品。
每种物品都只能挑选一件，求所有挑选方案中价值总和的最大值。

 */

#include <iostream>
#include <algorithm>

using namespace std;

int n, w;
int W[100] = {0};
int V[100] = {0};
int dp[100][100];

void zeroOneKnapsack()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = w; j >= W[i]; --j)
		{
			dp[i][j] = max(dp[i-1][j], dp[i-1][j-W[i]] + V[i]);
		}
	}
	cout << "Result max value is : " << dp[n][w] << endl;
}

int main(int argc, char const *argv[])
{
	cout << "Input number n and max weight w : " << endl;
	cin >> n >> w;

	for (int i = 0; i <= n; ++i)
		dp[i][0] = 0;
	for (int i = 0; i <= w; ++i)
		dp[0][i] = 0;

	for (int i = 0; i < n; ++i) {
		cout << "Input " << i + 1 << " weight and value : " << endl;
		cin >> W[i] >> V[i];
	}

	zeroOneKnapsack();

	return 0;
}