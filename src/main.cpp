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
    if(Serial.available()){
        String data = Serial.readString();
        if(data == "reset"){
            Serial.println("reset ok");
            ESP.restart();
        }
        if(data == "on"){
            sensor.on_sensor();
            Serial.println("on ok");
        }
        if(data == "off"){
            sensor.off_sensor();
            Serial.println("off ok");
        }
        if(data == "ds"){
            sensor.read_distance(10);
            Serial.println("ds ok ");
        }
    }
}