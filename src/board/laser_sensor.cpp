#include "laser_sensor.h"
#include "config.h"
laser_sensor sensor;
laser_sensor::laser_sensor() {
  is_activated = false;
  distance = 0.0;
}
void laser_sensor::init(){
    init_uart_port();
    
}

void laser_sensor::to_string(String& data){
  data+= "@laser_sensor:";
  data+= "Situation_Active:";
  data += String(get_situation_active());
  data+= ",";
  data += "";
}

void laser_sensor::init_uart_port(){
    mySerial.begin(LASER_BAURATE);
    int timeout = 30000;
    while (!mySerial && timeout > 0)
    {
      timeout--;
      if(timeout<= 0 ) 
          set_situation_active(SA_UART_INACTIVE);
      /* code */
    }
}
void laser_sensor::activate() {
  is_activated = true;
}
double laser_sensor::read_distance(const int& timeout) {

    (void ) timeout;
  if (get_situation_active()  ==  SA_INACTIVE)        return -1;
  if (get_situation_active()  ==  SA_UART_INACTIVE)   return -2; 
  /*get distance*/

  distance = 10.0;
  return distance;
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
/*****************PRIVATE************************/
void laser_sensor::uart_send_data(uint8_t data[]){
  //this->mySerial.write();
  uint8_t* buffer = data;
  size_t size_buf = sizeof(data);
  Serial.write(buffer, size_buf);
}
void laser_sensor::set_situation_state(const COMMUNICATION_STATE& communication_state){
  this->communication_state = communication_state;
}
COMMUNICATION_STATE laser_sensor::get_communication_state() const{
  return this->communication_state;
}
void laser_sensor::uart_read_data(uint8_t* buff, uint32_t& length){
  //uint8_t p_data[UART_RX_BUFF_LENGTH] = {};
  
  memset(buff,0,(size_t)UART_RX_BUFF_LENGTH);
  mySerial.read(buff, size_t(UART_RX_BUFF_LENGTH));
  
  

  //p_data.trim();
  //return p_data;
}
bool laser_sensor::is_uart_available() const{
  return Serial.available();
}
void laser_sensor::set_situation_active(const SITUATION_ACTIVE& situation_active){
  this->situation_active = situation_active;
}
SITUATION_ACTIVE laser_sensor::get_situation_active() const {
  return this->situation_active;
}