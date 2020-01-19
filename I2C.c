#include <I2C.h>
void Delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);
}
void I2CStart()                  //I2cstart
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();//keep SDA time>4.7us
	SDA=0;
	Delay10us();//time>4us
	SCL=0;			
	Delay10us();		
}
void I2cStop()                 //iicstop
{
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();//time>4.7us
	SDA=1;
	Delay10us();		
}
unsigned char I2cSendByte(unsigned char dat)                 //i2c send data
{
	unsigned char a=0,b=0;	
	for(a=0;a<8;a++)
	{
		SDA=dat>>7;	 
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();//time>4.7us
		SCL=0;
		Delay10us();//time>4us		
	}
	SDA=1;
	Delay10us();
	SCL=1;
	while(SDA)//wait answer
	{
		b++;
		if(b>200)	 //answer fail
		{
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
 	return 1;		
}
unsigned char I2cReadByte()      //i2c read data            
{
	unsigned char a=0,dat=0;
	SCL=0;
	SDA=1;			
	Delay10us();
	for(a=0;a<8;a++)
	{
		SCL=1;
		Delay10us();
		dat<<=1;
		dat|=SDA;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	return dat;		
}
void PCF8591Send(char addr,char dat)              
{
	I2cStart();
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cStop();
}
int PCF8591Read(char addr)                      
{
	int dat;
	I2cStart();
	I2cSendByte(addr + 1);
	dat = I2cReadByte();
	I2cStop();
	return dat;
}