#include "sys.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
  * @brief ����
  * @param  ��
  * @retval ��
  */
void FrontCover(void)
{	
	uint8_t k;	//��ui��Ч����ı���
	OLED_ShowPicture(0,0,128,32,BMP2[0],1);//��è
	for(k = 0; k < 128; k += 25)//���ˢ����è
	{
		OLED_PartialRefresh(0,k+25<128?k+25:128,0,4);
		delay_ms(300);
	}
	OLED_Clear();
	
	OLED_ShowString(0,0,"αʫ��",16,1);
	OLED_ShowString(24,16,"Designed by L",16,1);
	RightComeOut_Refresh();//����ˢ����Ч
}

/**
  * @brief �������ѡ���﷨
  * @param  ��
  * @retval ��
  */
void Grammar_Chioce(void)
{
	uint16_t RDTempNum1 = 0;	//������ʱ�����������1
	RDTempNum1 = RandomCreate() % 1000; //��һ���������ѡ��2����ͬ���﷨
	Time_ms ++;
	if(KeyNum == SHORT_PRESS)//����ˢ�´���
	{
		Time_msForAnim = 0;	//���������ʱ
		
		RightToLeft_Clear();//����//������Ч
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
		
		RightComeOut_Refresh();//����ˢ����Ч
//		OLED_Refresh();
		
	}
}

/**
  * @brief v+adj+n
  * @param  ��
  * @retval ��
  */
void Grammar1(void)
{
	uint8_t Row = 0;	//������y
	uint16_t RDTempNum1 = 0;	//������ʱ�����������1
	uint16_t RDTempNum2 = 0;	//������ʱ�����������1
	RDTempNum1 = RandomCreate() % 1000; 
	RDTempNum2 = RandomCreate() % 1000; 
	Time_ms ++;
	
	//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
	
	if(RDTempNum1 >= 200) //��һ������
	{
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum1].name,16,1);
	
	LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum1].name)/2);	//ȡ��һ����ӡ����Ļ�ϵ��ַ����ĳ��ȳ���2�ٳ���16������2����Ϊһ������ռ2byte��
	
	if(LengthTemp > 128)	//�Զ�����
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp, Row, Chinese_adj[RDNum2].name,16,1);
	
	LengthTemp +=  16 * (strlen((char *)Chinese_adj[RDNum2].name)/2);		//��strlen�����ó��ַ�����byte����
	
	if(LengthTemp > 128)	//�Զ�����
	{
		LengthTemp -= 128;
		Row += 16;
	}

	OLED_ShowString(LengthTemp,Row,"��",16,1);
	
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
	uint8_t Row = 0;	//������y
	for(i = 0; i <= 1; i++)
	{
		OLED_ShowString(0,Row,Chinese_v[i].name,16,1);
		
		LengthTemp = 16 * (strlen((char *)Chinese_v[i].name)/2);	//ȡ��һ����ӡ����Ļ�ϵ��ַ����ĳ��ȳ���2�ٳ���16������2����Ϊһ������ռ2byte��
		
		OLED_ShowString(LengthTemp, Row, Chinese_adj[i].name,16,1);
		
		LengthTemp +=  16 * (strlen((char *)Chinese_adj[i].name)/2);
		
		if(LengthTemp > 128)
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"��",16,1);
		
		if(LengthTemp > 128)
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		LengthTemp += 16;
		
		OLED_ShowString(LengthTemp, Row, Chinese_n[i].name,16,1);
		
		LengthTemp = 0;	
		Row = 0;	
		OLED_Refresh();		//ˢ��oled
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		OLED_ShowString(0, 0,"                               ", 16, 1);		//����oled�����ܸо��⺯�������Ǹ�clear����̫����
		OLED_Refresh();
	}
}

/**
  * @brief n+��+n//n+��+n
  * @param  ��
  * @retval ��
  */
void Grammar2(void)
{
	
		uint16_t RDTempNum1 = 0;	//������ʱ�����������1
		uint16_t RDTempNum2 = 0; //������ʱ�����������2
		RDTempNum1 = RandomCreate() % 1000; //��һ���������ѡ��2����ͬ���﷨
		Time_ms ++;
		RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
		Time_ms ++;
		
		if(RDTempNum1 >= 500)	//n+��+n
		{
			uint8_t Row = 0;	//������y
			
			//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
			
			if(RDTempNum2 > 600)	//ͨ���������Ҫ��Ҫ��һ�����ݴ�
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			}
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_And[RDNum2].name,16,1);	
			LengthTemp +=  16 * (strlen((char *)Chinese_And[RDNum2].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			if(RDTempNum1 > 600)	//ͨ���������Ҫ��Ҫ��һ�����ݴ�
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
			}
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_n[RDNum3].name,16,1);
			
			LengthTemp = 0;	
		}
		
		else//n+��+n
		{
			uint8_t Row = 0;	//������y
			
			//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
			
			if(RDTempNum2 >= 400)	//ͨ���������Ҫ��Ҫ��һ�����ݴ�
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
				LengthTemp = 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			}
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_OnlyForG3[RDNum2].name,16,1);	
			LengthTemp +=  16 * (strlen((char *)Chinese_OnlyForG3[RDNum2].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			if(RDTempNum1 > 400)	//ͨ���������Ҫ��Ҫ��һ�����ݴ�
			{
				OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
				LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
			}
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp, Row, Chinese_n[RDNum3].name,16,1);
			
			LengthTemp = 0;	
		}
}

