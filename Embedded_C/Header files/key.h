/*--------------------------------------------------------------------------
KEY.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __KEY_H__
#define __KEY_H__
//-----------------------------------------
//-----------------------------------------
unsigned char ds1,ds2,ds3,ds4;

sbit sl1 = P2^0;
sbit sl2 = P2^1;
sbit sl3 = P2^2;
sbit sl4 = P2^3;

sbit krl1 = P2^4;
sbit krl2 = P2^5;
sbit krl3 = P2^6;
sbit krl4 = P2^7;

sbit buz  = P1^5;
bit start_buzzer;

bit key_ready = 0;
bit nkp = 0;
bit tb =0;
unsigned char key_code = 0;
unsigned char krcount  = 0;
unsigned char scan_no  = 0;
unsigned char dcount   = 0;
bit c;

unsigned char Pattern[] = {0x0fc,0x60,0xda,0xf2,0x66,0xb6,
							0xbe,0xe0,0xfe,0xe6,0xee,0x3e,0x9c,
							0x7a,0x9e,0x8e,0x00,0xff};
//unsigned char ascii_Pattern[] = {"0123456789ABCDEF"};
//-----------------------------------------
//-----------------------------------------
void init_keypad();
void scanner();
void k();
void debounce();
void out_debounce();
void l1_k();
void key_release();
void delay(unsigned int time);
void buzzer();
//-----------------------------------------
//-----------------------------------------
void init_keypad()
{
	krl1 = krl2 = krl3 = krl4 = 1;
	scan_no = 0;
	dcount = 33 ;
	krcount = 32;
	key_ready = 0;
	nkp = 0	;
	start_buzzer = 0;
}

void scanner()
{
	switch(scan_no)
	{
		case 0: sl1=0;
				sl2=sl3=sl4=1;
				P0=Pattern[ds1];
				c=krl1;
				k();
				scan_no++;
				break;
		case 1: c=krl2;
				k();
				scan_no++;
				break;
		case 2: c=krl3;
				k();
				scan_no++;
				break;
		case 3: c=krl4;
				k();
				scan_no++;
				P0=0;
				break;
				
		case 4: sl1=sl3=sl4=1;
				sl2=0;
				P0=Pattern[ds2];
				c=krl1;
				k();
				scan_no++;
				break;
		case 5: c=krl2;
				k();
				scan_no++;
				break;
		case 6: c=krl3;
				k();
				scan_no++;
				break;
		case 7: c=krl4;
				k();
				scan_no++;
				P0=0;
				break;

		case 8: sl1=sl2=sl4=1;
				sl3=0;
				P0=Pattern[ds3];
				c=krl1;
				k();
				scan_no++;
				break;
		case 9: c=krl2;
				k();
				scan_no++;
				break;
		case 10:c=krl3;
				k();
				scan_no++;
				break;
		case 11:c=krl4;
				k();
				scan_no++;
				P0=0;
				break;

		case 12:sl1=sl2=sl3=1;
				sl4=0;
				P0=Pattern[ds4];
				c=krl1;
				k();
				scan_no++;
				break;
		case 13:c=krl2;
				k();
				scan_no++;
				break;
		case 14:c=krl3;
				k();
				scan_no++;
				break;
		case 15:c=krl4;
				k();
				scan_no=0;
				P0=0;
				break;
	}
}

void k()
{
	if(key_ready)
		out_debounce();
	else
	{
		if(dcount!=33)
			debounce();
		else
		{
			if(!c)
			{
				dcount--;
				key_code = scan_no;
				//ds2 = 1;
			}
		}
	}
}

void debounce()
{
	dcount--;
	if(dcount==0)
	{
		if(!c)
			key_ready=start_buzzer=1;
	 	dcount=33;	
	}
}

void out_debounce()
{
	if(c)
		l1_k();
	else
		krcount=32;
}

void l1_k()
{
	krcount--;
	if(krcount==0)
	{
		nkp=1;
		start_buzzer=0 ;
		krcount=32;
	}
}

void key_release()
{
	while(!nkp);
	key_ready=0;
	nkp=0;
}

void delay(unsigned int time)
{
 	unsigned int i,j;		
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}

void buzzer()
{
	if(start_buzzer)
		buz = ~ buz;
}
//-----------------------------------------
//-----------------------------------------
#endif
