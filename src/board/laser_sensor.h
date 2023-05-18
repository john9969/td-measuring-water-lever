#include <Arduino.h>
#include <SoftwareSerial.h>
#define UART_RX_BUFF_LENGTH 30UL
#define UART_TX_BUFF_LENGTH 9UL
#define rxPin 12
#define txPin 14
#ifndef LASER_SENSOR_H
#define LASER_SENSOR_H

typedef enum {
    SA_INACTIVE         =0,
    SA_UART_INACTIVE    =1,
    SA_RUN              =2
} SITUATION_ACTIVE;

class laser_sensor {
    
public:

typedef enum{
    STT_CMD_WAIT_RES,
    STT_CMD_ABOAD,
    STT_CMD_SUCCESS,
    STT_CMD_RES
}STT_CMD;

typedef enum{
    SENSOR_STATE_RES,
    SENSOR_STATE_ON,
    SENSOR_STATE_OFF,
    SENSOR_STATE_GET_DISTANCE
}SENSOR_STATE;

    void init();
    laser_sensor();
    void process();
    void activate();
    bool on_sensor();
    bool off_sensor();
    double read_distance(const int& timeout);
    
public:
    void set_distance( const double& distance);
    double get_distance() const;

    void set_is_activated(const bool& is_activated);
    bool get_is_activated() const;

    void set_sensor_state(const SENSOR_STATE& sensor_state);
    SENSOR_STATE get_sensor_state() const;

    SITUATION_ACTIVE get_situation_active() const;
    void set_situation_active(const SITUATION_ACTIVE& situation_active);
    void to_string(String& data);
private:
    void init_uart_port();
    void uart_send_data(const byte data[]);
    void uart_read_data(char* buff, int& length);
    void parse_data_receive(char* buff, const int& length);
    bool is_uart_available() const;
private:
typedef struct {
    byte on_led[9]                 =   {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x01,   0xC1};
    const byte off_led[9]          =   {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x00,   0xC0};
    const byte get_distance[9]     =   {0xAA,  0x00, 0x00, 0x20,   0x00,   0x01,   0x00,   0x00,   0x21};
} COMMAND_LED; 
    STT_CMD stt_cmd;
    COMMAND_LED command_led;
    
    SITUATION_ACTIVE situation_active;
    bool is_activated;
    bool has_response;
    double distance;
    SENSOR_STATE sensor_state;
};
extern SoftwareSerial mySerial;
extern void check_uart_available();
extern laser_sensor sensor; 
#endif