/**
  * @brief ���ʾ�
  * @param  ��
  * @retval ��
  */
void Grammar3(void)
{
	uint16_t RDTempNum1 = 0;	//������ʱ�����������1
	uint16_t RDTempNum2 = 0; //������ʱ�����������2
	RDTempNum1 = RandomCreate() % 1000; //��һ���������ѡ��2����ͬ���﷨
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	
	if(RDTempNum1 >= 500)
	{
		uint8_t Row = 0;	//������y
			
		//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
		
		OLED_ShowString(LengthTemp,Row,"Ҫ",16,1);
		LengthTemp += 16;
		
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum2].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum2].name)/2);
		
		if(RDTempNum2 > 500)	//ͨ���������Ҫ��Ҫ��һ�����ݴ�
		{
			OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum4].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum4].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp,Row,"��",16,1);
			LengthTemp += 16;
		}
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum3].name)/2);
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"��",16,1);
		
		LengthTemp = 0;	
	}
	else
	{
		uint8_t Row = 0;	//������y
			
		//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
			
			OLED_ShowString(LengthTemp,Row,"��",16,1);
			LengthTemp += 16;
		}
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_v[RDNum3].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_v[RDNum3].name)/2);
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		if(RDTempNum1 >= 400)
		{
			OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
			LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
			
			if(LengthTemp > 128)	//�Զ�����//����һ��
			{
				LengthTemp -= 128;
				Row += 16;
			}
		}
		
		OLED_ShowString(LengthTemp,Row,"����",16,1);
		
		LengthTemp = 0;	
	}
}

/**
  * @brief ��+n+��λ��+v
  * @param  ��
  * @retval ��
  */
void Grammar4(void)
{
	uint16_t RDTempNum1 = 0;	//������ʱ�����������1
	uint16_t RDTempNum2 = 0; //������ʱ�����������2
	uint16_t RDTempNum3 = 0; //������ʱ�����������3
	uint16_t RDTempNum4 = 0; //������ʱ�����������3
	
	uint8_t Row = 0;	//������y
	
	RDTempNum1 = RandomCreate() % 1000; //��һ���������ѡ��2����ͬ���﷨
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum3 = RandomCreateAgain(RDTempNum2 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum4 = RandomCreateAgain(RDTempNum3 + Time_ms) % 1000;
	Time_ms ++;
		
	//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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

	if(RDTempNum1 > 700)	//�Ӹ�����
	{
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum4].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum4].name)/2);
		
		RDTempNum2 = 0;//�Ѹ��ʶ����㣬��ֹ������Ļ
	}
	
	OLED_ShowString(LengthTemp,Row,"��",16,1);
	LengthTemp += 16;
	
	if(RDTempNum2 > 400)	//�Ӹ����ݴ�
	{
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum5].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum5].name)/2);
		
	}
	
	if(LengthTemp > 128)	//�Զ�����//����һ��
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
	LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
	
	if(LengthTemp > 128)	//�Զ�����//����һ��
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	OLED_ShowString(LengthTemp,Row,Chinese_Position[RDNum2].name,16,1);
	LengthTemp += 16 * (strlen((char *)Chinese_Position[RDNum2].name)/2);
	
	if(RDTempNum3 > 400)	//�Ӹ�����
	{
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum6].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum6].name)/2);
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"��",16,1);
		LengthTemp += 16;
		
	}
	
	if(LengthTemp > 128)	//�Զ�����//����һ��
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
  * @brief ��/���־�
  * @param  ��
  * @retval ��
  */
void Grammar5(void)
{
	uint16_t RDTempNum1 = 0;	//������ʱ�����������1
	uint16_t RDTempNum2 = 0; //������ʱ�����������2
	uint16_t RDTempNum3 = 0; //������ʱ�����������3
	uint16_t RDTempNum4 = 0; //������ʱ�����������4
	uint16_t RDTempNum5 = 0; //������ʱ�����������5
	
	uint8_t Row = 0;	//������y
	
	RDTempNum1 = RandomCreate() % 1000; //��һ���������ѡ��2����ͬ���﷨
	Time_ms ++;
	RDTempNum2 = RandomCreateAgain(RDTempNum1 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum3 = RandomCreateAgain(RDTempNum2 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum4 = RandomCreateAgain(RDTempNum3 + Time_ms) % 1000;
	Time_ms ++;
	RDTempNum5 = RandomCreateAgain(RDTempNum4 + Time_ms) % 1000;
	Time_ms ++;
		
	//������Ȼ�ܸ��ӣ�������ޣ��������������Ч���ܺã�Ҳ��û�а취�İ취��
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
			OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum6].name,16,1);	//���ݴ�
			LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum6].name)/2);
		}
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,Chinese_n[RDNum1].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_n[RDNum1].name)/2);
	}
	
	if(LengthTemp > 128)	//�Զ�����//����һ��
	{
		LengthTemp -= 128;
		Row += 16;
	}
	
	if(RDTempNum3 > 400)
	{
		OLED_ShowString(LengthTemp,Row,Chinese_adj[RDNum2].name,16,1);
		LengthTemp += 16 * (strlen((char *)Chinese_adj[RDNum2].name)/2);	//����
		
		if(LengthTemp > 128)	//�Զ�����//����һ��
		{
			LengthTemp -= 128;
			Row += 16;
		}
		
		OLED_ShowString(LengthTemp,Row,"��",16,1);
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






