#include "basic.h"
#include <REGX52.H>


sbit ENa = P1^0;//电机使能引脚A
sbit ENb = P1^1;//电机使能引脚B


int compare,counter,compare1; //通过compare调速，值越大越块

void Timer0_Routine() interrupt 1
{
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	counter++;
	if(counter > 120){
		counter = 0;
	}
	if(counter < compare){
		ENa = 1;
	}else{
		ENa = 0;
	}
	if(counter < compare1){
		ENb = 1;
	}else{
		ENb = 0;
	}
}


/*
Stop函数
停止运动
*/
void Stop(){
	LO();
	RO();
}

/*
forward前进函数
@param speed，速度，要求传为正值
*/
void Forward(int speed){
	compare = speed;
	compare1 = speed-4;
	LS(1);
	RS(1);
}

/*
backward前进函数
@param speed，速度，要求传为正值
*/
void Backward(int speed){
	compare = speed;
	compare1 = speed-2;
	LS(-1);
	RS(-1);
}

/*
TurnLeft左转函数
@param speed，速度，建议比直行后退小
*/
void TurnLeft(int speed){
	compare = speed;
	compare1 = speed-1;
	LS(-1);
	RS(1);
}

/*
TurnRight右转函数
@param speed，速度，建议比直行后退小
*/
void TurnRight(int speed){
	compare = speed;
	compare1 = speed-1;
	RS(-1);
	LS(1);
}

/*
RRight右转修正
@param speed 速度，要求传为正值
*/
void RRight(int speed){
	compare = speed;
	compare1 = speed-1;
	LO();
	RS(1);
}

/*
RLeft左转修正
@param speed 速度，要求传为正值
*/
void RLeft(int speed){
	compare = speed;
	compare1 = speed-1;
	RO();
	LS(1);
}





