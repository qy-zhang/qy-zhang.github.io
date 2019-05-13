#include "linearlist.h"
#include <stdio.h>
#include <stdlib.h>

Status createList(LinkList L, int n) {
	// 逆序输入n个元素的值，建立带表头结点的单链线性表L
	// 并输出链表
	LinkList p;
	int i;
	L->next = NULL;

	printf("Please input the element of the linear list:\n");	
    for (i=n; i>0; --i)	{
		p = (LNode*)malloc(sizeof (LNode));// 分配一个结点的内存
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
    
	return OK;
}

Status searchList (LinkList L, int i, ElemType e) {
	// 在链表L中查找元素e，把查到的位置保存到元素i中,若没有则i为0
	LinkList p = L;
	int j = 0;
	while (p) { // 遍历寻找元素
		if (p->data == e){ //找到
			i = j; // 把该元素的位置保存到i中，直接退出循环
			break;
		}
		j++;
		p = p->next;
		i = 0; // 每次都把i赋0，则循环结束i就是0
	}
	if (!i)
		printf("No such element!\n");
	else
		printf("The index of  element you want to search is %d\n", i);
	return OK;
}

Status insertList (LinkList L, int i, ElemType e) {
	// 在链表的第i个位置插入元素e
	LinkList p = L;
	int j = 0;
	while (p && j < i-1) { // 将p移动到要插入的前一个位置
		p = p->next;
		++j;
	}
	if (!p || j>i-1) { // 输入的位置超过长度或者输入i为负数
		printf("ERROR! please input valid parameters!\n");
		return ERROR;
	}
	LinkList s = (LinkList) malloc (sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s; // 插入操作
	return OK;
}

Status deleteList (LinkList L, int i, ElemType* e) {
	// 删除链表的第i个元素，并用e返回其值
	LinkList q, p = L;
	int j = 0;
	while (p->next && j<i-1) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i-1)// 输入的位置超过长度或者输入i为负数
		return ERROR;
	q = p->next; p->next = q->next;	*e = q->data;
	free(q);// 删除操作
	return OK;
}

Status reverseList(LinkList L) {
	// 链表的就地逆置
	LinkList p = L->next, q;
	L->next = NULL;
	while (p) { // 逆置操作
		q = p;	p = p->next;
		q->next = L->next;	L->next = q;
	}
	return OK;
}

Status traverseList (LinkList L) {
	// 遍历输出链表
	LinkList p = L;
	while (p->next){
		printf("%d ->", p->next->data);
		p = p->next;
	}
	printf("NULL\n");
	return OK;
}
