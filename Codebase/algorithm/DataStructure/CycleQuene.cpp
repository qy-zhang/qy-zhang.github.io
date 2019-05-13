/**
 * @File : CycleQueue.cpp
 * @Author : zhangqianyi
 * @Date : 2017/6/12 19:19
 * @Description :
ѭ������C++ʵ�֣�������ʼ������ӡ����ӡ��ж��Ƿ�Ϊ�ա��Ƿ�Ϊ��
ѭ�������ж��Ƿ�Ϊ�գ�front == rear
ѭ�������ж��Ƿ�Ϊ����(rear+1) % MAXQSIZE = front
����һ���洢�ռ䣬Ҳ������������һ�������ռ䲻��
ͷβָ������ƶ���ʱ��Ҫע���ֹ���(rear+1)%MAXQSIZE
 */

#include <iostream>
using namespace std;

const int maxn = 100;

template<class T>
class CycleQueue
{
private:
    unsigned int m_size;
    int m_front;
    int m_rear;
    T* m_data;
public:
    CycleQueue(unsigned int size) : m_size(size), m_front(0), m_rear(0)
    {
        m_data = new T[size];
    }
    ~CycleQueue()
    {
        delete[] m_data;
    }
    bool empty()
    {
        return m_front == m_rear;
    }
    bool full()
    {
        return m_front == (m_rear + 1) % m_size;
    }
    void push(T elem) throw(bad_exception)
    {
        if (full())
        {
            throw bad_exception();
        }
        m_data[m_rear] = elem;
        m_rear = (m_rear + 1) % m_size;
    }
    T pop() throw(bad_exception)
    {
        if (empty())
        {
            throw bad_exception();
        }
        T t = m_data[m_front];
        m_front = (m_front + 1) % m_size;
        return t;
    }
};

int main()
{
    CycleQueue<int> cq(5);
    cq.push(1);
    cq.push(2);
    cq.push(3);
    cq.push(4);

    for (int i = 0; i < 4; ++i)
    {
        cout << cq.pop() << endl;
    }
    cq.push(5);
    cout << cq.pop() << endl;
    return 0;
}