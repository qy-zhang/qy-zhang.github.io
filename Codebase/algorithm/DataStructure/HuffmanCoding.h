/*��һ�ļ��ж�ȡ�ַ����ֱ�ͳ�Ƹ��ļ���Ӣ���ַ�ABCD����26�����ֵĳ��ָ���
���Ը��Եĸ���ΪȨֵ��Ϊ��26���ַ�����һ�Ź�������������ÿ���ַ����й���
������͹��������롣Ҫ����нϺõ��˻�����������̡�*/
#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

// this is what has been defined by default
#define OK 1
#define ERROR 0
typedef bool Status;

// this is what should be defined by user !
typedef struct { // ��̬��������洢��������
	char ch; // ch�������ʾ���ַ�
	unsigned int weight, parent, lchild, rchild;
} HTNode, * HuffmanTree;

typedef char ** HuffmanCode; // ��̬��������洢�����������

Status HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int * w, int n);//���뺯��
Status Select (HuffmanTree &HT, int n, int &s1, int &s2); // ���Һ���
Status HuffmanDeCoding (HuffmanTree &HT, char * deCoding, int n); //���뺯��

#endif
