#ifndef _REDISSERVER_H_
#define _REDISSERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "string.h"
#include <hiredis.h>
#include "server.h"



class redisServer:public server{
public:
    bool connect();
    void setString(std::string key,std::string value);
private:
    redisContext *m_redis;
};



#endif
