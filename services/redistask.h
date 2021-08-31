#include "task.h"
#include "hiredis.h"
#include <string>
#include "redisserver.h"
enum redisCommandType{
    READSTRING,
    WRITESTRING,
};
class redisTask: public task{
public:
    redisTask(redisServer*c,redisCommandType type, std::string key, std::string value);
    void process();
private:
    redisServer* m_redis;
    redisCommandType m_Type;
    std::string m_sKey;
    std::string m_sValue;
};
