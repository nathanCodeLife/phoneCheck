#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

class server{
public:
    virtual bool connect()=0;
//private:
    int state;
    int sockfd;
    int connfd;
    int port;
    char* ip_addr;
};
