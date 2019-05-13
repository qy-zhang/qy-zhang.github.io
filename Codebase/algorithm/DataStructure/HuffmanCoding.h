/*从一文件中读取字符，分别统计该文件中英文字符ABCD…等26个数字的出现概率
并以各自的概率为权值，为这26个字符建立一颗哈夫曼树，并对每个字符进行哈夫
曼编码和哈夫曼解码。要求具有较好的人机交互处理过程。*/
#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

// this is what has been defined by default
#define OK 1
#define ERROR 0
typedef bool Status;

// this is what should be defined by user !
typedef struct { // 动态分配数组存储哈夫曼树
	char ch; // ch保存结点表示的字符
	unsigned int weight, parent, lchild, rchild;
} HTNode, * HuffmanTree;

typedef char ** HuffmanCode; // 动态分配数组存储哈夫曼编码表

Status HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int * w, int n);//编码函数
Status Select (HuffmanTree &HT, int n, int &s1, int &s2); // 查找函数
Status HuffmanDeCoding (HuffmanTree &HT, char * deCoding, int n); //解码函数

#endif
