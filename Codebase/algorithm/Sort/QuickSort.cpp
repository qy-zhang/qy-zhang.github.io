#include <iostream>
#include <vector>
using namespace std;

int partition1(int a[], int low, int high) {
    int pivotkey = a[low];
    while (low < high) {
        while (low < high && a[high] > pivotkey) --high;
        a[low] = a[high];
        while (low < high && a[low] < pivotkey) ++low;
        a[high] = a[low];
    }
    a[low] = pivotkey;
    return low;
}

int partition2(vector<int>& a, int low, int high) {
    int pivotkey = a[low];
    int loc = low;
    for (int i = low + 1; i <= high; ++i) {
        if (a[i] < pivotkey) {
            swap(a[i], a[++loc]);
        }
    }
    swap(a[low], a[loc]);
    return loc;
}

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a > b ? b : a; }
inline int midOfThree(int a, int b, int c) { return min(max(a, b), max(min(a, b), c)); }
int partition3(vector<int>& a, int low, int high) {
    int pivotkey = midOfThree(a[low], a[(low+high)/2], a[high]);
    int index = low;
    if (a[low] == pivotkey) index = low;
    else if (a[(low + high) / 2] == pivotkey) index = (low + high) / 2;
    else index = high;

    //先将枢纽值与a[low]交换，然后按照以a[low]为枢纽值的方式做就行了
    swap(a[index], a[low]);
    int loc = low;
    for (int i = low + 1; i <= high; ++i) { //比枢纽元小的元素依次放在前半部分
        if (a[i] < pivotkey) {
            swap(a[i], a[++loc]);
        }
    }
    swap(a[low], a[loc]);
    return loc;
}

void QSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int pivotloc = partition3(a, low, high);
        QSort(a, low, pivotloc-1);
        QSort(a, pivotloc+1, high);
    }
}

int main(int argc, char const *argv[])
{
	vector<int> a{ 3, 2, 4, 5, 1, 8, 7, 6 };
	QSort(a, 0, a.size() - 1);
	for (auto i : a) cout << i << "\t";
	cout << endl;

	return 0;
}