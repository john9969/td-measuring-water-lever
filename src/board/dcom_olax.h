#include <Arduino.h>
#include "config.h"

#define DCOM_ON     digitalWrite(OLAX_PIN, HIGH);
#define DCOM_OFF    digitalWrite(OLAX_PIN,LOW);
#define DCOM_INIT   pinMode(OLAX_PIN,OUTPUT);
