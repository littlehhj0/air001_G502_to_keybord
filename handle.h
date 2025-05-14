// #pragma once
#ifndef _handle_H_
#define _handle_H_

#include <Arduino.h>
#include "User.h"

#define key_pin1 PB_2
#define key_pin2 PB_0
#define key_pin3 PA_4

#define LEDS_COUNT  8

//int light = 10;   //定义灯光亮度

typedef enum
{
	RGB_off,     //RGB关闭
	RGB_loop_1,  //RGB循环1
	RGB_loop_2,  //RGB循环2
	RGB_loop_3,  //RGB循环3
}RGB_State;


class Handle
{
public:
	int light = 10;   //定义灯光亮度
	void key_handle(ec11_task_result_type ec_type, int16_t ec_value);
	void RGB_handle(ec11_task_result_type ec_type, int16_t ec_value);
	void key_loop(int count);
	void RGB_loop(int count);
	RGB_State get_rgb_state();
	//RGB闪烁
	void RGB_blink1();
	bool RGB_blink = false; //RGB闪烁状态
	RGB_State RGB_state = RGB_loop_3; //RGB状态
	RGB_State RGB_last_state = RGB_loop_1; //RGB上次状态
	bool task_flag = true; // 任务标志位 0-鼠标 1-RGB
private:
	void RGB_loop1();    //第一种循环效果
	//int loop1_time = 2;
	//int loop2_time = 200;
	void RGB_loop2();   //第二种循环效果
	void RGB_loop3();   //第三种循环效果

	void RGB_state_change(); //RGB状态改变
};

extern Handle handle;




void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value);  //按键事件中断处理

#endif
