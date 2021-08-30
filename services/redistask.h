#include "task.h"
#include <string>

class redisTask: public task{
public:
    redisTask(int type, std::string key, std::string value);
    void process();
private:
    int m_iType;
    std::string m_sKey;
    std::string m_sValue;
};
