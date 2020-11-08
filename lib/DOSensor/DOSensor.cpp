#include "Arduino.h"
#include "DOSensor.h"

DOSensor::DOSensor(int DOAnalogpin)
{
    _DOAnalogpin = DOAnalogpin;
}

void DOSensor::getAnalogDO()
{
  double ADC_Raw=analogRead(_DOAnalogpin);
  double ADC_Voltage = (double)VREF * ADC_Raw / ADC_RES;
  #if TWO_POINT_CALIBRATION == 0
   uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature - (uint32_t)CAL1_T * 35;
   DO = (ADC_Voltage * DO_Table[int(temperature)] / V_saturation);
  #else
    uint16_t V_saturation = (int16_t)((int8_t)temperature - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
    DO = (voltage_mv * DO_Table[int(temperature)] / V_saturation);
  #endif
}
