#include <Arduino.h>
#ifndef RTC_H
#define RTC_H

/*DEFINE HERE*/

//************************************************************************************
struct Rtc
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t milisec;
    uint32_t time_index;
    /* data */
};

class Date_Time {
    
private:
    Rtc* rtc;
    void parse();
    void update_local_time();
public:
typedef enum DATE_TIME_TYPE{
    DATE_TIME_TYPE_DDMMYY,
    DATE_TIME_TYPE_ddMMYY,
    DATE_TIME_TYPE_ddmmYY,
    DATE_TIME_TYPE_ddmmyy
} DATE_TIME_TYPE;
    Date_Time();
    String now(const DATE_TIME_TYPE& date_time_type);
    void to_json(String & data);
    uint64_t estimate_time();
    void from_string(String date_time);
    uint64_t get_time_remain(uint8_t min_wake_up);
};
extern Date_Time date_time;
#endif