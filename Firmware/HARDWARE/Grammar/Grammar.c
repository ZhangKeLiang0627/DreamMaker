#include "sys.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
  * @brief 封面
  * @param  无
  * @retval 无
  */
void FrontCover(void)
{	
	uint8_t k;	//做ui特效所需的变量
	OLED_ShowPicture(0,0,128,32,BMP2[0],1);//熊猫
	for(k = 0; k < 128; k += 25)//逐个刷新熊猫
	{
		OLED_PartialRefresh(0,k+25<128?k+25:128,0,4);
		delay_ms(300);
	}
	OLED_Clear();
	
	OLED_ShowString(0,0,"伪诗云",16,1);
	OLED_ShowString(24,16,"Designed by L",16,1);
	RightComeOut_Refresh();//出场刷新特效
}

/**
  * @brief 按键随机选择语法
  * @param  无
  * @retval 无
  */
void Grammar_Chioce(void)
{
	uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
	RDTempNum1 = RandomCreate() % 1000; //用一个随机数来选择2个不同的语法
	Time_ms ++;
	if(KeyNum == SHORT_PRESS)//单击刷新词条
	{
		Time_msForAnim = 0;	//清空屏保计时
		
		RightToLeft_Clear();//消退//清屏特效
//		OLED_Clear();
		
		if(RDTempNum1 >= 800)
		{
			Grammar1();
		}
		else if(RDTempNum1 >= 600 && RDTempNum1 < 800)
		{
			Grammar2();
		}
		else if(RDTempNum1 >= 400 && RDTempNum1 < 600)
		{
			Grammar3();
		}
		else if(RDTempNum1 >= 200 && RDTempNum1 < 400)
		{
			Grammar4();
		}
		else
		{
			Grammar5();
		}
		
		RightComeOut_Refresh();//出场刷新特效
//		OLED_Refresh();
		
	}
}

/**
  * @brief v+adj+n
  * @param  无
  * @retval 无
  */
void Grammar1(void)
{
	uint8_t Row = 0;	//纵坐标y
	uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
	uint16_t RDTempNum2 = 0;	//定义临时的随机数变量1
	RDTempNum1 = RandomCreate() % 1000; 
	RDTempNum2 = RandomCreate() % 1000; 
	Time_ms ++;
	
	//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
	RDNum1 = (uint16_t)RandomCreate() % 250;							//v.
	Time_ms ++;
	RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 210;		//adj.
	Time_ms ++;
	RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 540;		//n.
	Time_ms ++;
	RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 540;		//n.
	Time_ms ++;
	RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms) % 210;		//adj.
	Time_ms ++;
	
	if(RDTempNum2 > 200)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
	}
	
	if(RDTempNum1 >= 200) //加一个名词
	{
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum1].name,16,1);
	
	LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum1].name)/2);	//取上一个打印在屏幕上的字符串的长度除以2再乘上16（除以2是因为一个汉字占2byte）
	
	if(LengthTemp > 128)	//自动换行
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp, Row, Chinese_adj[RDNum2].name,16,1);
	
	LengthTemp +=  16 * (strlen((char *)Chinese_adj[RDNum2].name)/2);		//用strlen函数得出字符串的byte长度
	
	if(LengthTemp > 128)	//自动换行
	{
		LengthTemp -= 128;
		Row += 16;
	}

	OLED_ShowString(LengthTemp,Row,"的",16,1);
	
	LengthTemp += 16;
	
	if(LengthTemp > 128)
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp, Row, Chinese_n[RDNum3].name,16,1);
	
	LengthTemp = 0;	
}


void test(void)
{
	uint8_t i;
	uint8_t Row = 0;	//纵坐标y
	for(i = 0; i <= 1; i++)
	{
		OLED_ShowString(0,Row,Chinese_v[i].name,16,1);
		
		LengthTemp = 16 * (strlen((char *)Chinese_v[i].name)/2);	//取上一个打印在屏幕上的字符串的长度除以2再乘上16（除以2是因为一个汉字占2byte）
		
		OLED_ShowString(LengthTemp, Row, Chinese_adj[i].name,16,1);
		
		LengthTemp +=  16 * (strlen((char *)Chinese_adj[i].name)/2);
		
		if(LengthTemp > 128)
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"的",16,1);
		
		if(LengthTemp > 128)
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		LengthTemp += 16;
		
		OLED_ShowString(LengthTemp, Row, Chinese_n[i].name,16,1);
		
		LengthTemp = 0;	
		Row = 0;	
		OLED_Refresh();		//刷新oled
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		OLED_ShowString(0, 0,"                               ", 16, 1);		//清屏oled，我总感觉库函数里面那个clear函数太呆了
		OLED_Refresh();
	}
}

/**
  * @brief n+和+n//n+是+n
  * @param  无
  * @retval 无
  */
