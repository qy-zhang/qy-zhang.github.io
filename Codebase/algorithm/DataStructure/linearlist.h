/*（线性表）：以链式存储结构实现一个线性表的抽
象数据类型，并实现线性表的初始化、查找、插入、删除
和就地逆置等操作，要求具有较好的人机交互处理过程*/
#ifndef LINEARLIST_H
#define LINEARLIST_H

// this is what has already been defined by default
typedef int Status;
#define OK 1
#define ERROR 0

// this is what should be defined by user !
typedef int ElemType;

typedef struct LNode { //单链表存储结构表示
	ElemType data;
	struct LNode * next;
} LNode, * LinkList;

Status createList (LinkList L, int n);// 初始化
Status searchList (LinkList L, int i, ElemType e); // 查找
Status insertList (LinkList L, int i, ElemType e);// 插入
Status deleteList (LinkList L, int i, ElemType* e);//删除
Status reverseList (LinkList L);//就地逆置
Status traverseList (LinkList L); // 遍历

#endif
