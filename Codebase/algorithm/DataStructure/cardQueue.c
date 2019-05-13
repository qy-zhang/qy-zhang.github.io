/**
 * @File : cardQueue.c
 * @Author : zhangqianyi
 * @Date : 2016/11/8
 * @Description :
桌上有一叠牌，从第一张牌（即位于顶面的牌）开始从上往下依次编号为1~n。当至少还剩两张牌时进行一下操作：
把第一张牌扔掉，然后把新的第一张放到整叠牌的最后。
输入n，输出每次扔掉的牌，以及最后剩下的牌。

样例输入：7
样例输出：1 3 5 7 4 2 6

思路：
这些牌就是在排队，每次从排头拿到两个，其中第二个再次排到队尾。

 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int i;
	int queue[50];
	int n, front, rear;
	printf("Input the length of queue : ");
	scanf("%d", &n);

	for (i = 0; i < n; ++i) queue[i] = i + 1; // 初始化队列
	front = 0; rear = n; // 队首队尾

	while (front < rear) {
		printf("%d ", queue[front++]);
		queue[rear++] = queue[front++];
	}

	return 0;
}