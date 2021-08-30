#include "threadpool.hpp"
#include "tcpserver.h"
#include "task.h"
int main(){
    threadpool<task>* pool = new threadpool<task>;
    tcpserver* server = new tcpserver(pool);
    server->connect();
    return 0;
}
