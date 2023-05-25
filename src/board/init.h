
#include "dcom_olax.h"
#include "connect_internet.h"
#include "laser_sensor.h"
#include "read_adc.h"
#include "sleep_mode.h"
#include "blink_led.h"
static void board_int(){
    DCOM_INIT
    LED_INIT
    DCOM_ON
    sensor.init();
    connection.wifi_init();
}