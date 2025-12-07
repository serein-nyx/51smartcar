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




/*
51智能小车 - 全流程 
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

//急刹
void Hard_Stop() { Stop(); Backward(40); Delay(1); Stop(); }

// 直冲过线
void Smart_Skip() {
    Forward(45); Delay(2); 
    while((DL == 1 || DR == 1)) { Forward(45); }
}
void Skip_Line() { Smart_Skip(); }

// 偏向过线
void Bias_Skip_Left() { Smart_Skip(); TurnLeft(40); Delay(3); }


//左转90
void TurnLeft_90(int time) {
    TurnLeft(50); Delay(time); 
    while(1) { if(MID_L == 0 || MID_R == 0) break; }
    Hard_Stop(); Delay(4);    
}

//右转90
void TurnRight_90(int time) {
    TurnRight(50); Delay(time);
    while(1) { if(MID_L == 0 || MID_R == 0) break; }
    Hard_Stop(); Delay(4);
}

//掉头180
void TurnBack_180(int time) {
    TurnLeft(50); Delay(time); 
    while(1) { if(MID_L == 0 || MID_R == 0) break; }
    Hard_Stop(); Delay(4);
}


void main() {
    P2_0 = 0; Timer0_Init(); 
    Forward(45); Delay(15); 

    while(1) {
        track(); 

        if((DL == 1 || DR == 1) && sensor_lock == 0) {
            Delay(5); 
            if(DL == 1 || DR == 1) { step++; sensor_lock = 1; }
        }
        if(DL == 0 && DR == 0) sensor_lock = 0;

        switch(step) {
            
            //  绿块 (Step 1-70) 
            case 1: Skip_Line(); sensor_lock = 0; step = 10; break;

            case 11: Skip_Line(); sensor_lock = 0; step = 20; break;

            case 21: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 30; break;

            case 31: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 40; break;

            case 41: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 50; break;

            case 51: Skip_Line(); sensor_lock = 0; step = 60; break;

            case 61: Hard_Stop(); Delay(10); step = 71; break;

            //  蓝块 (Step 71-200) 
            case 71: // A区掉头
                Forward(45); Delay(60); Hard_Stop(); Backward(45); Delay(12); Hard_Stop();
                TurnBack_180(18); Forward(45); while(DL==1||DR==1){track();} sensor_lock = 0; step = 79; break;
            case 80: Skip_Line(); sensor_lock = 0; step = 89; break;
            case 90: Bias_Skip_Left(); sensor_lock = 0; step = 99; break;
            case 100: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 109; break;
            case 110: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(4); sensor_lock = 0; step = 119; break;
            case 120: Skip_Line(); sensor_lock = 0; step = 129; break;
            case 130: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 139; break;
            case 140: Skip_Line(); sensor_lock = 0; step = 149; break;
            case 150: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 159; break;
            case 160: Hard_Stop(); Delay(10); step = 200; break;

            // 红块 (Step 200-400) 
            case 200: // D区掉头
                Backward(45); Delay(12); Hard_Stop(); TurnBack_180(18); 
                Forward(45); while(DL==1||DR==1){track();} sensor_lock = 0; step = 209; break;
            case 210: Skip_Line(); sensor_lock = 0; step = 219; break;
            case 220: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 229; break;
            case 230: Skip_Line(); sensor_lock = 0; step = 239; break;
            case 240: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 249; break;
            case 250: Skip_Line(); sensor_lock = 0; step = 259; break;
            case 260: Skip_Line(); sensor_lock = 0; step = 269; break;
            case 270: Skip_Line(); sensor_lock = 0; step = 279; break;
            case 280: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 289; break;
            case 290: Skip_Line(); sensor_lock = 0; step = 299; break;
            case 300: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 309; break;
            case 310: Skip_Line(); sensor_lock = 0; step = 319; break;
            case 320: Hard_Stop(); Delay(10); step = 400; break;

            //  黑块 (Step 400-500)
            case 400: // C区掉头
                Forward(45); Delay(60); Hard_Stop(); Backward(45); Delay(12); Hard_Stop();
                TurnBack_180(18); Forward(45); while(DL==1||DR==1){track();} sensor_lock = 0; step = 409; break;
            case 410: Skip_Line(); sensor_lock = 0; step = 419; break;
            case 420: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 429; break;
            case 430: Skip_Line(); sensor_lock = 0; step = 439; break;
            case 440: Skip_Line(); sensor_lock = 0; step = 449; break;
            case 450: Hard_Stop(); Delay(10); TurnBack_180(24); Forward(45); Delay(6); sensor_lock = 0; step = 459; break;
            case 460: Skip_Line(); sensor_lock = 0; step = 469; break;
            case 470: Skip_Line(); sensor_lock = 0; step = 479; break;
            case 480: Hard_Stop(); Delay(4); TurnLeft_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 489; break;
            case 490: Hard_Stop(); Delay(10); step = 500; break;

            // 白块 (Step 500-600) 
            case 500: // B区掉头
                Forward(45); Delay(60); Hard_Stop(); Backward(45); Delay(12); Hard_Stop();
                TurnBack_180(18); Forward(45); while(DL==1||DR==1){track();} sensor_lock = 0; step = 509; break;
            case 510: Skip_Line(); sensor_lock = 0; step = 519; break;
            case 520: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 529; break;
            case 530: Skip_Line(); sensor_lock = 0; step = 539; break;
            case 540: Hard_Stop(); Delay(4); TurnRight_90(6); Forward(45); Delay(6); sensor_lock = 0; step = 549; break;
            case 550: Skip_Line(); sensor_lock = 0; step = 559; break;
            case 560: Skip_Line(); sensor_lock = 0; step = 569; break;
            case 570: Skip_Line(); sensor_lock = 0; step = 579; break;
            case 580: Hard_Stop(); Delay(10); step = 600; break; // E区停车，跳转到回家

            //  回家 (Step 600 Start) 

            case 600: 
                //  进站 E 区 (白块放好)
                Forward(45); Delay(60); Hard_Stop();
                
                //  倒车
                Backward(45); Delay(12); Hard_Stop();

                // 掉头 180 (注意：这次掉头会扫到两次线！)
                                TurnBack_180(24); 
                
                // 排雷
                Forward(45); while(DL==1||DR==1){track();} 
                sensor_lock = 0; step = 609; // 第一条黑线 (内环)
                break;

            case 610: Skip_Line(); sensor_lock = 0; step = 619; break; // 第1次 (内环上)
            case 620: Skip_Line(); sensor_lock = 0; step = 629; break; // 第2次 (白块位)
            case 630: Skip_Line(); sensor_lock = 0; step = 639; break; // 第3次 (米字上)
            case 640: Skip_Line(); sensor_lock = 0; step = 649; break; // 第4次 (中心点)
            case 650: Skip_Line(); sensor_lock = 0; step = 659; break; // 第5次 (米字下)
            case 660: Skip_Line(); sensor_lock = 0; step = 669; break; // 第6次 (内环下)

            case 670: // 第7次：小正方形上边框
                Skip_Line(); 
                sensor_lock = 0; step = 679; 
                break;

            case 680: // 第8次：大正方形底边 
                
                Forward(45); 
                
               
                Delay(60); 
                                
                Hard_Stop();
                
               
                Stop(); while(1); 
                break;
        }
    }
}






