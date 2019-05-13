/*�����Ա�������ʽ�洢�ṹʵ��һ�����Ա�ĳ�
���������ͣ���ʵ�����Ա�ĳ�ʼ�������ҡ����롢ɾ��
�;͵����õȲ�����Ҫ����нϺõ��˻������������*/
#ifndef LINEARLIST_H
#define LINEARLIST_H

// this is what has already been defined by default
typedef int Status;
#define OK 1
#define ERROR 0

// this is what should be defined by user !
typedef int ElemType;

typedef struct LNode { //������洢�ṹ��ʾ
	ElemType data;
	struct LNode * next;
} LNode, * LinkList;

Status createList (LinkList L, int n);// ��ʼ��
Status searchList (LinkList L, int i, ElemType e); // ����
Status insertList (LinkList L, int i, ElemType e);// ����
Status deleteList (LinkList L, int i, ElemType* e);//ɾ��
Status reverseList (LinkList L);//�͵�����
Status traverseList (LinkList L); // ����

#endif
