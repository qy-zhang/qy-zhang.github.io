//
// Created by zhangqianyi on 2017/7/6.
//

#ifndef DESIGNPATTERN_SINGLETON_H
#define DESIGNPATTERN_SINGLETON_H

#include <iostream>

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 懒汉型非线程安全单例模式，直到首次用到实例的时候才去创建
 */
class SingletonLazy {
public:
    static SingletonLazy& GetInstance();
    void showMessage() { std::cout << "message from SingletonLazy" << std::endl; }
private:
    SingletonLazy() {}
    static SingletonLazy* m_instance;
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 饿汉型单例模式，首次加载类的时候就创建实例，一直存在
 */
class SingletonHungry {
public:
    static SingletonHungry& GetInstance() { return *m_instance; }
    void showMessage() { std::cout << "message from SingletonHungry" << std::endl; }
private:
    SingletonHungry() {}
    static SingletonHungry* m_instance;
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief 懒汉型线程安全单例模式，C++11之后要求编译器保证内部静态变量的线程安全性。最好的实现方式，可作为模板使用
 */
class SingletonInside {
public:
    static SingletonInside& GetInstance() {
        static SingletonInside singletonInside;
        return singletonInside;
    }
private:
    SingletonInside() {}
};

/**
 * @author zhangqianyi
 * @date 2017/7/6
 * @brief N例模式，当创建一个实例的时候count减1，销毁一个实例的时候count加1。count减为0的时候不再创建实例，直接返回NULL。
 */
class NSingleton {
public:
    static NSingleton* GetInstance() {
        if (instanceCount <= 0) return NULL; // 已经存在了N个实例，不再创建实例，直接返回NULL
        --instanceCount; // 创建一个实例，计数减1
        return new NSingleton;
    }
    static void DeleteInstance(NSingleton* pInstance) {
        delete pInstance;
        pInstance = NULL;
        ++instanceCount; // 销毁一个实例，count加1
    }
private:
    NSingleton() {}
    static int instanceCount;
};

#endif //DESIGNPATTERN_SINGLETON_H
