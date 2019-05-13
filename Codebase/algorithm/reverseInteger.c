/**
 * @File : reverseInteger.c
 * @Author : zhangqianyi
 * @Date : 2016/7/12
 * @Description : introduce

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321
 */

#include <stdio.h>
#include <stdlib.h>

int reverse(int x)
{
	int ans = 0;

	while(x != 0) {
		int temp = ans * 10 + x % 10;
		if (temp/10 != ans)	{
			return 0;
		}
		ans = temp;
		x /= 10;
	}
	return ans;
}

int main(int argc, char const *argv[])
{
	int x = 1234;
	int x_rev = reverse(x);
	printf("The reverse of %d is %d\n", x, x_rev);
	return 0;
}