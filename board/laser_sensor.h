#include "Arduino.h"
#ifndef LASER_SENSOR_H
#define LASER_SENSOR_H

class laser_sensor {
    
public:
    void init();
    laser_sensor();
    void activate();
    double read_distance(const int& timeout);

public:
    void set_distance( const double& distance);
    double get_distance() const;
    void set_is_activated(const bool& is_activated);
    bool get_is_activated() const;
  
private:
    bool is_activated;
    double distance;
};

#endif