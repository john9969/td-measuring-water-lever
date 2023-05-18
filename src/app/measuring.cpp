#include "measuring.h"
Measuring measuring;
Measuring::Measuring(){
    wl_local = 0.00;
    wl_remote = 0.00;
}
void Measuring::init(){
}
bool Measuring::start_measuring(){
    
    return true;
}
double Measuring::get_wl(){
    return 0.0;
}
/*TYPE JSON:
"time_stamp":"10:59:59 30/12/2023",
"type"      :"water_lever/log",
"water_lever":num,
"vol"       :10000,
*/
String Measuring::to_json() {
  String data ="";
  data  +=  "\"type_data\": \"water_lever\",";
  data  +=  "\"water_lever\":" + String(this->wl_local) + ",";
  return data;
}

double Measuring::verify_value(){
    return 0.0;   
}