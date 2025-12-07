#include <REGX52.h>

sbit L1 = P1^4;//左侧轮A GPIO
sbit L2 = P1^5;//左侧轮B GPIO
sbit R1 = P1^2;//右侧轮A GPIO
sbit R2 = P1^3;//右侧轮B GPIO

/*
左侧轮旋转
@param s 正反转 正值为正转，负值反转
*/
void LS(int s){
	if(s>0){
		L1 = 0;
		L2 = 1;
	}else{
		L1 = 1;
		L2 = 0;
	}
}

/*
右侧轮旋转
@param s 正反转 正值为正转，负值反转
*/
void RS(int s){
	if(s>0){
		R1 = 1;
		R2 = 0;
	}else{
		R1 = 0;
		R2 = 1;
	}
}


/*
左侧轮停转
*/
void LO(){
	L1=0;
	L2=0;
}

/*
右侧轮停转
*/
void RO(){
	R1=0;
	R2=0;
}



