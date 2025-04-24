#pragma once
#ifndef _handle_H_
#define _handle_H_

#include <Arduino.h>
#include "User.h"

typedef enum
{
	RGB_off,     //RGB关闭
	RGB_blink,   //RGB闪烁
	RGB_loop_1,  //RGB循环1
	RGB_loop_2,  //RGB循环2
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
	//RGB闪烁
	void RGB_blink1();
	void RGB_loop1();    //第一种循环效果
	int loop1_time = 10;
	int loop2_time = 200;
	void RGB_loop2();   //第二种循环效果
	RGB_State RGB_state = RGB_off; //RGB状态
	RGB_State RGB_last_state = RGB_off; //RGB上次状态
};

extern Handle handle;



ec11_task_result_type ectype;
int key_value = 0;
void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value);  //按键事件中断处理

#endif
