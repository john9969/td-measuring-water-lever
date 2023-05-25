#include "app_send_data.h"
App_Send_Data app_send_data;
void app_process(){
  app_send_data.process();

}


App_Send_Data::App_Send_Data() {

  this->app_op =APP_OP_CHECK_VOL;
}

void App_Send_Data::process() {
  String data_send = "";
  switch (get_app_op()) {
  case APP_OP_CHECK_VOL:
    if(get_vol_input() <= MIN_VOL_RUNNING){
      break;
    }
    set_app_op(APP_OP_ON_SENSOR);
    DBln("done check vol");
    break;
  case APP_OP_ON_SENSOR:
    if(sensor.get_op_state() == laser_sensor::OP_STATE_ABORT){
      set_app_op(APP_OP_FAIL);
      sensor.set_op_state(laser_sensor::OP_STATE_INIT);
      break;
    }
    if(sensor.get_op_state() == laser_sensor::OP_STATE_DONE){
      sensor.set_op_state(laser_sensor::OP_STATE_INIT);
      set_app_op(APP_OP_CONNECT_WIFI);
      DBln("done check sensor");
      break;
    }
    if(sensor.get_op_state() == laser_sensor::OP_STATE_INIT){
      sensor.on_sensor();
      DBln("ON sensor");
    }
    break;
  case APP_OP_CONNECT_WIFI:
    if(connection.get_internet_status() == ConnectInternet::INTERNET_CONNECTED){
      set_app_op(APP_OP_GET_WATER_LEVER);
      DBln("wifi connect ok");
      break;
    }
    if(connection.get_internet_status() == ConnectInternet::INTERNET_DISCONNECTED){
      set_app_op(APP_OP_FAIL);
      DBln("wifi connect fail");
    }
    break;
  case APP_OP_GET_WATER_LEVER:
     if(sensor.get_op_state() == laser_sensor::OP_STATE_ABORT){
      set_app_op(APP_OP_FAIL);
      sensor.set_op_state(laser_sensor::OP_STATE_INIT);
      DBln("measuring fail");
      break;
    }
    if(sensor.get_op_state() == laser_sensor::OP_STATE_DONE){
      sensor.set_op_state(laser_sensor::OP_STATE_INIT);
      set_app_op(APP_OP_SEND);
      DBln("measuring ok ");
      break;
    }
    if(sensor.get_op_state() != laser_sensor::OP_STATE_READ_DISTANCE){
      sensor.read_water_lever();
    }
    break;
  case APP_OP_SEND:
    DB("Send data: ");
    sensor.to_json(data_send);
    to_json(data_send);
    DBln(data_send);
    set_app_op(APP_OP_DONE);
    break;
  case APP_OP_DONE:
    DBln("done");

    break;
  case APP_OP_FAIL:
    break;
  }
  
}


/*TYPE JSON:
"time_stamp":"10:59:59 30/12/2023",
"type"      :"water_lever/log",
"water_value":num,
"vol"       :10000,
*/
void App_Send_Data::to_json(String& data){
  
  data  +=  "\"serial_number\":"  SERIAL_NUMBER ",";
  data  +=  "\"type\":\"water_lever\",";
  //data  +=  "\"water_value\":" + String(get_water)
   data  += "\"vol\":" + String(get_vol_input()) + ",";
}


App_Send_Data::APP_OP App_Send_Data::get_app_op() const{
  return this->app_op;
}
void  App_Send_Data::set_app_op(const APP_OP& app_op){
  this->app_op = app_op;
}