#include "send_data.h"

app_send_data::app_send_data() {
  // Constructor
}

void app_send_data::loop() {
  
}

bool app_send_data::send_data(String data, const DATA_TYPE& type) {
  return true;
}
/*TYPE JSON:
"time_stamp":"10:59:59 30/12/2023",
"type"      :"water_lever/log",
"water_lever":num,
"vol"       :10000,
*/
String app_send_data::to_json(){
  String data ="{";
  data  +=  "\"serial_number\":"  SERIAL_NUMBER;
  data  +=  "\"type_data\":   
  }
bool app_send_data::check_response() {
  // Check if client is connected
  
  return false;
}