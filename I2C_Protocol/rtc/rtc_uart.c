#include <REG51F.H>
#include<intrins.h>
  
sbit scl=P1^6;
sbit sda=P1^7;

bit flag;

unsigned char sec,min,hrs;

unsigned char i2c_read(void);


 void i2c_write(unsigned char a);
 void rtc_read(void);
 void display(void);


void ack_w(void);
void nack_w(void);
void ack_r(void);
void start(void);
void stop(void);

void rtc_write(unsigned char h,unsigned char m,unsigned char s);

  void init_timer(void);
 void init_uart(void);
 void tx(unsigned char a);
 unsigned char rx(void);

void main(void)
{

 init_uart();

 rtc_write(0x11,0x35,0x43);                                                                                                        
  while(1) 
  {
  	rtc_read();
  	display();
	 tx(0x0d);              //CARRIAGE RETURN
  }
}

/**********************i2c function start**********************************/
unsigned char i2c_read(void)
 { 
 unsigned char i,store = 0;

  sda=1;	 //sda in input direction

  for(i=0;i<8;i++)
  {
   scl=1;
   	_nop_();
	_nop_();
	store = store << 1; 
	if(sda)
	{
    store=store|0x01;
	}
	
    scl=0;
    _nop_();
	_nop_();

   }
	  return(store);
 }


 void i2c_write(unsigned char a)
{
unsigned char b,i;
		
	 scl=0;
	 for(i=0;i<8;i++)
	 {
		b=a;
	   	b=b&0x80;

		if(b==0x80)
		{
		 sda=1;
		}
		else if(b==0x00)
		{
		  sda=0;
		}
		  a=a<<1;
		 _nop_();
		 scl=1;
		 _nop_();
		 _nop_();
		 scl=0;
	 }
	 
	 ack_r();	

}


void ack_w(void)
{
sda=0;		 //sda low give ack
scl=1;
_nop_();
_nop_();
scl=0;

}

void nack_w(void)
{
sda=1;				//sda high give nack

scl=1;
_nop_();
_nop_();
scl=0;

}

void ack_r(void)
{

sda=1;    //make the sda pin in input direction
scl=1;
_nop_();
_nop_();
flag=sda;             //if flag=1 nack and if 0 ack properly write
_nop_();
_nop_();
scl=0;
 
}


void start(void)
{

  sda=1;
  scl=1;
	_nop_();
	_nop_();
  sda=0;
  _nop_();
  _nop_();
     scl=0;


}


void stop(void)
{
 sda=0;
  scl=1;
	_nop_();
	_nop_();
  sda=1;
  _nop_();
  _nop_();
     scl=0;
}

/***************************i2c function stop***********************************/


/**************************rtc function*****************************/
void rtc_write(unsigned char h,unsigned char m,unsigned char s)
{
 
	start();
	
	i2c_write(0xa2);        //rtc address
	
	i2c_write(0x00);        //rtc register starting address
	
	i2c_write(0x00);        //control register 1
	
	i2c_write(0x00);        //control register 2
	
	i2c_write(s);		//sec register
	
	i2c_write(m);           //minute register
	
	i2c_write(h);          //hour register
	
	stop();

}

void rtc_read(void) 
{

	start();
	
	i2c_write(0xa2);        //rtc write register

	i2c_write(0x02);       //address register of sec

	start();             

	i2c_write(0xa3);        //rtc read address

	sec=i2c_read();
	ack_w();
	
	sec=(sec & 0x7f);

	min=i2c_read();
	ack_w();
	min=(min & 0x7f);
	
	
	hrs=i2c_read();
	hrs=(hrs & 0x3f);
	nack_w();

}


void display(void)
{
  unsigned char hh,hl,mh,ml,sh,sl;
 
  hh=hrs & 0xf0;
  hh=hh>>4;
  hh=hh | 0x30;

  hl=hrs & 0x0f;
  hl=hl | 0x30;


  mh=min & 0xf0;
  mh=mh>>4;
  mh=mh | 0x30;

  ml=min & 0x0f;
  ml=ml | 0x30;

  sh=sec & 0xf0;
  sh=sh>>4;
  sh=sh | 0x30;

  sl=sec & 0x0f;
  sl=sl | 0x30;



  tx(hh);
  tx(hl);

  tx(':');

  tx(mh);
  tx(ml);

  tx(':');

  tx(sh);
  tx(sl);

 
 // tx(0x0a);              //line feed  new line



}
	//*****************************uart start
void init_uart(void)
{
	init_timer();
	SCON=0X52;
	

}
void init_timer(void)
{
	TMOD|=0X20;
	TH1=0XFD;
	TR1=1;
}

void tx(unsigned char a)
{
	 while(!TI);
 	SBUF=a;
	 TI=0;
}

 
 
 //****************uart stop //****************uart stop