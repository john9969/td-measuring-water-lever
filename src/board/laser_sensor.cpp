#include "laser_sensor.h"
#define ENABLE_DEBUG 1
laser_sensor sensor;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

laser_sensor::laser_sensor() {
  this->distance = 0.0;
  this->has_response = false;
  this->timeout_read_sensor = 10;
  this->is_timeout_active = false;
  this->op_state = OP_STATE_INIT;
  memset(this->water_lever, 0, sizeof(this->water_lever));
}

void laser_sensor::init(){
    init_uart_port();
}

void laser_sensor::to_json(String& data){
  for(int i =0;i < MAX_NUMBER_VALUE_WATER_LEVER; i++){
    data += "\"water_lever_" + String(i)+"\":" + String (this->water_lever[i]) + ",";
  }
  //data += "\"signal_quarity\":"
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
          set_op_state(OP_STATE_FAIL);
          DBln("UART Open Fail");
    }
    DBln("UART OPEN SUCCESS");
}

/*****************PRIVATE************************/
void laser_sensor::uart_send_data(const byte data[])  {
  mySerial.write(data, UART_TX_BUFF_LENGTH);
}

void laser_sensor::set_distance( const double& distance){
  this->distance = distance;
}

double laser_sensor::get_distance() {
  return this->distance;
}

void laser_sensor::uart_read_data(char* buff, int& length){
  char* value;
  if(!mySerial.available()) return;
  length = mySerial.available();
  memset(buff,0,(size_t)UART_RX_BUFF_LENGTH);
  mySerial.readBytes(buff, size_t(UART_RX_BUFF_LENGTH));
  for(int i =0;i< length;i++){
    Serial.println(buff[i],HEX);
  }
  this->has_response = true;
}

bool laser_sensor::parse_data_receive(char* buff, int& length){
  if(!this->has_response) return false;
  this->has_response = false;
  bool ok = false;
  OP_STATE op_state = get_op_state(); 
  if(buff[0] == 0xAA) ok = true;
  //6 to 9 distance, and 10,11 signal qualitycation
  if(!ok){
    DBln("wrong form, data Frame: ");
    memset(buff, 0, UART_RX_BUFF_LENGTH);
    return false;
  }

  DB("receive data ok");
  if(op_state == OP_STATE_READ_DISTANCE){
    if(buff[3] != 0x22) {
      int index =0;
      for (size_t i = 1; i < length; i++) {
        if (buff[i] == 0xAA) {
            index = i;
            ok = true;
            break;
        }
        ok=false;
      }
      if(!ok){
          DBln("wrong form, data Frame: ");
          memset(buff, 0, UART_RX_BUFF_LENGTH);
          return false;
      }
      for (size_t i = 0; i < length - index; i++) {
        buff[i] = buff[i + index];
    }
    length -= index;
    }
    uint32_t distance = 0;
    
    for(int i = 6; i <=9;i++){
        distance = (distance<<8)|buff[i];
    }
    DB("distance_value: ");
    DBln(distance);
    set_distance(distance);
    if(distance > MAX_DISTANCE){
      DBln("wrong distance: "  + String(distance));
      return false;
    }
    bool has_new = false;
    for(int i =0;i< MAX_NUMBER_VALUE_WATER_LEVER;i++){
      if(this->water_lever[i] != 0) continue;
      has_new = true;
      this->water_lever[i] = distance;
      this->timeout_read_sensor = TIMEOUT_COMMAND_SENSOR;
      break;
    }
    if(!has_new) {
      DBln("Done get water lever:");
      for (int i = 0; i < MAX_NUMBER_VALUE_WATER_LEVER ; i++)
      {
        DB("number: " + String(i) + "~");
        DB("value: " + String(this->water_lever[i]) + ",");
      }
      DBln();
      set_op_state(OP_STATE_DONE);
      this->timeout_read_sensor = TIMEOUT_COMMAND_SENSOR;
    }
  }
  else if( get_op_state() == OP_STATE_ON){
    DBln("turn on ok");
    this->timeout_read_sensor = TIMEOUT_COMMAND_SENSOR;
    set_op_state(OP_STATE_DONE);
  }
  return true;
}


bool laser_sensor::is_uart_available() const{
  return Serial.available();
}
  
void laser_sensor::set_signal_quality(const double& signal_quality){
  this->signal_quality = signal_quality;
}

double laser_sensor::get_signal_quality() const{
  return this->signal_quality;
}
void laser_sensor::set_op_state(const OP_STATE& op_state){
  this->op_state = op_state;
}
laser_sensor::OP_STATE laser_sensor::get_op_state() const{
  return this->op_state;
}
uint16_t* laser_sensor::get_water_lever(){
  return this->water_lever;
}

/*********************************PUPLIC FUNCTION*****************************************************/

bool laser_sensor::on_sensor(){
  set_op_state(OP_STATE_ON);
  DBln("sensor on");
  return true;
}
bool laser_sensor::off_sensor(){
  set_op_state(OP_STATE_OFF);
  return true;
}
void laser_sensor::read_water_lever(){
  set_op_state(OP_STATE_READ_DISTANCE);
}
void board_process(){
    sensor.process();
}
void laser_sensor::process(){
  if(this->timeout_read_sensor <=0){
    set_op_state(OP_STATE_ABORT);
  }
  OP_STATE op_state = get_op_state();
  if(op_state == OP_STATE_DONE) return;
  static char buff[UART_RX_BUFF_LENGTH];
  static int length;
  uart_read_data(buff, length);
  parse_data_receive(buff,length);

  if(get_op_state() == OP_STATE_READ_DISTANCE){
    DBln("send_read_waterlever");
    uart_send_data(this->command_led.get_distance);
    this->timeout_read_sensor--;
  }
  else if (get_op_state() == OP_STATE_ON)
  {
    DBln("ON_LED");
    uart_send_data(this->command_led.on_led);
    this->timeout_read_sensor --;
  }
}
/******************************************************************************************************/
