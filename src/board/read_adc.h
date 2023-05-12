#ifndef READ_ADC
#define READ_ADC
#include <Arduino.h>
#define MULTIPILER 0.01     //unit minivol
#define ADC_PIN_OUT A0
typedef struct read_adc
{
    /* data */
    int (*read_adc)(); 
}read_adc;

static inline int p_read_adc(){
    int p_adc_data = analogRead(ADC_PIN_OUT);
    int voltage = p_adc_data * MULTIPILER;
    return voltage;
}

// extern read_adc adc{
//     .read_adc = p_read_adc,
// };
#endif // !READ_ADC
