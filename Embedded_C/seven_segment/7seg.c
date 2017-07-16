//---simple seven segment without look up table---//

#include<REG51F.h>

unsigned char ds1,ds2,ds3,ds4;
sbit sl1 = P2^0;
sbit sl2 = P2^1;
sbit sl3 = P2^2;
sbit sl4 = P2^3;

void delay(unsigned int time);
//---------------------------------//
void main()
{

   while(1)
   {
    //-----------------------------//

    sl1=0;		 // for display1
    sl2=1;		 //
    sl3=1;		 //
    sl4=1;		 //

    ds1=0xFC;
    P0=ds1;
    delay(1);
    //-----------------------------//

    sl1=1;		 //
    sl2=0;		 // for display2
    sl3=1;		 //
    sl4=1;		 //

    ds2=0x60;
    P0=ds2;
    delay(1);
    //-----------------------------//

    sl1=1;		 //
    sl2=1;		 //
    sl3=0;		 //	for display3
    sl4=1;		 //

    ds3=0xDA;
    P0=ds3;
    delay(1);
    //-----------------------------//

    sl1=1;		  //
    sl2=1;		  //
    sl3=1;		  //
    sl4=0;		  // for display4

    ds4=0xF2;
    P0=ds4;
    delay(1);
    //-----------------------------//

  }
}
//---------------------------------------//
void delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    for(j=0;j<120;j++);
}
//---------------------------------------//

