#ifndef _PS5_H_
#define _PS5_H_

#include "mbed.h"

class PS5 : public UnbufferedSerial
{
public:
    enum{
        RIGHT,
        DOWN,
        UP,
        LEFT,
        UPRIGHT,
        DOWNRIGHT,
        UPLEFT,
        DOWNLEFT,
        SQUARE,
        CROSS,
        CIRCLE,
        TRIANGLE,
        L1,
        R1,
        SHARE,
        OPTIONS,
        L3,
        R3,
        PSBUTTON,
        TOUCHPAD,
        L2,
        R2,
        ALL_BUTTON
    };
    enum{
        L2VALUE,
        R2VALUE,
        LSTICKX,
        LSTICKY,
        RSTICKX,
        RSTICKY,
        ALL_ANALOG
    };

    PS5(PinName rx,PinName busy,int rate=19200);

    int get_data(bool* p);
    void get_analog(int* analog);
    
private:

    DigitalOut _busy;

    int input[28];
    int data[8];
    int sig;

};

#endif
