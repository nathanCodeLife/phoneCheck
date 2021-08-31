#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include "tcpserver.h"
#include "simpletask.h"
#include "redistask.h"

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 255

enum msgType{
    SIMPLE,
    REDIS
};
static int setnonblocking( int fd )
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

static void addfd( int epollfd, int fd)
{
    epoll_event event;
    event.data.fd= fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd ,&event );
    setnonblocking(fd);
}
tcpserver::tcpserver(threadpool<task> *p)
{
    pool = p;
}
bool tcpserver::connect()
{
    const char* ip = "127.0.0.1";
    int port = 8001;
    int ret= 0 ;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    //inet_pton(AF_INET,ip ,&address.sin_addr);
    address.sin_addr.s_addr = htons(INADDR_ANY);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    ret = bind(listenfd, (struct sockaddr*)&address,sizeof(address));
    if(ret <0)
    {
       printf("bind error\n");
    }
    ret = listen(listenfd,5);
    if(ret < 0 )
    {
       printf("listen error");

    }
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    addfd(epollfd, listenfd);
    while(1)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER,-1);
        if(number <0)
        {
            printf("epoll failure \n");
            break;
        }
        for(int i = 0; i<number;i++)
        {
            int sockfd = events[i].data.fd;
            if( sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept( listenfd,(struct sockaddr*)&client_address,&client_addrlength);
                if(connfd<0)
                    printf("connect err\n");
                addfd(epollfd, connfd);

                printf("conn sucess");
            }
            else if ( events[i].events &EPOLLIN)
            {
                    char buf[BUFFER_SIZE];
                    memset(buf,0, BUFFER_SIZE);
                    ret = recv(sockfd,buf,BUFFER_SIZE,0);
                    if(ret<0)
                    {
                        printf("recv error");
                        close(sockfd);
                        break;
                    }
                    else
                    {   
                        //task* ptask = new simpleTask(buf);
                        //pool->append(ptask);
                        
                        printf("tcp %s\n",buf);
                        dealMsg(buf);
                    }
            }
            else
            {
                printf("something else ");
            }
        }
     }
    close( listenfd);
    return 0;
}

bool tcpserver::dealMsg(const char* buff)
{
    int msglen = strlen(buff);
    //if(msglen !=)
    char key[256];
    char value[256];
    msgType t = static_cast<msgType>(buff[0]-'0');
    redisCommandType subType = static_cast<redisCommandType>(buff[1]-'0');
    int len1 = buff[2]-'0';
    int len2 = buff[3]-'0';
    memset(key,0,255);
    memset(value,0,255);

    memcpy(key,&buff[4],len1);
    memcpy(value,&buff[4+len1],len2);
    redisTask* pCommand = new redisTask(subType,key,value);
    pool->append(pCommand);
}