void Grammar2(void)
{
	
		uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
		uint16_t RDTempNum2 = 0; //定义临时的随机数变量2
		RDTempNum1 = RandomCreate() % 1000; //用一个随机数来选择2个不同的语法
		Time_ms ++;
		RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
		Time_ms ++;
		
		if(RDTempNum1 >= 500)	//n+和+n
		{
			uint8_t Row = 0;	//纵坐标y
			
			//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
			RDNum1 = (uint16_t)RandomCreate() % 540;							//n.
			Time_ms ++;
			RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 4;	//And.
			Time_ms ++;
			RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 540;		//n.
			Time_ms ++;
			RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 210;		//adj.
			Time_ms ++;
			RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms) % 210;		//adj.
			Time_ms ++;
			
			if(RDTempNum2 > 600)	//通过这里决定要不要加一个形容词
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			}
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_And[RDNum2].name,16,1);	
			LengthTemp +=  16 * (strlen((char *)Chinese_And[RDNum2].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			if(RDTempNum1 > 600)	//通过这里决定要不要加一个形容词
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
			}
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_n[RDNum3].name,16,1);
			
			LengthTemp = 0;	
		}
		
		else//n+是+n
		{
			uint8_t Row = 0;	//纵坐标y
			
			//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
			RDNum1 = (uint16_t)RandomCreate() % 540;							//n.
			Time_ms ++;
			RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 20;	//OnlyForG3
			Time_ms ++;
			RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 540;		//n.	
			Time_ms ++;
			RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 210;		//adj.
			Time_ms ++;
			RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms) %210;		//adj.
			Time_ms ++;
			
			if(RDTempNum2 >= 400)	//通过这里决定要不要加一个形容词
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
				LengthTemp = 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			}
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_OnlyForG3[RDNum2].name,16,1);	
			LengthTemp +=  16 * (strlen((char *)Chinese_OnlyForG3[RDNum2].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			if(RDTempNum1 > 400)	//通过这里决定要不要加一个形容词
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
			}
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_n[RDNum3].name,16,1);
			
			LengthTemp = 0;	
		}
}

/**
  * @brief 疑问句
  * @param  无
  * @retval 无
  */
void Grammar3(void)
{
	uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
	uint16_t RDTempNum2 = 0; //定义临时的随机数变量2
	RDTempNum1 = RandomCreate() % 1000; //用一个随机数来选择2个不同的语法
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	
	if(RDTempNum1 >= 500)
	{
		uint8_t Row = 0;	//纵坐标y
			
		//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
		RDNum1 = (uint16_t)RandomCreate() % 7;						//Possible.
		Time_ms ++;
		RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 250;		//v.
		Time_ms ++;
		RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 540;		//n.
		Time_ms ++;
		RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 210;		//adj.
		Time_ms ++;
		RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms);	//None
		Time_ms ++;
		
		OLED_ShowString(LengthTemp,Row,Chinese_Possible[RDNum1].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_Possible[RDNum1].name)/2);
		
		OLED_ShowString(LengthTemp,Row,"要",16,1);
		LengthTemp += 16;
		
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum2].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum2].name)/2);
		
		if(RDTempNum2 > 500)	//通过这里决定要不要加一个形容词
		{
			OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp,Row,"的",16,1);
			LengthTemp += 16;
		}
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum3].name)/2);
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"吗",16,1);
		
		LengthTemp = 0;	
	}
	else
	{
		uint8_t Row = 0;	//纵坐标y
			
		//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
		RDNum1 = (uint16_t)RandomCreate() % 540;							//n.
		Time_ms ++;
		RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 210;		//adj.
		Time_ms ++;
		RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 250;		//v.
		Time_ms ++;
		RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 540;		//n.
		Time_ms ++;
		RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms);		//None
		Time_ms ++;
		
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
		
		if(RDTempNum2 >= 400)
		{
			OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum2].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum2].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp,Row,"地",16,1);
			LengthTemp += 16;
		}
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum3].name)/2);
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		if(RDTempNum1 >= 400)
		{
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
			
			if(LengthTemp > 128)	//自动换行//保险一点
			{
				LengthTemp -= 128;
				Row += 16;
			}
		}
		
		OLED_ShowString(LengthTemp,Row,"了吗",16,1);
		
		LengthTemp = 0;	
	}
}

/**
  * @brief 在+n+方位词+v
  * @param  无
  * @retval 无
  */
