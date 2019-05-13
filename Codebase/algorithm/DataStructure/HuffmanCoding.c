#include "HuffmanCoding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;

	FILE * fp = fopen("HuffmanText.txt", "r"); // ���ļ��ж�ȡ�ַ������ÿ���ַ���Ȩֵ
	char character = getc(fp); // fgets�������ļ��ж�ȡ�ַ�
	int w[26] = {0}; // �������鱣��26���ַ���Ȩֵ
	while (character != EOF) { // һֱ��ȡÿ���ַ���ֱ�������ļ�������
		if (character>='a' && character<='z')
			w[(character-'a')]++;
		if (character>='A' && character<='Z')
			w[(character-'A')]++;
		character = getc(fp); // ����ȡһ���ַ�
	}
	fclose(fp);

	HuffmanCoding(HT, HC, w, 26);
	for(int i=1; i<=26; ++i){ // �����Ϣ
		printf("HT[%2d] ��ʾ���ַ�Ϊ��%c\t", i, i+96);
		printf("ȨֵΪ�� %d\t", *(w+i-1));
		printf("�ı���Ϊ�� %s\n", HC[i]);
	}

	int opt=0;
	char ch[255]={0};
	for (; ;){ // ѡ��������б������
		printf("\n\n\n    ��ѡ�������\n");
		printf("    1.����\n");
		printf("    2.����\n");
		printf("    3.�˳�\n");
		printf("    ��ѡ��");
		scanf("%d", &opt);
		if (opt==1)	{
			printf("    ��������Ҫ������ַ�����");
			scanf("%s",ch);
			printf("    ���ַ����ĺշ�������Ϊ��");
			for(int l=0;l<255;l++)		{
				if(ch[l]==0) break;
				printf("%s",HC[(ch[l]-96)]); // �����ch[1] - 96������ı���ֵ
			}
		}
		else if(opt==2)	{
			printf("    ��������Ҫ������ַ�����");
			scanf("%s", ch);
			printf("    ���ַ����Ĺ���������Ϊ��");
			HuffmanDeCoding(HT,ch,26);
		}
		else if(opt==3)	{
			printf("    �ɹ��˳�!");
			break;
		}
		else
			printf("    ��������Ч������");
	}
	return 0;
}
