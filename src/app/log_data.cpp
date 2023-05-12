#include "log_data.h"
LogData log_data;
void LogData::add_log(String str) {
  for (int i = MAX_LOG_NUM - 1; i > 0; i--) {
    log[i] = log[i - 1];
  }
  log[0] = str;
}

String LogData::to_string() {
  String result = "";
  for (int i = 0; i < MAX_LOG_NUM; i++) {
    result += log[i] + "\n";
  }
  return result;
}