void Grammar4(void)
{
	uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
	uint16_t RDTempNum2 = 0; //定义临时的随机数变量2
	uint16_t RDTempNum3 = 0; //定义临时的随机数变量3
	uint16_t RDTempNum4 = 0; //定义临时的随机数变量3
	
	uint8_t Row = 0;	//纵坐标y
	
	RDTempNum1 = RandomCreate() % 1000; //用一个随机数来选择2个不同的语法
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum3 = RandomCreateAgain(RDTempNum2 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum4 = RandomCreateAgain(RDTempNum3 + Time_ms) % 1000;
	Time_ms ++;
		
	//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
	RDNum1 = (uint16_t)RandomCreate() % 540;						//n.
	Time_ms ++;
	RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 20;		//Position.
	Time_ms ++;
	RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 250;		//v.
	Time_ms ++;
	RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 540;		//n.
	Time_ms ++;
	RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms) % 210;		//adj.
	Time_ms ++;
	RDNum6 = (uint16_t)RandomCreateAgain(RDNum5 + Time_ms) % 210;		//adj.
	Time_ms ++;
	RDNum7 = (uint16_t)RandomCreateAgain(RDNum6 + Time_ms) % 80;		//vn.
	Time_ms ++;

	if(RDTempNum1 > 700)	//加个名词
	{
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
		
		RDTempNum2 = 0;//把概率都清零，防止超出屏幕
	}
	
	OLED_ShowString(LengthTemp,Row,"在",16,1);
	LengthTemp += 16;
	
	if(RDTempNum2 > 400)	//加个形容词
	{
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
		
	}
	
	if(LengthTemp > 128)	//自动换行//保险一点
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
	LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
	
	if(LengthTemp > 128)	//自动换行//保险一点
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_Position[RDNum2].name,16,1);
	LengthTemp += 16 * (strlen((char *)Chinese_Position[RDNum2].name)/2);
	
	if(RDTempNum3 > 400)	//加个副词
	{
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum6].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum6].name)/2);
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"地",16,1);
		LengthTemp += 16;
		
	}
	
	if(LengthTemp > 128)	//自动换行//保险一点
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	if(RDTempNum4 > 700)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum3].name)/2);
	}
	else
	{
		OLED_ShowString(LengthTemp,Row,Chinese_vn[RDNum7].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_vn[RDNum7].name)/2);
	}
	

	LengthTemp = 0;	
}





/**
  * @brief 被/把字句
  * @param  无
  * @retval 无
  */
void Grammar5(void)
{
	uint16_t RDTempNum1 = 0;	//定义临时的随机数变量1
	uint16_t RDTempNum2 = 0; //定义临时的随机数变量2
	uint16_t RDTempNum3 = 0; //定义临时的随机数变量3
	uint16_t RDTempNum4 = 0; //定义临时的随机数变量4
	uint16_t RDTempNum5 = 0; //定义临时的随机数变量5
	
	uint8_t Row = 0;	//纵坐标y
	
	RDTempNum1 = RandomCreate() % 1000; //用一个随机数来选择2个不同的语法
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum3 = RandomCreateAgain(RDTempNum2 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum4 = RandomCreateAgain(RDTempNum3 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum5 = RandomCreateAgain(RDTempNum4 + Time_ms) % 1000;
	Time_ms ++;
		
	//这里虽然很复杂，疯狂套娃，但是生成随机数效果很好！也是没有办法的办法！
	RDNum1 = (uint16_t)RandomCreate() % 540;						//n.
	Time_ms ++;
	RDNum2 = (uint16_t)RandomCreateAgain(RDNum1 + Time_ms) % 210;		//adj.
	Time_ms ++;
	RDNum3 = (uint16_t)RandomCreateAgain(RDNum2 + Time_ms) % 250;		//v.
	Time_ms ++;
	RDNum4 = (uint16_t)RandomCreateAgain(RDNum3 + Time_ms) % 540;		//n.
	Time_ms ++;
	RDNum5 = (uint16_t)RandomCreateAgain(RDNum4 + Time_ms) % 80;		//vn.
	Time_ms ++;
	RDNum6 = (uint16_t)RandomCreateAgain(RDNum5 + Time_ms) % 210;		//adj.
	Time_ms ++;
	RDNum7 = (uint16_t)RandomCreateAgain(RDNum6 + Time_ms) % 5;		//OnlyForG5.
	Time_ms ++;
	
	if(RDTempNum1 > 500)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_OnlyForG5[RDNum7].name,16,1);
	LengthTemp += 16 * (strlen((char *)Chinese_OnlyForG5[RDNum7].name)/2);
	
	if(RDTempNum2 > 200)
	{
		if(RDTempNum5 > 400)
		{
			OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum6].name,16,1);	//形容词
			LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum6].name)/2);
		}
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
	}
	
	if(LengthTemp > 128)	//自动换行//保险一点
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	if(RDTempNum3 > 400)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum2].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum2].name)/2);	//副词
		
		if(LengthTemp > 128)	//自动换行//保险一点
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"地",16,1);
		LengthTemp += 16;
	}
	
	if(RDTempNum4 > 850)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum3].name)/2);
	}
	else
	{
		OLED_ShowString(LengthTemp,Row,Chinese_vn[RDNum5].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_vn[RDNum5].name)/2);
	}

	LengthTemp = 0;	

}






