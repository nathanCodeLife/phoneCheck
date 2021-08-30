#include "redistask.h"


redisTask::redisTask(int type,std::string key,std::string value){

  m_iType = type;
  m_sKey = key;
  m_sValue = value;
}

void redisTask::process(){


}
