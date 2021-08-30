#include "threadpool.hpp"
#include "task.h"
int main(){
    threadpool<task>* pool = new threadpool<task>;
    return 0;
}
