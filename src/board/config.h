#include <Arduino.h>


#define LASER_BAURATE                   19200
#define OLAX_PIN                        4
#define LED                             LED_BUILTIN
#define LED_INIT                        pinMode(LED,OUTPUT);
#define LED_TOGGLE                      digitalWrite(LED, !digitalRead(LED));
#define LED_SIGNAL                      LED_BUILTIN
#define TIME_OUT_CONNECT_WIFI           100UL  //times   
#define HEART_BIT_CLOCK                 1000UL //ms
#define TIMER_CHECK_UART_PORT           100UL   //ms
#define SSID                            "laser_sensor"
#define PASS                            "j12345678"
#define TIMEOUT_OFF_WIFI                10
#define DBln                            Serial.println
#define DB                              Serial.print
