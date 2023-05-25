#ifndef BLINK_LED_H
#define BLINK_LED_H

#include <Arduino.h>
#include "config.h"
#define LED_INIT                        pinMode(LED,OUTPUT);
#define LED_TOGGLE                      digitalWrite(LED, !digitalRead(LED));
class Blink_Led
{
private:
    int timeout;
public:
    Blink_Led(){
        this->timeout = 10;
    }
    void set_timeout(const int& timeout) { this->timeout = timeout;}
    int get_timeout() const{
        return this->timeout;
    }   
};
extern Blink_Led led_build_in;
extern void blink_led();
#endif
