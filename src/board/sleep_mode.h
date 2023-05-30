#include <Arduino.h>
#ifndef SLEEP_ADC
#define SLEEP_ADC
static void sleep(const uint16_t& sleep_time){
    ESP.deepSleep(sleep_time);
}
#endif