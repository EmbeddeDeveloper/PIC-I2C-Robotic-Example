// dc motor (forward and reverse)

#include <REG51F.H>

//--------------------------------------//
sbit	en12=P1^0;		//enable pin
sbit	en34=P1^5;		//enable pin

sbit	inp1=P1^1;		//inp1 for mtr 1
sbit	inp2=P1^2;		//inp2 for mtr 1
sbit	inp3=P1^3;		//inp1 for mtr 2
sbit	inp4=P1^4;		//inp2 for mtr 2

void 	delay(unsigned int);
//--------------------------------------//

void	main()
{
	en12=1;
	en34=1;

	while(1)
	// start of while loop
	{
	inp1=1;		 //rotate forward for motor1
	inp2=0;
	
	inp3=1;		 //rorate forward for motor2
	inp4=0;
	
	delay(50000);	 //then wait
	delay(50000);
	
	inp1=0;	 	 //stop the motor1
	inp2=0;
	
	inp3=0;		 //stop the motor2
	inp4=0;
	
	delay(50000); 	 // then wait
	delay(50000);
	
	inp1=0; 	 //rotate reverse for motor1
	inp2=1;
	
	inp3=0;		 //rotate reverse for motor2
	inp4=1;

	delay(50000);	 // then wait
	delay(50000);
	}
	// end of while loop..

}

//-----------------------------------//
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
	for(j=0;j<150;j++);
} 
