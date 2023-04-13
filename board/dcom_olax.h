#include "Arduino.h"
#include "config_board.h"
#ifndef HTTP_REQUEST
#define HTTP_REQUEST

/*DEFINE HERE*/

#define DCOM_ON     digitakWrite(OLAX_PIN, HIGH);
#define DCOM_OFF    digitalWrite(OLAX_PIN,LOW);
//************************************************************************************
static void init_dcom(){
    pinMode(OLAX_PIN,OUTPUT);
}

#endif