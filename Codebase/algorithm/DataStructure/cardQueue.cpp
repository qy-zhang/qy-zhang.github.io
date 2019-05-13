/**
 * @File : cardQueue.cpp
 * @Author : zhangqianyi
 * @Date : 2016/10/31
 * @Description :
桌上有一叠牌，从第一张牌（即位于顶面的牌）开始从上往下依次编号为1~n。当至少还剩两张牌时进行一下操作：
把第一张牌扔掉，然后把新的第一张放到整叠牌的最后。
输入n，输出每次扔掉的牌，以及最后剩下的牌。

样例输入：7
样例输出：1 3 5 7 4 2 6

思路：
这些牌就是在排队，每次从排头拿到两个，其中第二个再次排到队尾。

 */

#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	cout << "Input n : " << endl;
	cin >> n;

	// 新建并初始化牌队列
	queue<int> cardQueue;
	for (int i = 0; i < n; ++i)
	{
		cardQueue.push(i + 1);
	}

	while (!cardQueue.empty())
	{
		cout << cardQueue.front() << " "; // 输出队首元素
		cardQueue.pop(); // 弹出队首元素
		cardQueue.push(cardQueue.front()); // 把现在的队首元素放到队尾
		cardQueue.pop(); // 弹出队首元素
	}
	cout << endl;

	return 0;
}