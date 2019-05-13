/**
 * @File : atexit.c
 * @Author : zhangqianyi
 * @Date : 2017/7/31 21:34
 * @Description : 比较进程退出函数_exit和exit
 atexit()函数用于注册终止函数(即main执行结束后调用的函数)，其原型为：
 `int atexit(void (*function)(void));`
 函数的参数是一个函数指针，函数指针指向一个没有参数也没有返回值的函数。
 很多时候我们需要在程序退出的时候做一些诸如释放资源的操作，这个时候就需要注册main函数执行完之后的函数了。

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fun1()
{
    printf("fun1 is called\n");
}

void fun2()
{
    printf("fun2 is called\n");
    // kill(getpid(), SIGINT); //如果这句话执行的话，在fun2的注册函数中就kill了进程，后续的注册函数不会被执行
}

void fun3()
{
    printf("fun3 is called\n");
}

int main()
{
    printf("main : \n");
    atexit(fun1); //参数是一个函数指针，并且函数参数和返回值必须是void，最多只能注册32个终止处理程序
    atexit(fun2); //atexit会按照注册的顺序逆序输出，输出顺序为3、2、1
    atexit(fun3);
    return 0;
}