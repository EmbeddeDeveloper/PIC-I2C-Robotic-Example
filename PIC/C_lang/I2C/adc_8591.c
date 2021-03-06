#include<pic.h>
void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_ack();
void i2c_wait();
void i2c_nack();
void init_uart();
void tx(unsigned char temp);
void i2c_restart();
unsigned char i2c_read();
void i2c_send(unsigned char dat);
void delay(unsigned int time);
unsigned char temp;
void main()
{
	unsigned char i;
	unsigned char i2cdata[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};/*  define data to be send on port  */
	TRISB=0;
	init_uart();
	i2c_init();  /*  initiate the i2c  */
	i2c_start();/*  initiate the start condition  */
	i2c_send(0x91);/*  send the slave address  */
	i2c_read();
		//tx(temp);
	i2c_stop();
}
void i2c_init()
{
	TRISC3=1;/* SDA & SCL as input pin  */
	TRISC4=1;/*  These pin configured either as i/p or o/p  */
	
	SSPSTAT!=0x80;/*  Disables the Slew rate  */
	SSPCON=0x28;/*  Select master mode, SSPEN=1, clock=Fosc/(4*(SSPADD+1))  */
	SSPADD=0x28;/*  100 kHz @ 4 MHz Fosc  */
}
void i2c_start()
{
	SEN=1;   /*  Enable the start bit  */
	while(SEN); /* Check the bit while not completely set  */
}
void i2c_stop()
{
	PEN=1;
	while(PEN);
}
void i2c_ack()
{
	ACKDT=0;
	ACKEN=1;
	while(ACKEN);
}
void i2c_wait()
{
	while((SSPCON2 & 0x1f) || (SSPSTAT & 0x04));
}
void i2c_send(unsigned char dat)
{
	SSPBUF=dat;
	PORTB=SSPBUF;
	while(BF);
	i2c_wait();
}
void delay(unsigned int time)
{
	unsigned int m,n;
	for(m=0;m<time;m++)
	for(n=0;n<40;n++);
}

void i2c_nack()
{
	ACKDT=1;
	ACKEN=1;
	while(ACKEN);
}
unsigned char i2c_read()
{
	unsigned char temp;
	RCEN=1;
	while(!BF);
	temp=SSPBUF;
	i2c_wait();
	PORTB=temp;
	return temp;
}
/*void i2c_restart()
{
	RSEN=1;
	while(RSEN);
}*/
void init_uart()
{
	TXSTA=0x24;
	SPBRG=25;
	RCSTA=0x80;	
}
void tx(unsigned char temp)
{
	TXREG=temp;
	while(!TXIF);
	TXIF=0;
}
