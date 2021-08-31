#include "redisserver.h"
#include <string>
#include "string.h"

bool  redisServer::connect()
{
    redisReply *reply;
    const char *hostname = "127.0.0.1";
    int port =  6379;

    struct timeval timeout = { 1, 500000 };
    m_redis = redisConnectWithTimeout(hostname, port, timeout);
    if (m_redis == NULL || m_redis->err) {
        if (m_redis) {
            printf("Connection error: %s\n", m_redis->errstr);
            redisFree(m_redis);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return 0;
    }
    const char*password ="kainan"; 
    reply = static_cast<redisReply*>(redisCommand(m_redis, "AUTH %s", password));
    return 1;
}
void redisServer::setString(std::string key,std::string value)
{
    redisReply *reply;
    reply = static_cast<redisReply*>(redisCommand(m_redis, "SET  %s %s", key.c_str(),value.c_str()));
    printf("set: %s\n",reply->str);
}
