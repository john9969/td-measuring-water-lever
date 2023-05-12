#ifndef APP_SEND_DATA_H
#define APP_SEND_DATA_H
#include "lib/tiny-json.h"
#include "config.h"
#include "board/connect_internet.h"
#include "service/rtc.h"
class app_send_data {

public:
  typedef enum DATA_TYPE{
    DATA_TYPE_LOG,
    DATA_TYPE_MEASURING,
  } DATA_TYPE;
    app_send_data();
    void loop();
    bool send_data(String data, const DATA_TYPE& type);
    bool check_response();
private:
    String to_json();
};

#endif