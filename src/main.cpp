#include <Arduino.h>

#include "service/init.h"
#include "board/init.h"
#include "app/init.h"

void setup() {
    Serial.begin(115200);
    board_int();
    service_inti();
    app_inti();
}

void loop() {
    multi_task.run();
}