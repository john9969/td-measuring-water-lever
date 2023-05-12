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
void Measuring::to_json(String& data){
    data = "{"
            "\"water_lever\":" + String(get_wl());
            
    "}";
    
}
double Measuring::verify_value(){
    return 0.0;   
}