#include<pic.h>


unsigned char temp,temp1;

void delay(unsigned int);

void init_main();
void init_timer1();

//====================================================

void main()
{
   unsigned int i;
   TRISB=0X00;
   PORTB=0X00;
   for(i=0;i<100;i++)  
      init_timer1();
  while(1)
  {  

	 do
     {
      temp=PIR1;
      temp=temp&0x01;
     }while(temp==0x00);
         
     
            temp1=temp1^0xFF;
            PORTB=~temp1;
            
            PIR1=0X00;
  }        
}
//====================================================


void init_timer1()
{
  T1CON=0X04; //configure timer1 as timer
  TMR1H=0X00;
  TMR1L=0X00;
  temp =temp |0x01;
  T1CON=temp;
}
//-----------------------------------------------------
 void delay(unsigned int k)
  {
    unsigned int i,j;
    for(i=0;i<k;i++)
    for(j=0;j<120;j++);
  }
//-----------------------------------------------------