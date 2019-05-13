#include "HuffmanCoding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;

	FILE * fp = fopen("HuffmanText.txt", "r"); // 从文件中读取字符，算出每个字符的权值
	char character = getc(fp); // fgets函数在文件中读取字符
	int w[26] = {0}; // 定义数组保存26个字符的权值
	while (character != EOF) { // 一直读取每个字符，直到遇到文件结束符
		if (character>='a' && character<='z')
			w[(character-'a')]++;
		if (character>='A' && character<='Z')
			w[(character-'A')]++;
		character = getc(fp); // 向后读取一个字符
	}
	fclose(fp);

	HuffmanCoding(HT, HC, w, 26);
	for(int i=1; i<=26; ++i){ // 输出信息
		printf("HT[%2d] 表示的字符为：%c\t", i, i+96);
		printf("权值为： %d\t", *(w+i-1));
		printf("的编码为： %s\n", HC[i]);
	}

	int opt=0;
	char ch[255]={0};
	for (; ;){ // 选择操作进行编码解码
		printf("\n\n\n    请选择操作：\n");
		printf("    1.编码\n");
		printf("    2.解码\n");
		printf("    3.退出\n");
		printf("    请选择：");
		scanf("%d", &opt);
		if (opt==1)	{
			printf("    请输入需要编码的字符串：");
			scanf("%s",ch);
			printf("    该字符串的赫夫曼编码为：");
			for(int l=0;l<255;l++)		{
				if(ch[l]==0) break;
				printf("%s",HC[(ch[l]-96)]); // 输出第ch[1] - 96个代表的编码值
			}
		}
		else if(opt==2)	{
			printf("    请输入需要解码的字符串：");
			scanf("%s", ch);
			printf("    该字符串的哈弗曼解码为：");
			HuffmanDeCoding(HT,ch,26);
		}
		else if(opt==3)	{
			printf("    成功退出!");
			break;
		}
		else
			printf("    请输入有效参数！");
	}
	return 0;
}
