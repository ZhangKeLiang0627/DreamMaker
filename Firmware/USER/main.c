#include "sys.h"

unsigned char LengthTemp = 0;	//字符占像素长度（重要！）
uint8_t KeyNum;			//返回的键码值（在主程序中循环获得）
uint16_t RDNum1 = 0, RDNum2 = 0, RDNum3 = 0,
RDNum4 = 0, RDNum5 = 0, RDNum6 = 0,
RDNum7 = 0;	//随机数

int16_t FPS_Count;//帧率变量
char FPS[10] = "FPS";

uint8_t OLED_BUFF[128][4];
u8g2_t u8g2;	//初始化u8g2结构体

int main(void)
{ 
	
	delay_init();
 	OLED_Init();				//初始化OLED 
	
	Key_Init();
	TIM2_Key_Init();
	TIM4_Random_Init(8400 - 1, 10 - 1);
	
	Key_A0.LongPressOpen_Flag = 1;	//长按开关标志位开启
	
	Key_A0.DoublePressOpen_Flag = 0;	//双击开关标志位关闭
	
	
	u8g2Init(&u8g2); //u8g2图形库初始化
	u8g2_SetFont(&u8g2,u8g2_font_profont15_mr);//选择字库

//	FrontCover();//封面or开场动画
	
	while(1) 
	{	
		
		KeyNum = Key_GetNum();
		ui_proc();
	
	
	}
	
}



