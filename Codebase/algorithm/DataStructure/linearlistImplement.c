#include "linearlist.h"
#include <stdio.h>
#include <stdlib.h>

Status createList(LinkList L, int n) {
	// ��������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
	// ���������
	LinkList p;
	int i;
	L->next = NULL;

	printf("Please input the element of the linear list:\n");	
    for (i=n; i>0; --i)	{
		p = (LNode*)malloc(sizeof (LNode));// ����һ�������ڴ�
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
    
	return OK;
}

Status searchList (LinkList L, int i, ElemType e) {
	// ������L�в���Ԫ��e���Ѳ鵽��λ�ñ��浽Ԫ��i��,��û����iΪ0
	LinkList p = L;
	int j = 0;
	while (p) { // ����Ѱ��Ԫ��
		if (p->data == e){ //�ҵ�
			i = j; // �Ѹ�Ԫ�ص�λ�ñ��浽i�У�ֱ���˳�ѭ��
			break;
		}
		j++;
		p = p->next;
		i = 0; // ÿ�ζ���i��0����ѭ������i����0
	}
	if (!i)
		printf("No such element!\n");
	else
		printf("The index of  element you want to search is %d\n", i);
	return OK;
}

Status insertList (LinkList L, int i, ElemType e) {
	// ������ĵ�i��λ�ò���Ԫ��e
	LinkList p = L;
	int j = 0;
	while (p && j < i-1) { // ��p�ƶ���Ҫ�����ǰһ��λ��
		p = p->next;
		++j;
	}
	if (!p || j>i-1) { // �����λ�ó������Ȼ�������iΪ����
		printf("ERROR! please input valid parameters!\n");
		return ERROR;
	}
	LinkList s = (LinkList) malloc (sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s; // �������
	return OK;
}

Status deleteList (LinkList L, int i, ElemType* e) {
	// ɾ������ĵ�i��Ԫ�أ�����e������ֵ
	LinkList q, p = L;
	int j = 0;
	while (p->next && j<i-1) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i-1)// �����λ�ó������Ȼ�������iΪ����
		return ERROR;
	q = p->next; p->next = q->next;	*e = q->data;
	free(q);// ɾ������
	return OK;
}

Status reverseList(LinkList L) {
	// ����ľ͵�����
	LinkList p = L->next, q;
	L->next = NULL;
	while (p) { // ���ò���
		q = p;	p = p->next;
		q->next = L->next;	L->next = q;
	}
	return OK;
}

Status traverseList (LinkList L) {
	// �����������
	LinkList p = L;
	while (p->next){
		printf("%d ->", p->next->data);
		p = p->next;
	}
	printf("NULL\n");
	return OK;
}
