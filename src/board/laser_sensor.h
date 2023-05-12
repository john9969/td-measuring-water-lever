#include <Arduino.h>
#include <SoftwareSerial.h>
#define UART_RX_BUFF_LENGTH 30UL
#define rxPin 12
#define txPin 14
#ifndef LASER_SENSOR_H
#define LASER_SENSOR_H

typedef enum {
    SA_INACTIVE         =0,
    SA_UART_INACTIVE    =1,
    SA_RUN              =2
} SITUATION_ACTIVE;
typedef enum{
    WAIT_FOR_RESPONSE,
    WRITE_OPEN_SENSOR,
    WRITE_CLOSE_SENSOR,
    WRITE_GET_DISTANCE
}COMMUNICATION_STATE;
typedef struct {
    const byte on_led[9] =       {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x01,   0xC1};
    const byte off_led[9] =      {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x00,   0xC0};
    const byte get_distance[9] = {0xAA,  0x00, 0x00, 0x20,   0x00,   0x01,   0x00,   0x00,   0x21};
} COMMAND_LED;
class laser_sensor {
    
public:
    void init();
    laser_sensor();
    void activate();
    double read_distance(const int& timeout);

public:
    void set_distance( const double& distance);
    double get_distance() const;
    void set_is_activated(const bool& is_activated);
    bool get_is_activated() const;
    void set_situation_state(const COMMUNICATION_STATE& communication_state);
    COMMUNICATION_STATE get_communication_state() const;
    SITUATION_ACTIVE get_situation_active() const;
    void set_situation_active(const SITUATION_ACTIVE& situation_active);
    void to_string(String& data);
private:
    void init_uart_port();
    void uart_send_data(uint8_t data[]);
    void uart_read_data(uint8_t* buff,uint32_t& length);
    bool is_uart_available() const;
private:
    SoftwareSerial mySerial;
    SITUATION_ACTIVE situation_active;
    bool is_activated;
    double distance;
    COMMUNICATION_STATE communication_state;
};
extern laser_sensor sensor; 
#endif