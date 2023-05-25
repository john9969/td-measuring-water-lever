#ifndef APP_SEND_DATA_H
#define APP_SEND_DATA_H
#include "config.h"
#include "board/blink_led.h"
#include "board/laser_sensor.h"
#include "board/connect_internet.h"
#include "board/read_adc.h"
#include "service/rtc.h"
class App_Send_Data {

public:
  enum DATA_TYPE{
    DATA_TYPE_LOG,
    DATA_TYPE_MEASURING,
  };

  enum APP_OP{
    APP_OP_CHECK_VOL,
    APP_OP_ON_SENSOR,
    APP_OP_CONNECT_WIFI,
    APP_OP_GET_WATER_LEVER,
    APP_OP_SEND,
    APP_OP_DONE,
    APP_OP_FAIL
  };

  App_Send_Data();
  void process();
  APP_OP get_app_op() const;
  void  set_app_op(const APP_OP& app_op);
private:
  void to_json(String& data);
  APP_OP app_op;
};
extern App_Send_Data app_send_data;
extern void app_process();
#endif