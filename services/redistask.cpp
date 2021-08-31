#include "redistask.h"


redisTask::redisTask(redisServer*c,redisCommandType type,std::string key,std::string value){

  m_redis = c;
  m_Type = type;
  m_sKey = key;
  m_sValue = value;
}

void redisTask::process(){
    
    printf("redis_type:%d\n", m_Type);
    printf("redis_key:%s\n", m_sKey.c_str());
    printf("redis_value:%s\n",m_sValue.c_str());
    if(m_redis == NULL)
        return;
    m_redis->setString(m_sKey,m_sValue);
    //redisReply *reply;
    //reply = (redisReply*)redisCommand(m_redis,"set %s %s", m_sKey.c_str(), m_sValue.c_str());

}
