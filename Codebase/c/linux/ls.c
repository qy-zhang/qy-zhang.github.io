/**
 * @File : ls.c
 * @Author : zhangqianyi
 * @Date : 2017/08/09 09:30
 * @Description : 实现列出文件目录命令ls（list segment）
 通过调用几个函数实现
 DIR * opendir(const char * name);
 struct dirent* readdir(DIR* dir);
 int closedir(DIR* dir);
 opendir函数用来打开参数name指定的目录，并返回DIR*形态的目录流，和open函数类似
 readdir函数返回参数dir目录流的下一个目录进入点
 closedir函数关闭参数dir所指的目录流
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    DIR * dp;
    struct dirent* dirp;

    if (argc != 2) {
        printf("usage: ls directory_name!\n");
        exit(-1);
    }

    if ((dp = opendir(argv[1])) == NULL) {
        printf("can't open %s!\n", argv[1]);
        exit(-1);
    }

    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);

    return 0;
}