/*
51智能小车 
*/

#include <REGX52.H>
#include "Track.h"
#include "Timer.h"
#include "car.h"


sbit DL = P0^0;    
sbit DR = P0^5;    
sbit MID_L = P0^2; 
sbit MID_R = P0^3; 

int step = 0;          
bit sensor_lock = 0;   


void Delay(int m) {	
	while(m--) {
		unsigned char i, j;
		i = 90; j = 163;
		do { while (--j); } while (--i);
	}
}

// 软停
void Soft_Stop() { Stop(); Delay(2); }

// 急刹 终点停车
void Hard_Stop() { Stop(); Backward(21); Delay(1); Stop(); }

// 智能过线
void Smart_Skip() {
    Forward(21); 
    { unsigned int k=500; while(k--); } 
    while((DL == 1 || DR == 1)) { Forward(21); } 
}
//带有修正的右转
void Correction_Right(int time) {
    TurnRight(27);  
    Delay(time); 
    while(1) { if(MID_L == 1 || MID_R == 1) break; }
    Soft_Stop(); Delay(2);    
}

// 带有修正的左转 
void Correction_Left(int time) {
    TurnLeft(27);   
    Delay(time);
    while(1) { if(MID_L == 1 || MID_R == 1) break; }
    Soft_Stop(); Delay(2);
}
 

void Blind_Correction_Right(int time) {
    RLeft(40);   
    Delay(time); 
    Soft_Stop(); Delay(2);
}

// 掉头 180 
void TurnBack_180(int time) {
    TurnLeft(30); Delay(time); 
    while(1) { if(MID_L == 1 || MID_R == 1) break; }
    Hard_Stop(); Delay(4);
}

void main() {
	Timer0_Init();  
    Forward(45); Delay(4); 
   while(1) {		
        track();

        if((DL == 1 || DR == 1) && sensor_lock == 0) {
            unsigned int i = 500; while(i--); 
            if(DL == 1 || DR == 1) { step++; sensor_lock = 1; }
        }
		
        if(DL == 0 && DR == 0) sensor_lock = 0;
		
        switch(step) {
            
            // 推黑块                      
            case  1: Smart_Skip(); sensor_lock = 0; step = 10; break;
			case 11: Smart_Skip(); sensor_lock = 0; step = 20; break;
			case 21: Smart_Skip(); sensor_lock = 0; step = 30; break;
			case 31: Smart_Skip(); sensor_lock = 0; step = 40; break;
			/*
			case 41:
				Hard_Stop(); Delay(10);
                Blind_Correction_Right(7); 
                 
                Forward(20); Delay(2); 
                sensor_lock = 0; step = 60; 
                break;
            */
			case 41: Smart_Skip(); sensor_lock = 0; step = 50; break;
			case 51: 
                Hard_Stop(); Delay(10);
                Blind_Correction_Right(6); 
                 
                Forward(21); Delay(2); 
                sensor_lock = 0; step = 60; 
                break;
			
            // 去 B 角 
            
            case 61: 
				Forward(21); 
				{ unsigned int k=500; while(k--); } 
				while((DL == 1 || DR == 1)) { Forward(19); }  
				sensor_lock = 0; step = 70; break; 
            case 71: 
				Forward(21); 
				{ unsigned int k=500; while(k--); } 
				while((DL == 1 || DR == 1)) { Forward(19); }  
				sensor_lock = 0; step = 80; break; 
            
            // 到达 B 角
            case 81:
                Hard_Stop(); Delay(10);
                
                
                Backward(21); Delay(3); Hard_Stop();
                TurnBack_180(15);
                               
                Forward(25); while(DL==1||DR==1){track();} 
                sensor_lock = 0; step = 90; 
                break;

            // 回中心 
            
            case 91: Smart_Skip(); sensor_lock = 0; step = 100; break;
            case 101: Smart_Skip(); sensor_lock = 0; step = 110; break;
            
            
            case 111:
                Hard_Stop(); Delay(10);                  
                // 135度 是 45度 的 3倍               
                // 【调试】：单轮转135度比较慢，时间给足
//                Blind_Correction_Right(18); 
				Correction_Right(16); 
                
                Forward(25); Delay(2); 
                sensor_lock = 0; step = 120; 
                break;

            // 推白块去 E 区 
            
            case 121: Smart_Skip(); sensor_lock = 0; step = 230; break; 
						case 231: Smart_Skip(); sensor_lock = 0; step = 240; break;
						case 241: Smart_Skip(); sensor_lock = 0; step = 130; break;
			// 白色物块左右两边的圆弧
            case 131: 
                Hard_Stop(); Delay(10); // 大正方形上边边框停顿确认               
                step = 140; 
                break;
                
            case 141: 
//                Forward(30);                                
//                sensor_lock = 0; step = 141; 
//                break;
//            
//            case 141: 
//                Smart_Skip(); sensor_lock = 0; step = 150; break;
//                
//            case 151: 
//                Hard_Stop(); Delay(10);
//                
//                //  E 区
                Forward(10); Delay(5); Hard_Stop();
                
                // ====== 第五阶段：回家 ======
                Backward(21); Delay(3); Hard_Stop();
                TurnBack_180(15); // 掉头
                
                Forward(25); while(DL==1||DR==1){track();} 
                sensor_lock = 0; step = 160; 
                break;

            // 回家
            case 161: Smart_Skip(); sensor_lock = 0; step = 170; break;
            case 171: Smart_Skip(); sensor_lock = 0; step = 180; break;
            case 181: Smart_Skip(); sensor_lock = 0; step = 190; break;
            case 191: Smart_Skip(); sensor_lock = 0; step = 200; break;
            case 201: Smart_Skip(); sensor_lock = 0; step = 210; break;
            case 211: Smart_Skip(); sensor_lock = 0; step = 220; break;
            
            case 221:
                Forward(21); Delay(4); Hard_Stop(); 
                Stop(); while(1); 
                break;
        }
	}
}




