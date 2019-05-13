#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define PORT 8888
#define SERV "127.0.0.1"
#define BUFF 1024

int main()
{
    // 定义socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 定义sockaddr_in
    struct sockaddr_in skaddr;
    skaddr.sin_family = AF_INET;
    skaddr.sin_port   = htons(PORT);
    skaddr.sin_addr.s_addr = inet_addr(SERV);

    if(connect(sockfd,(struct sockaddr *)&skaddr, sizeof(skaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    char sendbuff[BUFF];
    char recvbuff[BUFF];
    while(fgets(sendbuff, sizeof(sendbuff), stdin) != NULL) {
        send(sockfd, sendbuff, strlen(sendbuff), 0);
        if( strcmp(sendbuff,"exit\n") == 0) break;
        recv(sockfd, recvbuff, sizeof(recvbuff), 0);
        fputs(recvbuff,stdout);

        memset(sendbuff, 0, sizeof(sendbuff));
        memset(recvbuff, 0, sizeof(recvbuff));
    }
    close(sockfd);
    return 0;
}
