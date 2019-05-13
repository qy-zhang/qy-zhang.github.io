/**
 * @File : NSingleton.cpp
 * @Author : zhangqianyi
 * @Date : 2017/5/18 20:28
 * @Description :
N例模式，与单例模式相比，能够设置最多存在N个实例
 */
#include <iostream>

using namespace std;

class NSingleton {
public:
    static int count;
    static void setCount(int n) { count = n; }

    static NSingleton* GetInstance() {
        if (count <= 0) return NULL;
        --count;
        return new NSingleton;
    }
    static void DeleteInstance(NSingleton* pInstance) {
        delete pInstance; pInstance = NULL;
        ++count;
    }

private:
    NSingleton() { cout << "constructor" << endl; }
    ~NSingleton() { cout << "destructor" << endl; }
};

int NSingleton::count = 3;

int main(int argc, char const *argv[])
{
    NSingleton* s1 = NSingleton::GetInstance();
    NSingleton* s2 = NSingleton::GetInstance();
    NSingleton* s3 = NSingleton::GetInstance();

    NSingleton* s4 = NSingleton::GetInstance();
    if (s4 == NULL) cout << "s4 is NULL" << endl;
    else cout << "s4 is not NULL" << endl;

    NSingleton::DeleteInstance(s3);

    NSingleton* s5 = NSingleton::GetInstance();
    if (s5 == NULL) cout << "s5 is NULL" << endl;
    else cout << "s5 is not NULL" << endl;

    return 0;
}