#include<REG51F.H>
#include<intrins.h>
	sbit sda=P1^7;
	sbit scl=P1^6;
	void delay(unsigned int time);
	void start(void);
	void stop(void);
	void ack();
	void nack();
	void sh_in();
	void sh_out(unsigned char ch);
	void write();
	void read();
	unsigned char c,r,p,o,recdata,flag;
void main()
	{ 
	 while(1)
	 {	r=0x01; 
	 	for(o=0;o<8;o++)
		{
	    
	    write();
	    read();
		P0=recdata;
		delay(1000);
		r=r<<1;
		}
				
		r=0x80;
		for(p=0;p<8;p++)
		{
		write();
	   	read();
		P0=recdata;
		delay(1000);
		r=r>>1;
		} 
		}
		}
	/*while(1)
	    {
		  read();
		  P0=recdata;

		} */

	
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
	void ack()
		{
		  sda=0;
		  scl=1;
		  _nop_();
		  _nop_();
		  _nop_();
		  scl=0;
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
	void sh_out(unsigned char ch)
		{
		 unsigned char i,j=0x80,temp;

		 scl=0;	
		 for(i=0;i<8;i++)
			{
			temp=(ch&j);
			if(temp==0)
				sda=0;
			else
				sda=1;
			 scl=1;
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
	void sh_in()
		{
		unsigned char i,j=0x80,temp1=0;
		 sda=1;
		 
		 for(i=0;i<8;i++)
		 	{
		 	  scl=1;
			  if(sda)
			  temp1=(temp1|j);
			  j=j>>1;
			  _nop_();
			  _nop_();
			  _nop_();
			  scl=0;
		 	}
			recdata=temp1;
			//P0=temp1;
		}
	void error()
		{
		  P0=0x11;
		}
	void write()
		{
		 start();
		 sh_out(0x40);
		 if(c)
		 error();
		
		 sh_out(r);
		 if(c)
		 error();
		 stop();
		}
	void read()
		{
		 start();
		 sh_out(0x41);
		 if(c)
		 error();
		 sh_in();
		 nack();
		 stop();
		}
	void delay(unsigned int time)
	     { unsigned int m,n;
		  for(m=0;m<time;m++)
		  for(n=0;n<120;n++);
		 }	 