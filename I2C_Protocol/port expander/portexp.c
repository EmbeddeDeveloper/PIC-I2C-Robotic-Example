#include <REG51F.H>
#include<intrins.h>
#include<stdio.h>

sbit scl=P1^6;
sbit sda=P1^7;

void start(void);
void stop(void);
void shout(unsigned char ch);
void shin(void);
// void ack();
void nack();
void err();
void peread();
void pewrite();
unsigned char c,flag,rec_data;

void main()
{
  pewrite();
  
  while(1)
  {
  peread();
  P0=rec_data;
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
   unsigned char i,j=0x80,k=0;
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
   unsigned char a,j=0x80,k1=0;
   sda=1;
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
	 rec_data=k1;
}

void peread()
{
   start();
   shout(0x41);
   if(c)
   err();
   shin();
   nack();
   stop();
}

void pewrite()
{
   start();
   shout(0x40);
   if(c)
   err();
   shout(0x81);
   if(c)
   err();
   stop();
}

void err()
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