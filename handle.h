#pragma once
#ifndef _handle_H_
#define _handle_H_

#include <Arduino.h>
#include "User.h"

typedef enum
{
	RGB_off,     //RGB�ر�
	RGB_blink,   //RGB��˸
	RGB_loop_1,  //RGBѭ��1
	RGB_loop_2,  //RGBѭ��2
}RGB_State;



class Handle
{
public:
	void key_handle(ec11_task_result_type ec_type, int16_t ec_value);
	void RGB_handle(ec11_task_result_type ec_type, int16_t ec_value);
	void key_loop(int count);
	void RGB_loop(int count);
	RGB_State get_rgb_state();
private:
	//RGB��˸
	void RGB_blink1();
	void RGB_loop1();    //��һ��ѭ��Ч��
	int loop1_time = 10;
	int loop2_time = 200;
	void RGB_loop2();   //�ڶ���ѭ��Ч��
	RGB_State RGB_state = RGB_off; //RGB״̬
	RGB_State RGB_last_state = RGB_off; //RGB�ϴ�״̬
};

extern Handle handle;



ec11_task_result_type ectype;
int key_value = 0;
void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value);  //�����¼��жϴ���

#endif
