#include "laser_sensor.h"
#include "config.h"
laser_sensor sensor;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
void check_uart_available();
laser_sensor::laser_sensor() {
  is_activated = false;
  distance = 0.0;
  this->stt_cmd = STT_CMD_RES;
  this->has_response = false;
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
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    mySerial.begin(LASER_BAURATE);
    int timeout = 30000;
    while (!mySerial && timeout > 0)
    {
      timeout--;
      if(timeout<= 0 ) 
          set_situation_active(SA_UART_INACTIVE);
          DBln("UART Open Fail");
    }
    DBln("UART OPEN SUCCESS");
}
void laser_sensor::activate() {
  is_activated = true;
}
double laser_sensor::read_distance(const int& timeout) {

    (void ) timeout;
    uart_send_data(this->command_led.get_distance);
    set_sensor_state(SENSOR_STATE_GET_DISTANCE);
  // if (get_situation_active()  ==  SA_INACTIVE)        return -1;
  // if (get_situation_active()  ==  SA_UART_INACTIVE)   return -2; 
  // /*get distance*/

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
void laser_sensor::uart_send_data(const byte data[]){
  //this->mySerial.write();/
  //Serial.println(sizeof(data));
  mySerial.write(data, UART_TX_BUFF_LENGTH);
}
void laser_sensor::set_sensor_state(const SENSOR_STATE& sensor_state){
  this->sensor_state = sensor_state;
}
laser_sensor::SENSOR_STATE laser_sensor::get_sensor_state() const{
  return this->sensor_state;
}
/*********************************PUPLIC FUNCTION*****************************************************/

bool laser_sensor::on_sensor(){
  uart_send_data(this->command_led.on_led);
  set_sensor_state(SENSOR_STATE_ON);
  DBln("sensor on");
  return true;
}
bool laser_sensor::off_sensor(){
  uart_send_data(this->command_led.off_led);
  set_sensor_state(SENSOR_STATE_OFF);
  return true;
}
void check_uart_available(){
    sensor.process();
}

/******************************************************************************************************/
void laser_sensor::uart_read_data(char* buff, int& length){
  if(!mySerial.available()) return;
  length = mySerial.available();
  memset(buff,0,(size_t)UART_RX_BUFF_LENGTH);
  mySerial.readBytes(buff, size_t(UART_RX_BUFF_LENGTH));
  this->has_response = true;
}
void laser_sensor::parse_data_receive(char* buff, const int& length){
  if(!this->has_response) return;
  bool ok = false;
  SENSOR_STATE sensor_state = get_sensor_state();
  char compare[UART_TX_BUFF_LENGTH] = {};
  memset(compare,0,UART_TX_BUFF_LENGTH);
  switch (sensor_state)
  {
  case SENSOR_STATE_OFF:
    memcpy(compare,command_led.off_led,sizeof(command_led.off_led));
    break;
  case SENSOR_STATE_ON:
    memcpy(compare,command_led.on_led,sizeof(command_led.on_led));
    break;
  case SENSOR_STATE_GET_DISTANCE:
    memcpy(compare,command_led.get_distance,sizeof(command_led.get_distance));
    break;
  case SENSOR_STATE_RES:
    DBln("Wrong state");
    break;
  }
  if(buff[0] == 0xAA) ok = true;

  //6 to 9 distance, and 10,11 signal qualitycation
  if(ok){
    DB("receive data ok");
    if(sensor_state == SENSOR_STATE_GET_DISTANCE){
      uint32_t distance = 0;
      for(int i = 6; i <=9;i++){
          distance = (distance<<8)|buff[i];
      }
      
      DB("distance_value: ");
      DBln(distance);
      set_distance(distance);
    }
    int k =0;
    while (k< length)
    {
      Serial.print(k);
      Serial.print(":");
      Serial.print(buff[k],HEX);
      Serial.print(" ");
      k++;
      /* code */
    }
    Serial.println();
    
    //Serial.write(buff);
    
  } 
  else {
    DBln("verify response command fail");
    int k =0;
    while (k< length)
    {
      Serial.print(k);
      Serial.print(":");
      Serial.print(buff[k],HEX);
      Serial.print(" ");
      k++;
      /* code */
    }
    Serial.println();
    memset(buff, 0, UART_RX_BUFF_LENGTH);
  }
  this->has_response = false;
  set_sensor_state(SENSOR_STATE_RES);
}

void laser_sensor::process(){
  static char buff[UART_RX_BUFF_LENGTH];
  static int length;
  uart_read_data(buff, length);
  parse_data_receive(buff,length);
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