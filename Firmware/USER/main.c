#include "sys.h"

unsigned char LengthTemp = 0;	//�ַ�ռ���س��ȣ���Ҫ����
uint8_t KeyNum;			//���صļ���ֵ������������ѭ����ã�
uint16_t RDNum1 = 0, RDNum2 = 0, RDNum3 = 0,
RDNum4 = 0, RDNum5 = 0, RDNum6 = 0,
RDNum7 = 0;	//�����

int16_t FPS_Count;//֡�ʱ���
char FPS[10] = "FPS";

uint8_t OLED_BUFF[128][4];
u8g2_t u8g2;	//��ʼ��u8g2�ṹ��

int main(void)
{ 
	
	delay_init();
 	OLED_Init();				//��ʼ��OLED 
	
	Key_Init();
	TIM2_Key_Init();
	TIM4_Random_Init(8400 - 1, 10 - 1);
	
	Key_A0.LongPressOpen_Flag = 1;	//�������ر�־λ����
	
	Key_A0.DoublePressOpen_Flag = 0;	//˫�����ر�־λ�ر�
	
	
	u8g2Init(&u8g2); //u8g2ͼ�ο��ʼ��
	u8g2_SetFont(&u8g2,u8g2_font_profont15_mr);//ѡ���ֿ�

//	FrontCover();//����or��������
	
	while(1) 
	{	
		
		KeyNum = Key_GetNum();
		ui_proc();
	
	
	}
	
}



