#include "laser_sensor.h"
#include "config_board.h"
laser_sensor::laser_sensor() {
  is_activated = false;
  distance = 0.0;
}
void laser_sensor::init(){
    Serial.begin(LASER_BAURATE);
    
}
void laser_sensor::activate() {
  is_activated = true;
}
double laser_sensor::read_distance(const int& timeout) {

    (void ) timeout;
  if (is_activated) {
    // Do some calculations to get the distance
    distance = 10.0;
    return distance;
  } else {
    return 0.0;
  }
}
void laser_sensor::set_distance( const double& distance){
    this->distance = distance;
}
double laser_sensor::get_distance() const{
    return this->distance;
}
void laser_sensor::set_is_activated(const bool& is_activated){
    this->is_activated = is_activated;
}
bool laser_sensor::get_is_activated() const{
    return this->is_activated;
}