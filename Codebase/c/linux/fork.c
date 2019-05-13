/**
 * @File : fork.c
 * @Author : zhangqianyi
 * @Date : 2017/8/1 10:03
 * @Description : fork、wait使用
 fork函数创建一个子进程，在子进程中pid == 0
 

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fail to fork!");
        exit(-1);
    }
    else if (pid == 0)
    {
        printf("child process, pid:%u, ppid:%u\n", getpid(), getppid());
        sleep(1);
        exit(0);
    }
    else
    {
        printf("parent process, pid:%u, ppid:%u, child id:%u\n", getpid(), getppid(), pid);
        pid_t pr = wait(NULL);
        printf("parent process, catch a child process with pid:%u\n", pr);
    }
    return 0;
}