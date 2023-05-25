#include "blink_led.h"
Blink_Led led_build_in;
void blink_led(){
    static int timeout = led_build_in.get_timeout();
    if(timeout > 0) {
        timeout--;
        return;
    }
    LED_TOGGLE
    timeout = led_build_in.get_timeout();
}