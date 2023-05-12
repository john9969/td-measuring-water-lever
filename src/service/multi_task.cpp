#include "multi_task.h"
Multi_Task multi_task;

Multi_Task::Multi_Task(){
    this->controll = new ThreadController();
}
bool Multi_Task::add_new_task(void (*call_back)(), const unsigned long & interval){
    Thread* p_new_thread = new Thread();
    p_new_thread->enabled = true;
    p_new_thread->onRun(call_back);
    p_new_thread->setInterval(interval);
    controll->add(p_new_thread);
    return true;
}
void Multi_Task::run(){
   this->controll->run();
}