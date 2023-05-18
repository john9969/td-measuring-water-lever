#include <Arduino.h>
#include "board/laser_sensor.h"

#ifndef MEASURING
#define MEASURING

/*DEFINE HERE*/

//************************************************************************************

class Measuring {
private:
    double wl_local;
    double wl_remote;
    
public:
    Measuring();
    void init();
    bool start_measuring();
    double get_wl();
    double verify_value();
    String to_json();
};
extern Measuring measuring;
#endif