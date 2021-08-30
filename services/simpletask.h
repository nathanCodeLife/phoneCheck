#include "task.h"


class simpleTask: public task{
public:
    simpleTask(const char*data);
    void process();
private:
    const char* m_data;
};
