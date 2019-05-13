/**
 * @File : bigFactory.cpp
 * @Author : zhangqianyi
 * @Date : 2016/10/21
 * @Description : introduce
 输入不超过1000的正整数n，输出n!=1*2*3*...*n的精确结果
 样例输入：30
 样例输出：
 */

#include <stdio.h>
#include <string.h>

#define maxn 3000
int f[maxn];

int main(int argc, char const *argv[])
{
	int i, j, n;
	printf("Please input n : ");
	scanf("%d", &n);
	memset(f, 0, sizeof(f));
	f[0] = 1; // 0! = 1
	for (i = 2; i <= n; ++i)
	{
		int c = 0;
		for (j = 0; i < maxn; ++j)
		{
			int s = f[j] * i + c;
			f[j] = s % 10;
			c = s / 10;
		}
	}
	for (j = maxn - 1; j >= 0; --j)
		if (f[j])
			break;
	for (i = j; i >= 0; --i)
		printf("%d", f[i]);
	printf("\n");

	return 0;
}