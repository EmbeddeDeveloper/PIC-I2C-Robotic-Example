#include <REG51F.H>
#include<intrins.h>
//#include<stdio.h>

sbit scl=P1^6;
sbit sda=P1^7;

void start();
void stop();
void shout(unsigned char ch);
void shin();
void nack();
void error();
void eeprom_read();
void eeprom_write();
void delay(unsigned int time);
void ack();
unsigned char flag,data0=0x00,k1=0x00;

void main()
{
  	eeprom_write();
  	while(1)
  	{
  		delay(65);
  		eeprom_read();
  	}
}

void start()
{
   sda=1;
   scl=1;
   _nop_();
   _nop_();
   _nop_();
   sda=0;
   _nop_();
   _nop_();
   scl=0;
}

void stop()
{
   sda=0;
   scl=1;
   _nop_();
   _nop_();
   _nop_();
   sda=1;
   _nop_();
   _nop_();
   scl=0;
}

void shout(unsigned char ch)
{
   unsigned char i,j=0x80,k;
   //sda=0;
   scl=0;
   for(i=0;i<8;i++)
   {
     k=(ch&j);
	 if(k==0)
	 {
	   sda=0;
     }
	 else
	 {
	   sda=1;
	 }
	 scl=1;
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 scl=0;
	 j=j>>1;
   }
   sda=1;
   _nop_();
   scl=1;
   _nop_();
   _nop_();
   flag=sda;
   _nop_();
   _nop_();
   scl=0;
}

void shin()
{
   unsigned char a,j=0x80;
   for(a=0;a<8;a++)
   {
     scl=1;
	 _nop_();
	 _nop_();
	 if(sda)
	 k1=(j|k1);
	 j=j>>1;
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 scl=0;
	 }
	 data0=k1;
	 }

void eeprom_read()
{
	unsigned int ii;
   	start();
   	shout(0xa0);
   	if(flag)
   		error();
   	shout(0xaa);
   	if(flag)
   		error();
   	shout(0x00);
   	if(flag)
   		error();
   	for(ii=0;ii<9;ii++)
   	{
   		start();
   		shout(0xa1);
   		if(flag)
   			error();
   		shin();
   		P0=data0;
   		delay(500);
   	}
   	nack();
   	stop();
}

void eeprom_write()
{
   start();
   shout(0xa0);
   if(flag)
   error();
   shout(0xaa);
   if(flag)
   error();
   shout(0x00);
   if(flag)
   error();
   shout(0x00);
   if(flag)
   error();
   shout(0x01);
   if(flag)
   error();
   shout(0x02);
   if(flag)
   error();
   shout(0x03);
   if(flag)
   error();
   shout(0x04);
   if(flag)
   error();
   shout(0x05);
   if(flag)
   error();
   shout(0x06);
   if(flag)
   error();
   shout(0x07);
   if(flag)
   error();
   shout(0x08);
   if(flag)
   error();	    
   shout(0x09);
   if(flag)
   error();
   stop();
}

void error()
{
   P0=0x0f0;
}        	 

void nack()
{
  sda=1;
  scl=1;
  _nop_();
  _nop_();
  _nop_();
  scl=0;
}

void delay(unsigned int time)
{
int x,y;
for(x=0;x<time;x++)
for(y=0;y<120;y++);
}

void ack()
{
scl=1;
sda=0;
_nop_();
_nop_();
scl=0;
}