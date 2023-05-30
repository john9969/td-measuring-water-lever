#include "rtc.h"
Date_Time date_time;
Date_Time::Date_Time(){
    rtc = new Rtc{2023,0,0,0,0,0,0};
}
uint64_t Date_Time::get_time_remain(uint8_t min_wake_up){
    uint64_t us_wakeup = 0;
    update_local_time();
    return us_wakeup;
}
uint64_t Date_Time::estimate_time(){
    if(this->rtc->min > 55 || this->rtc->min < 5) {
        return (3600e6);
    }
    return (60 - this->rtc->min) * (60e6);
    //return 60e6;
}
String Date_Time::now(const DATE_TIME_TYPE& date_time_type){
    update_local_time();
    String date_time = "";
    switch (date_time_type)
    {
    case DATE_TIME_TYPE_DDMMYY:
    case DATE_TIME_TYPE_ddMMYY:
    case DATE_TIME_TYPE_ddmmYY:
    case DATE_TIME_TYPE_ddmmyy:
        date_time   +=  String(rtc->hour);
        date_time   +=  ":";
        date_time   +=  String(this->rtc->min);
        date_time   +=  ":";
        date_time   +=  String(this->rtc->sec);
        date_time   +=  " ";
        date_time   +=  String(this->rtc->day);
        date_time   +=  "/";
        date_time   +=  String(this->rtc->month);
        date_time   +=  "/";
        date_time   +=  String(this->rtc->year);
        /* code */  
        break;
    
    default:
        break;
    }
    return date_time;
}

void Date_Time::to_json(String& data){
    data += "\"date_time\":\"" + now(DATE_TIME_TYPE_DDMMYY) + "\",";
}

void Date_Time::update_local_time(){
    uint64_t total_sec = millis() - this->rtc->time_index;
    uint64_t min_total = total_sec/60000;
    if((min_total + this->rtc->min) >= 60){
        this->rtc->hour ++;
        this->rtc->min = min_total+this->rtc->min - 60;
    }
    else{
        this->rtc->min = min_total+this->rtc->min;  
    }
}
void Date_Time::from_string(String date_time){

    this->rtc->hour     = date_time.substring(0,2).toInt();
    this->rtc->min      = date_time.substring(3,5).toInt();
    this->rtc->sec      = date_time.substring(6,8).toInt();
    this->rtc->day      = date_time.substring(9,11).toInt();
    this->rtc->month    = date_time.substring(12,14).toInt();
    this->rtc->year     = date_time.substring(15,19).toInt();
    if(this->rtc->min >=    60) this->rtc->min  = 59;
    if(this->rtc->hour >=   24) this->rtc->hour = 23;
    if(this->rtc->min <     0)  this->rtc->min  = 0;
    if(this->rtc->hour <    0)  this->rtc->hour = 0;
}