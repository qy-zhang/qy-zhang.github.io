//
// Created by zhangqianyi on 2017/7/6.
//

#include "Singleton.h"

SingletonLazy* SingletonLazy::m_instance = NULL; // 懒汉型单例模式，直到首次用到实例的时候才去创建

SingletonLazy& SingletonLazy::GetInstance() {
    if (m_instance == NULL) { // 这里的操作是非线程安全的，多线程情况下可能会生成多个实例，需要使用double check计数
        m_instance = new SingletonLazy;
    }
    return *m_instance;
}


SingletonHungry* SingletonHungry::m_instance = new SingletonHungry(); // 饿汉型单例模式，首次加载类的时候就创建实例，一直存在

int NSingleton::instanceCount = 3; // N例模式最多存在3个实例