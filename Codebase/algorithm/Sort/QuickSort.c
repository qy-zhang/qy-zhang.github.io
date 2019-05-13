/*实验3（排序）：从一文件中读取待排数字，编写一程序实现对其进行快速排序
（或者堆排序），并把排序结果和比较次数等信息写入到输出文件中去，
要求具有较好的人机交互处理过程。*/

#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;  // 定义排序对象的数据类型
#define MAXSIZE 100     // 定义排序序列的最大长度
typedef struct SqList {  // 定义序列
    KeyType r[MAXSIZE+1];
	int length;			// 定义序列的长度，第0项不算
} SqList;
// 定义一个全局变量保存比较次数
int compCount = 0;

int Compare (int i, int j) {
    // 定义比较函数，若第i个元素的值小于第j个元素的值， 返回真
    // 同时在compare时就把比较次数加一，记录比较次数
    compCount++;
    return i<j;
}

int Partition (SqList &L, int low, int high) {
    //交换顺序表L中子表r[low..high]的记录，枢纽记录到位，并返回其所在位置
    //此时在它之前的记录均不大于它
    L.r[0] = L.r[low];
    int pivotkey = L.r[low];
    while (low<high) {
		while (low<high && Compare(pivotkey, L.r[high])) --high;
        L.r[low] = L.r[high];
		while (low<high && Compare(L.r[low], pivotkey)) ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}

void QSort (SqList &L, int low, int high) {
    //对顺序表L中的子序列L.r[low..high]作快速排序
    if (low<high) {
		int pivotkey = Partition(L, low, high);
        QSort(L, low, pivotkey-1);
        QSort(L, pivotkey+1, high);
    }
}

int main(){
    SqList L;
    int i = 1;

	FILE * fp_Sort = fopen("Sort.txt", "r"); // 从文件中读入要排序的元素
	int temp;
	fscanf(fp_Sort, "%d", &temp);
	while (!feof(fp_Sort)) {
		L.r[i] = temp;
		++i;
		fscanf(fp_Sort, "%d", &temp);
	}
	fclose(fp_Sort);
	L.length = i-1; // i从1取起，最后i多加了1

	QSort(L, 1, L.length);
	printf("排序后的结果为：\n");
	for(i=1; i<=L.length; ++i)
		printf("%d\t", L.r[i]);
	printf("\n比较次数为：%d\n", compCount);

	FILE * fp_Info = fopen("Info.txt", "wt+"); // 向文件中写入要排序后的结果以及排序次数
	int space = 32;
	int cr = 13;
	fprintf(fp_Info, "%s", "比较之后的序列为：");
	for (i=1; i<=L.length; ++i){
		fprintf(fp_Info, "%d", L.r[i]);
		fprintf(fp_Info, "%c", space);
	}
	fprintf(fp_Info, "%c", cr);
	fprintf(fp_Info, "%s", "比较次数为：");
	fprintf(fp_Info, "%d", compCount);
	fclose(fp_Info);
    getchar();
    return 0;
}
