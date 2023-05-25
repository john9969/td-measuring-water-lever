#include "log_data.h"
#include "app_send_data.h"
static void app_inti(){
    multi_task.add_new_task(app_process,TIMER_APP_PROCESS);
    multi_task.add_new_task(blink_led, TIMER_BLINK_LED);
}