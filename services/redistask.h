#include "task.h"
#include <string>
enum redisCommandType{
    READSTRING,
    WRITESTRING,
};
class redisTask: public task{
public:
    redisTask(redisCommandType type, std::string key, std::string value);
    void process();
private:
    redisCommandType m_Type;
    std::string m_sKey;
    std::string m_sValue;
};
