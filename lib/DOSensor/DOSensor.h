#ifndef DOSensor_h
#define DOSensor_h

#include "Arduino.h"

#define ArrayLenthDO 30
#define VOLTAGE 5.00    //system voltage
#define OFFSET 0
#define DO_PIN A1
#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution
#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function
//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃
const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};
//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

class DOSensor
{
    private:
        int _DOAnalogpin;

    public:
        DOSensor(int DOAnalogpin);
        void getAnalogDO();
        double DO;
        double temperature=25.0;       
};

#endif
