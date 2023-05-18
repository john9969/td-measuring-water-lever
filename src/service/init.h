#include "multi_task.h"
#include "http_request.h"
#include "board/connect_internet.h"
#include "board/laser_sensor.h"
static void service_inti(){
    http_request.init();
    multi_task.add_new_task(checking_connection, HEART_BIT_CLOCK);
    multi_task.add_new_task(check_uart_available,TIMER_CHECK_UART_PORT);
    //multi_task.add_new_task(thread_test_two, HEART_BIT_CLOCK);
}
