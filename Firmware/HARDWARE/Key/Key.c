#include "Delay.h"
#include "stm32f4xx.h"                  // Device header

/*Only For 1 Key//ֻ������һ������//�����öఴ��*/

uint8_t Key_KeyNumber;//�ڶ�ʱ���еõ��ļ���ֵ�������������е�delayӰ�죩

Key_Tag Key_A0;	//����һ��A0���ſڵİ����ṹ��

/**
  * @brief ���ؼ���ֵ��������������ѭ����
  * @param  ��
  * @retval ����ֵ
  */
uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

/**
  * @brief ����������ʼ��
  * @param  ��
  * @retval ��
  */
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**
  * @brief ���ö�ʱ��ɨ�谴���ķ�ʽ���Ѿ���ʼ�����ȼ����жϣ�
  * @param  ��
  * @retval ��
  */
void TIM2_Key_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;	//50HZ//20ms
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief ������ð����ĵ�ƽ
  * @param  ��
  * @retval ���ؼ���ֵ
  */
uint8_t Key_GetState(void)
{
	uint8_t KeyNumber = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0){KeyNumber = 1;}
	
	return KeyNumber;
}

/**
  * @brief �жϵ���&����&˫��&�������
  * @param  ��
  * @retval ��
  */
void Key_Loop(void)
{
	
	static uint8_t NowState, LastState;	//��������ʱ�̵İ�����ƽ״̬��ǰһʱ�̵İ�����ƽ״̬
	LastState = NowState;//����ǰһʱ��״̬
	NowState = Key_GetState();//�������ڵ�״̬
	
	if(LastState==0 && NowState==1 && Key_A0.LongPressOpen_Flag)	//�������£�������ʱ��ʼ
	{
		Key_A0.Time_1 = 0;//�����ж�ʱ������
	}
	
	if(LastState==1 && NowState==1 && Key_A0.Time_1 <= 1500 && Key_A0.LongPressOpen_Flag)	//����������ѹ������ʱ���ۼӣ�1.5s��
	{
		Key_A0.Time_1 += 20;	//��20����ΪTIM2��ʱ20ms
	}
	
	if(LastState == 1 && Key_A0.Time_1 > 1500 && Key_A0.LongPressOpen_Flag)				//����1.5s
	{
		Key_KeyNumber = LONG_PRESS;//���س�������ֵ2
		Key_A0.Time_1 = 201;//���ŵرܿ�������ͷ�����̰�������
	}
	
	
	
	if(LastState==1 && NowState==0 && Key_A0.Time_1 <= 200)	//�̰�&&˫��
	{
		
		if(Key_A0.DoublePressOpen_Flag == 0)	//˫�����ر�־Ϊ��//˫��û�д�
		{
			Key_KeyNumber = SHORT_PRESS;//���ص�������ֵ1
		}
		
		if(Key_A0.DoublePressOpen_Flag == 1)	//˫����
		{
			if(Key_A0.FirstPress_Flag == 0)		//��һ�ΰ����ж�
			{	
				Key_A0.FirstPress_Flag = 1;
				Key_A0.Time_2 = 0;//˫���ж�ʱ������
			}
			else if(Key_A0.FirstPress_Flag == 1)	//����Ѿ����µ�һ��
			{
				if(Key_A0.Time_2 <= 200)	//���ǰ�����ΰ���ʱ����С��0.3s//����ĳ�0.2s�� ʵ�����ⲻ��
				{
					Key_KeyNumber = DOUBLE_PRESS;//����˫������ֵ3
					Key_A0.FirstPress_Flag = 0;//�����һ�ΰ��±�־λ
				}
			}
		}
	}

	if(Key_A0.FirstPress_Flag)//�����һ���Ѿ�����
	{
		Key_A0.Time_2 += 20;	//˫���ж�ʱ����ʼ�ۼ�//�����20����ΪTIM2��ʱ20ms
		if(Key_A0.Time_2 > 200)//���˫���ж�ʱ������0.3s//���ж�Ϊ����//����ĳ�0.2s��//0.2s����Ǽ�����
		{
			Key_KeyNumber = SHORT_PRESS;//���ص�������ֵ1
			Key_A0.FirstPress_Flag = 0;//�����һ�ΰ��±�־λ
		}
	}
}


/**
  * @brief TIM2�ж�ɨ�谴��
  * @param  ��
  * @retval ��
  */
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		Key_Loop();
	}
}




