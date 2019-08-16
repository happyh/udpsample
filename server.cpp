/*************************************************************************
    > File Name: server.c
    > Author: happyhe
    > Mail: heguang@qiyi.com
    > Created Time: Thu 15 Aug 2019 02:25:17 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>

typedef struct sockaddr* saddrp;

int main(int argc, char *argv[])
{
    int nSendBufferSize = 1024;
    int nSendCount= 1000;
    unsigned short nPort = 5050;
    std::string strServerName;
    int ch;
    while ((ch = getopt(argc, argv, "s:p:n:b:")) != -1)
    {
        switch(ch) {
        case 'p':
            nPort = atoi(optarg);
            break;
        case 's':
            strServerName = optarg;
            break;
        case 'n':
            nSendCount = atoi(optarg);
            break;
        case 'b':
            nSendBufferSize = atoi(optarg);
            break;
        case 'h':
            printf("Usage: %s -s 10.10.10.10 [-p 5050 -n 1000 -b 1024]\n", argv[0]);
            exit(0);
            break;
        case '?':
            printf("Unknown option: %c\n",(char)optopt);
            break;
        }
    }

    if (nPort == 0 || strServerName == "")
    {
        printf("Usage: %s -s 10.10.10.10 [-p 5050 -n 1000 -b 1024]\n", argv[0]);
        exit(0);
    }


    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (0 > sockfd)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(nPort);
    addr.sin_addr.s_addr = inet_addr(strServerName.c_str());

    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buf[1024*10] = {0};
    int i = 0;
    while(i < nSendCount)
    {
        int r = sendto(sockfd,buf,nSendBufferSize,0,(saddrp)&addr,sizeof(addr));
        if (r < nSendBufferSize)
        {
            printf("send failed,r:%d\n",r);
        }
        i++;
    }
    close(sockfd);
    return 0;
}
