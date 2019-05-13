#include <iostream>

using namespace std;

void BigFactorial(int value) {
	int result[10000] = {0};
	result[0] = 1; // 初始值为1
	int result_size = 1; // 实时更新result的实际位数
	int carry = 0; // 进位

	for (int i = 2; i <= value; ++i) { // 对乘数的每一位进行乘法运算
		for (int j = 0; j < result_size; ++j) {
			// 计算进位，留下进位之后每一位的结果
			int temp = result[j] * i + carry;
			result[j] = temp % 10;
			carry = temp / 10;
		}
		// 乘数的一位计算完毕之后，进位到result的下一位
		while (carry != 0) {
			result[result_size] = carry % 10;
			carry /= 10;
			++result_size;			
		}
	}

	cout << "The factorial of " << value << " is : ";
	// 从最高位到最低位输出结果
	for (int i = result_size - 1; i >= 0; --i) {
		cout << result[i];
	}
	cout << endl;
}

int main()
{
	BigFactorial(6);
	return 0;
}