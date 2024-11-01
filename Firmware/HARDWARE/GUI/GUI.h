#ifndef __GUI_H__
#define __GUI_H__

uint8_t ui_run(short *a, short *a_trg, u8 step, u8 slow_cnt); //ui 滑动效果实现

void menu_ui_show(short offset_y); //菜单ui显示

void setting_ui_show(short offset_y); //设置ui显示

void poet_ui_show(short offset_y);

void menu_proc(void); //菜单处理函数

void pic_proc(void);//几个ui的proc函数都差不多，要注意ui_select为多少就会运行哪个proc

void setting_proc(void);

void ui_proc(void);

uint8_t ui_disapper(void);

uint8_t ui_come(void);

void aboutus_ui_show(short offset_y);
void aboutus_proc(void);

void more_ui_show(short offset_y);
void more_proc(void);
#endif





