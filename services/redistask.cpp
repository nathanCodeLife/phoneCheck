#include "redistask.h"


redisTask::redisTask(redisCommandType type,std::string key,std::string value){

  m_Type = type;
  m_sKey = key;
  m_sValue = value;
}

void redisTask::process(){
    
    printf("redis_type:%d\n", m_Type);
    printf("redis_key:%s\n", m_sKey.c_str());
    printf("redis_value:%s\n",m_sValue.c_str());

}
