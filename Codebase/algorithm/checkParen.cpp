/**
 * @File : checkParent.c
 * @Author : zhangqianyi
 * @Date : 2017/4/25 16:03
 * @Description :
括号匹配，使用栈stack实现
思路：遇到一个左括号压栈，遇到一个右括号弹栈（先判断是否栈为空），判断是否匹配
如果遍历完字符串最后栈为空，表示字符串括号匹配（或者字符串中没有任何括号，也是匹配）
 */

#include <iostream>
#include <stack>

using namespace std;

bool isParen(const string& str) {
    if (str.empty()) return false;
    stack<char> s;
    for (unsigned int i = 0; i < str.size(); ++i) {
        switch (str[i]) {
            case '(': s.push(str[i]); break;
            case '[': s.push(str[i]); break;
            case '{': s.push(str[i]); break;

            case ')':
                if (s.empty() || s.top() != '(') return false; // 要检测栈是否为空，防止弹空栈
                else s.pop();
                break;
            case ']':
                if (s.empty() || s.top() != '[') return false;
                else s.pop();
                break;
            case '}':
                if (s.empty() || s.top() != '{') return false;
                else s.pop();
                break;
            default: break;
        }
    }
    return s.empty();
}

int main()
{
    string str = "{(1,[2,3(4,5,6),7],8)}";

    cout << isParen(str) << endl;

    return 0;
}
