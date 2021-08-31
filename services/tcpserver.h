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
#include "hiredis.h"
#include "redisserver.h"
class tcpserver : public server{
public:
    
    tcpserver(threadpool<task>* p);
    bool connect();
    bool dealMsg(const char* msg);
    redisServer * getFreeRedis();
    redisServer *m_redis; //tmp
private:
    threadpool<task>* pool;
};

