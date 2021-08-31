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
#include "server.h"
#include "threadpool.hpp"
#include "task.h"
class tcpserver : public server{
public:
    
    tcpserver(threadpool<task>* p);
    bool connect();
    bool dealMsg(const char* msg);
private:
    threadpool<task>* pool;
};

