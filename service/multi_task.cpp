#include "multi_task.h"
Multi_Task::Multi_Task(){
    this->controll = new ThreadController();
}
 bool Multi_Task::init_new_task(void (*call_back)(), const uint8_t& interval){
    Thread p_new_thread = Thread();
    p_new_thread.onRun(call_back);
    p_new_thread.setInterval(interval);
    controll->add(&p_new_thread);

 }