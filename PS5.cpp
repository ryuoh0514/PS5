#include "mbed.h"
#include "PS5.h"

PS5::PS5(PinName rx, int rate): UnbufferedSerial(NC, rx, rate)
{
    ORIGIN[0]=0;
    ORIGIN[1]=0;
    ORIGIN[2]=128;
    ORIGIN[3]=128;
    ORIGIN[4]=128;
    ORIGIN[5]=128;
    ORIGIN[6]=0;
    ORIGIN[7]=0;
}

int PS5::get_data(bool* p)
{
    if(readable()){
        for(int i=0;i<28;i++){
            read(&input[i],1);
        }
    
        for(int k=12;k<26;k++){      
            if(input[k]>='0'&&input[k]<='9')input[k]-='0';
            else if(input[k]>='A'&&input[k]<='F') input[k]=input[k]-'A'+10;    
        }
        for(int j=0;j<6;j++){
            data[j]=input[j*2+12]*16+input[j*2+13];
        }
        data[6]=input[24];
        data[7]=input[25];
        
        p[RIGHT]=data[0]==0b0001?true:false;
        p[DOWN]=data[0]==0b0010?true:false;
        p[UP]=data[0]==0b0011?true:false;
        p[LEFT]=data[0]==0b0100?true:false;
        p[UPRIGHT]=data[0]==0b0101?true:false;
        p[DOWNRIGHT]=data[0]==0b0110?true:false;
        p[UPLEFT]=data[0]==0b0111?true:false;
        p[DOWNLEFT]=data[0]&0b1000?true:false;
        p[SQUARE]=data[0]&0b00010000?true:false;
        p[CROSS]=data[0]&0b00100000?true:false;
        p[CIRCLE]=data[0]&0b01000000?true:false;
        p[TRIANGLE]=data[0]&0b10000000?true:false;
        p[L1]=data[1]&0b0001?true:false;
        p[R1]=data[1]&0b0010?true:false;
        p[SHARE]=data[1]&0b0100?true:false;
        p[OPTIONS]=data[1]&0b1000?true:false;
        p[L3]=data[1]&0b00010000?true:false;
        p[R3]=data[1]&0b00100000?true:false;
        p[PSBUTTON]=data[1]&0b01000000?true:false;
        p[TOUCHPAD]=data[1]&0b10000000?true:false;
        p[L2]=data[6]?true:false;
        p[R2]=data[7]?true:false;

    }
    j=0;
    for(int i=0;i<8;i++){
        if(data[i]==ORIGIN[i])j++;
    }
    if(j==8)return 0;
    else return 1;
}

void PS5::get_analog(int* ps5_analog){
    ps5_analog[L2VALUE]=data[6];
    ps5_analog[R2VALUE]=data[7];
    ps5_analog[LSTICKX]=data[2]-128;
    ps5_analog[LSTICKY]=data[3]-128;
    ps5_analog[RSTICKX]=data[4]-128;
    ps5_analog[RSTICKY]=data[5]-128;
}
