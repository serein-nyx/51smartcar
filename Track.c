#include "car.h"
#include <REGX52.H>
#define fs 20
#define rs 18
#define ts 19
sbit D1 = P0^1;
sbit D2 = P0^2;
sbit D3 = P0^3;
sbit D4 = P0^4;


void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 90;
	j = 163;
	do
	{
		while (--j);
	} while (--i);
}

void track() //循迹实际执行函数
{
	//D1 = ~D1;
	//D2 = ~D2;
	//D3 = ~D3;
	//D4 = ~D4;
	if(D1==0&&D2==0&&D3==0&&D4==0)
	{Forward(fs);}
	if(D1==1&&D2==1&&D3==1&&D4==1) 
	{ Forward(fs);}
	if(D1==0&&D2==1&&D3==0&&D4==0)
	{
		RRight(rs);
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{Forward(fs);}
	}
	if(D1==0&&D2==0&&D3==1&&D4==0)
	{
		RLeft(rs);
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{Forward(fs);}
	}
	if(D1==0&&D2==0&&D3==1&&D4==1)
	{
		Forward(fs);
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			Stop();
			Delay50ms();
			TurnRight(ts);
		}
	}
	if(D1==1&&D2==1&&D3==0&&D4==0)
	{
		Forward(fs);
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			Stop();
			Delay50ms();
			TurnLeft(ts);
		}
	}
	if((D1==0&&D2==0&&D3==0&&D4==1)||(D1==0&&D2==1&&D3==0&&D4==1)||(D1==0&&D2==1&&D3==1&&D4==1))
	{
		Forward(fs);
		Delay50ms();
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			Stop();
			Delay50ms();
			TurnRight(ts);
		}
	}	
	if((D1==1&&D2==0&&D3==0&&D4==0)||(D1==1&&D2==0&&D3==1&&D4==0)||(D1==1&&D2==1&&D3==1&&D4==0))
	{
		Forward(fs);
		Delay50ms();
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			Stop();
			Delay50ms();
			TurnLeft(ts);
		}
	}
	if(D1==0&&D2==1&&D3==1&&D4==0)
	{
		if(D1==1)
		{
			TurnLeft(ts);
		}
	}
	
	if(D1==0&&D2==1&&D3==1&&D4==0)
	{
		if(D4==1)
		{
			TurnLeft(ts);
		}
	}
	
}