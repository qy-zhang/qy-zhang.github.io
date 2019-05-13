/**
 * @File : CycleQueue.cpp
 * @Author : zhangqianyi
 * @Date : 2017/6/12 19:19
 * @Description :
循环队列C++实现，包括初始化，入队、出队、判断是否为空、是否为满
循环队列判断是否为空：front == rear
循环队列判断是否为满：(rear+1) % MAXQSIZE = front
少用一个存储空间，也就是数组的最后一个存数空间不用
头尾指针向后移动的时候要注意防止溢出(rear+1)%MAXQSIZE
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