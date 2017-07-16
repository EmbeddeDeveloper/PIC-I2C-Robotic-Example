#include <REG51F.H>
#include<intrins.h>
//-------------------------//
void start();
void stop();
void shout();
void shin();
void err();
void nack();
void rd1();
void min();
void rd();
void wr();
void ack();
void init_rtc();
//-------------------------//
bit cy;
unsigned int A,i,temp,val,R0,R1;
sbit SDA=P1^7;
sbit SCL=P1^6;
//-------------------------//
void main()
{
	init_rtc();
	//wr();
	while(1)
	{
		rd();
		P0=R0;
		rd1();
	}
}
//-------------------------//
void init_rtc()
{
	start();
	
	A=0xa2;	   	// write mode selected
	shout();
	if(cy)
		err();

	A=0x00;		// 	rtc address define
	shout();
	if(cy)
		err();

	A=0x00;		   // control status 1
	shout();
	if(cy)
		err();

	A=0x00;		  // control status 2
	shout();
	if(cy)
		err();


	A=0x01;		// staritng second from 15
	shout();
	if(cy)
		err();

	stop();
}
//-------------------------//
void rd()				  //4 second
{
	//R0=0x40;
	start();

	A=0xa2;			 // write mode selected
	shout();
	if(cy)
		err();

	A=0x02;				// for second
	shout();
	if(cy)
		err();

	start();
	
	A=0xa3;				// read mode selected
	shout();
	if(cy)
		err();
	
	shin();
	nack();
    	R0=val&0x7f;
	stop();
}
//-------------------------//
void rd1()		// 4 minit
{
	start();

	A=0xa2;
	shout();
	if(cy)
		err();

	A=0x03;
	shout();
	if(cy)
		err();

	start();
	
	A=0xa3;
	shout();
	if(cy)
		err();
	
	shin();
	nack();
    R1=val&0x7f;
	stop();
}
//-------------------------//
void shout()
{
	SDA=0;
	for(i=0;i<8;i++)
	{
		temp=A&0x80;
		if(temp==0x80)
			SDA=1;
		else 
			SDA=0;
		A=A<<1;
		SCL=1;
		_nop_();
		_nop_();
		_nop_();
		SCL=0;
	}
	SDA=1;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	cy=SDA;
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
}
//-------------------------//
void shin()
{
	SDA=1;
	for(i=0;i<8;i++)
	{
		SCL=1;
		if(SDA)
			val=val|0x01;
		SCL=0;
		_nop_();
		_nop_();
		_nop_();
		if(i<7)
			val=val<<1;
	}
}
//-------------------------//
void err()
{
	P0=0x20;
//	err();
}
//-------------------------//
void start()
{
	SDA=1;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	SDA=0;
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
}
//-------------------------//
void stop()
{
	SDA=0;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	SDA=1;
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
}
//-------------------------//
void ack()
{
	SDA=0;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
}
//-------------------------//
void nack()
{
	SDA=1;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	SCL=0;
} 	