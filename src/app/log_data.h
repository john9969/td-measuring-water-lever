
#ifndef LOG_DATA_H
#define LOG_DATA_H
#include "Arduino.h"
const int MAX_LOG_NUM = 10;

class LogData {
  private:
    String log[MAX_LOG_NUM];
  public:
    void add_log(String str);
    String to_string();
};
extern LogData log_data;
#endif