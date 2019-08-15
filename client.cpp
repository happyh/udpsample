#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctime>
#include <iostream>
#include <string>
#include <stdlib.h>

typedef struct sockaddr* saddrp;
int main(int argc, char *argv[])
{
    unsigned short nPort = 5050;
    int ch;
    while ((ch = getopt(argc, argv, "p:")) != -1)
    {
        switch(ch) {
        case 'p':
            nPort = atoi(optarg);
            break;
        case 'h':
            printf("Usage: %s [-p 5050]\n", argv[0]);
            exit(0);
            break;
        case '?':
            printf("Unknown option: %c\n",(char)optopt);
            break;
        }
    }

    //创建socket
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (0 > sockfd)
    {
        perror("sockfd");
        return -1;
    }
    //准备地址
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;//ipv4
    addr.sin_port = htons(nPort);//端口号
    addr.sin_addr.s_addr = INADDR_ANY;//我的ip地址
    //绑定
    int ret = bind(sockfd,(saddrp)&addr,sizeof(addr));
    if (0 > ret)
    {
        perror("bind");
        return -1;
    }
    struct sockaddr_in src_addr = {};
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buf[1024*10] = {};
    int i = 0;
    int receivedall = 0;
    while(1)
    {
        //接收数据和来源的ip地址
        int received = recvfrom(sockfd,buf,sizeof(buf),0,(saddrp)&src_addr,&addr_len);
        receivedall += received;
        i++;
        printf("recevie:%d receivedall:%d index:%d\n",received,receivedall,i);
    }
    //关闭socket对象
    close(sockfd);
    return 0;
}
