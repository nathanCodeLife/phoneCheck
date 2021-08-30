#include "simpletask.h"
#include <cstdio>
#include <cstring>

simpleTask::simpleTask(const char * data)
{

    m_data = data;
}


void simpleTask::process()
{
    printf("task  %d\n", strlen(m_data));
}
