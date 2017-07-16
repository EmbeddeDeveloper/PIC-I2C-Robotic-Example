 #include <REG51F.H>
sbit ts1=P3^2;
sbit ts2=P3^3;
sbit en1=P1^0;
sbit dc1=P1^1;
sbit dc2=P1^2;
void delay(unsigned int time);
void main()
{
	
	while(1)
	{
		if(ts1==1)
		{
		en1=0;	
		}	
		else
		{  
			while(1)
	    		{
back:			en1=1;
			dc1=1;
			dc2=0;
			delay(1);
 		 
			if(ts2==1)
			{
				en1=0;
			}
			else
			{
				while(1)
				{
				en1=1;
				dc1=0;
				dc2=1;
				delay(1); 
				if(ts1==0)
				goto back;
				}
			}
			}
		}	
	}
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(j=0;j<time;j++)
	for(i=0;i<=120;i++);
}
