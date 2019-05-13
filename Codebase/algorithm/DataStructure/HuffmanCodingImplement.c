#include "HuffmanCoding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status HuffmanCoding (HuffmanTree HT, HuffmanCode HC, int* w, int n) {
	// w���n���ַ���Ȩֵ(��>0)�������������HT�������n���ַ��Ĺ���������HC
	int i;
    int m = 2*n-1;
	if (n<=1) return ERROR; // �ַ���С��1���˳�
    //	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));  //0�ŵ�Ԫδ��
	// ��ʼ����������
	for (i=1; i<=n; ++i, ++w) {
		HT[i].ch = i+96; // ǰn�������ַ�ֵ��Ϊa��b����
		HT[i].weight = *w; // ǰn������Ȩֵ��Ϊw
		HT[i].lchild = 0; HT[i].rchild = 0; HT[i].parent = 0;
	}
	for (i=n+1; i<=m; ++i){ // �������Ϊ0
		HT[i].weight = 0; HT[i].lchild = 0; HT[i].rchild = 0; HT[i].parent = 0;
	}
	// ��������������ҽ��
	int* s1 = (int*)malloc(sizeof(int));
    int* s2 = (int*)malloc(sizeof(int));
	for (i=n+1; i<=m; ++i){
		Select(HT, i-1, s1, s2); // ��i-1��������ҵ���С��û��ʹ�õ��������
		HT[*s1].parent = i; HT[*s2].parent = i;
		HT[i].lchild = *s1; HT[i].rchild = *s2;
		HT[i].weight = HT[*s1].weight + HT[*s2].weight;
	}
	// ����������
	int start, f;
	unsigned int c;
	HC = (HuffmanCode)malloc((n+1) * sizeof(char*)); // ����n���ַ�����Ŀռ�
	char* cd =  (char*)malloc(n*sizeof(char)); // �ַ��������ʱ�洢�ռ�
	cd[n-1] = '\0'; // ���������
	for (i=1; i<=n; ++i) {
		start = n-1;
		// ��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
		for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent)
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';	
		// ����n-start���洢�ռ����������
		HC[i] = (char*)malloc((n-start)*sizeof(char)); 
		strcpy(HC[i], &cd[start]);
		//printf("The code of HT[%d] is %s\n", i, HC[i]);
	}
	free(cd);
	return OK;
}

Status Select (HuffmanTree HT, int n, int* s1, int* s2){
	int i, j;
	for (i=1; i<=n; ++i)// ѭ������Select���еĽ���ѱ�ʹ�ã��򲻲���֮��ѡ��
		if(!HT[i].parent){ // һ���Ҳ���������ֹͣ
			*s1 = i; // �ҵ��Ƚϵ����
			break;
		}
	for(j=i+1; j<=n; ++j)
		if(!HT[j].parent){
			*s2 = j;
			break;
		}
	for(i=1; i<=n; ++i) // �ҵ�Ȩֵ��С�Ľ�㣬�Ҳ���ΪҪ�ҵ���һ�����
		if(HT[*s1].weight>HT[i].weight && !HT[i].parent && (*s2!=i))
			*s1 = i;
	for(j=1; j<=n; ++j)
		if(HT[*s2].weight>HT[j].weight && !HT[j].parent && (*s1!=j))
			*s2 = j;
	if(s1>s2){ // ��s1��С��s2��s1��
		int temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}
	return OK;
}

Status HuffmanDeCoding (HuffmanTree HT, char * deCoding, int n){ //���뺯��
	int p = 2*n-1; // ��p��Ϊ���ڵ�
	int i = 0;
	while(deCoding[i]!='\0') {
		/* ����û�е������������Ҷ�Ӳ���Ҫ������ַ���û�н���ʱ */
		while((HT[p].lchild !=0 && HT[p].rchild!=0) && deCoding[i]!='\0') {
			if(deCoding[i]=='0')

				p=HT[p].lchild; // �����0����Ҷ����������
			else
				p=HT[p].rchild;	// �����1����Ҷ����������
			//printf("cd[%d] = %c\tp = %d\n",i,deCoding[i],p);
			i++;
		}
		/* ����������������Ҷ��ʱ */
		if (HT[p].lchild==0 && HT[p].rchild==0)	{
			printf("%c",HT[p].ch);
			p=2*n-1;
		}
		else {  /* ������Ϊp�Ľ�㲻��Ҷ�ӣ���ô�����д� */
			printf("\nError in decoding !\n");
			return ERROR;
		}
	}
	printf("\n");

    return OK;
}
