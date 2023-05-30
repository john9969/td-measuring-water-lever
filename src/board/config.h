#include <Arduino.h>


#define LASER_BAURATE                   19200
#define OLAX_PIN                        4
#define LED                             2


#define MAX_NUMBER_VALUE_WATER_LEVER    3
#define TIME_OUT_CONNECT_WIFI           100UL  //times   
#define TIMES_CONNECT_WIFI              3
#define HEART_BIT_CLOCK                 1000UL //ms
#define TIMER_CHECK_UART_PORT           2000UL   //ms
#define TIMER_BLINK_LED                 500UL   //ms

#define TIMEOUT_OFF_WIFI                10
#define DBln                            Serial.println
#define DB                              Serial.print
#define PASS                            "j12345678"
#define SSID1                           "laser_sensor"
