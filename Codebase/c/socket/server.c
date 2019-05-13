#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h> // socket
#include <sys/types.h>  // 基本数据类型
#include <unistd.h> // read write
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> // open close
#include <sys/shm.h>

#define PORT 8888
#define SERV "127.0.0.1"
#define QUEUE 20
#define BUFF 1024

int main()
{
    // 定义 socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 定义 sockaddr_in
    struct sockaddr_in skaddr;
    skaddr.sin_family = AF_INET; // ipv4
    skaddr.sin_port   = htons(PORT);
    skaddr.sin_addr.s_addr = inet_addr(SERV);
    // bind，绑定 socket 和 sockaddr_in
    if(bind(sockfd,(struct sockaddr *)&skaddr,sizeof(skaddr)) == -1 ){
        perror("bind error");
        exit(1);
    }
    
    // listen，开始添加端口
    if(listen(sockfd,QUEUE) == -1 ){
        perror("listen error");
        exit(1);
    }
    
    // 客户端信息
    char buff[BUFF];
    struct sockaddr_in claddr;
    socklen_t length = sizeof(claddr);
    
    int conn = accept(sockfd,(struct sockaddr *)&claddr, &length);
    
    if(conn < 0){
        perror("accept error");
        exit(1);
    }
    
    while(1){
        memset(buff,0,sizeof(buff));
        int len = recv(conn,buff,sizeof(buff),0);
        if( strcmp(buff,"exit\n") ==0 ) break;
        fputs(buff,stdout);
        send(conn,buff,len,0);
    }
    close(conn);
    close(sockfd);
    return 0;
}