#ifndef __GUI_H__
#define __GUI_H__

uint8_t ui_run(short *a, short *a_trg, u8 step, u8 slow_cnt); //ui ����Ч��ʵ��

void menu_ui_show(short offset_y); //�˵�ui��ʾ

void setting_ui_show(short offset_y); //����ui��ʾ

void poet_ui_show(short offset_y);

void menu_proc(void); //�˵�������

void pic_proc(void);//����ui��proc��������࣬Ҫע��ui_selectΪ���پͻ������ĸ�proc

void setting_proc(void);

void ui_proc(void);

uint8_t ui_disapper(void);

uint8_t ui_come(void);

void aboutus_ui_show(short offset_y);
void aboutus_proc(void);

void more_ui_show(short offset_y);
void more_proc(void);
#endif





