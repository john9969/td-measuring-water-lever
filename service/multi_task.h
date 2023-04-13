#include "Arduino.h"
#include <Thread.h>
#include <ThreadController.h>


#ifndef MULTI_TASK
#define MULTI_TASK

/*DEFINE HERE*/

//************************************************************************************

class Multi_Task {
private:
    ThreadController* controll;
    uint8_t total_task;        
public:
    Multi_Task();
    bool init_new_task(void (*call_back)(),const uint8_t& interval);

};

#endif