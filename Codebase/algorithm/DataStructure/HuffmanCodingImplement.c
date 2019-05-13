#include "HuffmanCoding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status HuffmanCoding (HuffmanTree HT, HuffmanCode HC, int* w, int n) {
	// w存放n个字符的权值(均>0)，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC
	int i;
    int m = 2*n-1;
	if (n<=1) return ERROR; // 字符数小于1，退出
    //	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));  //0号单元未用
	// 初始化哈夫曼树
	for (i=1; i<=n; ++i, ++w) {
		HT[i].ch = i+96; // 前n个结点的字符值置为a，b……
		HT[i].weight = *w; // 前n个结点的权值置为w
		HT[i].lchild = 0; HT[i].rchild = 0; HT[i].parent = 0;
	}
	for (i=n+1; i<=m; ++i){ // 后面的置为0
		HT[i].weight = 0; HT[i].lchild = 0; HT[i].rchild = 0; HT[i].parent = 0;
	}
	// 构造哈夫曼树，找结点
	int* s1 = (int*)malloc(sizeof(int));
    int* s2 = (int*)malloc(sizeof(int));
	for (i=n+1; i<=m; ++i){
		Select(HT, i-1, s1, s2); // 在i-1个结点中找到最小的没被使用的两个结点
		HT[*s1].parent = i; HT[*s2].parent = i;
		HT[i].lchild = *s1; HT[i].rchild = *s2;
		HT[i].weight = HT[*s1].weight + HT[*s2].weight;
	}
	// 哈夫曼编码
	int start, f;
	unsigned int c;
	HC = (HuffmanCode)malloc((n+1) * sizeof(char*)); // 分配n个字符编码的空间
	char* cd =  (char*)malloc(n*sizeof(char)); // 字符编码的临时存储空间
	cd[n-1] = '\0'; // 编码结束符
	for (i=1; i<=n; ++i) {
		start = n-1;
		// 从叶子到根逆向求每个字符的哈夫曼编码
		for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';	
		// 分配n-start个存储空间来保存编码
		HC[i] = (char*)malloc((n-start)*sizeof(char)); 
		strcpy(HC[i], &cd[start]);
		//printf("The code of HT[%d] is %s\n", i, HC[i]);
	}
	free(cd);
	return OK;
}

Status Select (HuffmanTree HT, int n, int* s1, int* s2){
	int i, j;
	for (i=1; i<=n; ++i)// 循环调用Select后有的结点已被使用，则不参与之后选择
		if(!HT[i].parent){ // 一旦找不到父结点就停止
			*s1 = i; // 找到比较的起点
			break;
		}
	for(j=i+1; j<=n; ++j)
		if(!HT[j].parent){
			*s2 = j;
			break;
		}
	for(i=1; i<=n; ++i) // 找到权值最小的结点，且不能为要找的另一个结点
		if(HT[*s1].weight>HT[i].weight && !HT[i].parent && (*s2!=i))
			*s1 = i;
	for(j=1; j<=n; ++j)
		if(HT[*s2].weight>HT[j].weight && !HT[j].parent && (*s1!=j))
			*s2 = j;
	if(s1>s2){ // 让s1最小，s2比s1大
		int temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}
	return OK;
}

Status HuffmanDeCoding (HuffmanTree HT, char * deCoding, int n){ //解码函数
	int p = 2*n-1; // 将p置为根节点
	int i = 0;
	while(deCoding[i]!='\0') {
		/* 当还没有到达哈夫曼树的叶子并且要解码的字符串没有结束时 */
		while((HT[p].lchild !=0 && HT[p].rchild!=0) && deCoding[i]!='\0') {
			if(deCoding[i]=='0')

				p=HT[p].lchild; // 如果是0，则叶子在左子树
			else
				p=HT[p].rchild;	// 如果是1，则叶子在右子树
			//printf("cd[%d] = %c\tp = %d\n",i,deCoding[i],p);
			i++;
		}
		/* 如果到达哈夫曼树的叶子时 */
		if (HT[p].lchild==0 && HT[p].rchild==0)	{
			printf("%c",HT[p].ch);
			p=2*n-1;
		}
		else {  /* 如果编号为p的结点不是叶子，那么编码有错 */
			printf("\nError in decoding !\n");
			return ERROR;
		}
	}
	printf("\n");

    return OK;
}
