/*ʵ��3�����򣩣���һ�ļ��ж�ȡ�������֣���дһ����ʵ�ֶ�����п�������
�����߶����򣩣������������ͱȽϴ�������Ϣд�뵽����ļ���ȥ��
Ҫ����нϺõ��˻�����������̡�*/

#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;  // ��������������������
#define MAXSIZE 100     // �����������е���󳤶�
typedef struct SqList {  // ��������
    KeyType r[MAXSIZE+1];
	int length;			// �������еĳ��ȣ���0���
} SqList;
// ����һ��ȫ�ֱ�������Ƚϴ���
int compCount = 0;

int Compare (int i, int j) {
    // ����ȽϺ���������i��Ԫ�ص�ֵС�ڵ�j��Ԫ�ص�ֵ�� ������
    // ͬʱ��compareʱ�ͰѱȽϴ�����һ����¼�Ƚϴ���
    compCount++;
    return i<j;
}

int Partition (SqList &L, int low, int high) {
    //����˳���L���ӱ�r[low..high]�ļ�¼����Ŧ��¼��λ��������������λ��
    //��ʱ����֮ǰ�ļ�¼����������
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
    //��˳���L�е�������L.r[low..high]����������
    if (low<high) {
		int pivotkey = Partition(L, low, high);
        QSort(L, low, pivotkey-1);
        QSort(L, pivotkey+1, high);
    }
}

int main(){
    SqList L;
    int i = 1;

	FILE * fp_Sort = fopen("Sort.txt", "r"); // ���ļ��ж���Ҫ�����Ԫ��
	int temp;
	fscanf(fp_Sort, "%d", &temp);
	while (!feof(fp_Sort)) {
		L.r[i] = temp;
		++i;
		fscanf(fp_Sort, "%d", &temp);
	}
	fclose(fp_Sort);
	L.length = i-1; // i��1ȡ�����i�����1

	QSort(L, 1, L.length);
	printf("�����Ľ��Ϊ��\n");
	for(i=1; i<=L.length; ++i)
		printf("%d\t", L.r[i]);
	printf("\n�Ƚϴ���Ϊ��%d\n", compCount);

	FILE * fp_Info = fopen("Info.txt", "wt+"); // ���ļ���д��Ҫ�����Ľ���Լ��������
	int space = 32;
	int cr = 13;
	fprintf(fp_Info, "%s", "�Ƚ�֮�������Ϊ��");
	for (i=1; i<=L.length; ++i){
		fprintf(fp_Info, "%d", L.r[i]);
		fprintf(fp_Info, "%c", space);
	}
	fprintf(fp_Info, "%c", cr);
	fprintf(fp_Info, "%s", "�Ƚϴ���Ϊ��");
	fprintf(fp_Info, "%d", compCount);
	fclose(fp_Info);
    getchar();
    return 0;
}
