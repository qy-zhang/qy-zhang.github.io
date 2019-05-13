/**
 * @File : rebuildBianryTree.c
 * @Author : zhangqianyi
 * @Date : 2016/11/8
 * @Description :

对于一个二叉树T，可以递归定义它的先序遍历、中序遍历和后序遍历如下：
PreOrder(T) = T的根结点 + PreOrder（T的左子树）+PreOrder（T的右子树）
InOrder(T) = InOrder（T的左子树）+T的根结点+InOrder（T的右子树）
PostOrder（T） = PostOrder（T的左子树）+PostOrder（T的右子树）+T的根结点
其中，加号表示字符串链接运算。

输入一颗二叉树的先序遍历和中序遍历序列，输出他的后序遍历序列。
样例输入：
DBACEGF ABCDEFG
BCAD CBAD

样例输出：
ACBFGED
CDAB

分析：
先序遍历的第一个字符就是根结点，因此只需在中序遍历中找到它，就知道左右子树的先序和后序遍历了。

 */

#include <stdio.h>
#include <string.h>

void rebuildBianryTree(int n, char* strPreOrder, char* strInOrder, char* s)
{
	if (n <= 0) return;
	// 先根据先序遍历的第一个字符找到根结点，然后依此作为中序遍历序列中的划分依据
	int p = strchr(strInOrder, strPreOrder[0]) - strInOrder;
	rebuildBianryTree(p, strPreOrder + 1, strInOrder, s); // 递归构造左子树的后序遍历
	rebuildBianryTree(n - p - 1, strPreOrder + p + 1, strInOrder + p + 1, s + p); // 递归构造右子树的后序遍历
	s[n - 1] = strPreOrder[0]; // 把根结点添加到最后
}

int main(int argc, char const *argv[])
{
	char strPreOrder[] = "AAAAAAAA";
	scanf("%s", strPreOrder);
	char strInOrder[] = "AAAAAAAA";
	scanf("%s", strInOrder);
	char strPostOrder[] = "AAAAAAAA";


	int n = strlen(strPreOrder);
	rebuildBianryTree(n, strPreOrder, strInOrder, strPostOrder);
	strPostOrder[n] = '\0';
	printf("%s\n", strPostOrder);

	return 0;
}