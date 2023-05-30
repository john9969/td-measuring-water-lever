#include <Arduino.h>
#include <SoftwareSerial.h>
#include "config.h"


#ifndef LASER_SENSOR_H
#define LASER_SENSOR_H
#define UART_RX_BUFF_LENGTH 30UL
#define UART_TX_BUFF_LENGTH 9UL
#define TIMEOUT_COMMAND_SENSOR  5
#define rxPin 12
#define txPin 14
#define MAX_DISTANCE            60000UL
class laser_sensor {
    
public:
typedef enum {
    OP_STATE_ON,
    OP_STATE_OFF,
    OP_STATE_READ_DISTANCE,
    OP_STATE_ABORT,
    OP_STATE_DONE,
    OP_STATE_INIT,
    OP_STATE_FAIL
} OP_STATE;
    void init();
    laser_sensor();
    void process();
    bool on_sensor();
    bool off_sensor();
    void read_water_lever();
    
    void to_json(String& data);
    void set_op_state(const OP_STATE& op_state);
    OP_STATE get_op_state() const;
    
private:
    void init_uart_port();
    void uart_send_data(const byte data[]);
    void uart_read_data(char* buff, int& length);
    bool parse_data_receive(char* buff, int& length);
    bool is_uart_available() const;
    void set_distance( const double& distance);
    double get_distance();
    uint16_t* get_water_lever();
    void set_signal_quality(const double& signal_quality);
    double get_signal_quality() const;
private:
typedef struct {
    byte on_led[9]                 =   {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x01,   0xC1};
    const byte off_led[9]          =   {0xAA,  0x00, 0x01, 0xBE,   0x00,   0x01,   0x00,   0x00,   0xC0};
    const byte get_distance[9]     =   {0xAA,  0x00, 0x00, 0x20,   0x00,   0x01,   0x00,   0x00,   0x21};
} COMMAND_LED; 
    COMMAND_LED command_led;
    int timeout_read_sensor;
    bool is_timeout_active;
    bool has_response;
    double distance;
    double signal_quality;
    uint16_t water_lever[MAX_NUMBER_VALUE_WATER_LEVER];
    OP_STATE op_state;

};
extern SoftwareSerial mySerial;
extern void board_process();
extern laser_sensor sensor; 
#endif