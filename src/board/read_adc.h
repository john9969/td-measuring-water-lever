#ifndef READ_ADC
#define READ_ADC
#include <Arduino.h>
#define MULTIPILER 37     //unit minivol
#define ADC_PIN_OUT A0
// typedef struct read_adc
// {
//     /* data */
//     int (*read_adc)(); 
// }read_adc;
// extern read_adc vol_in;
static inline unsigned long get_vol_input(){
    int p_adc_data = analogRead(ADC_PIN_OUT);
    unsigned long voltage = (unsigned long)(p_adc_data * MULTIPILER);
    return voltage;
}

//  vol_in{
//     .read_adc = p_read_adc,
// };
#endif // !READ_ADC
