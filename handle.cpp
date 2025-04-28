#include "User.h"
#include "handle.h"

ec11_task_result_type ectype;
int key_value = 0;


Handle handle;
bool task_flag = false;  //任务标志位 0-鼠标 1-RGB

extern AIR001_WS2812 strip;

void Handle::key_handle(ec11_task_result_type ec_type, int16_t ec_value)
{
	if (ec_type == ec11_task_is_key)
	{
		Serial.println("key");

		if (ec_value == sw_long)
		{
			task_flag = !task_flag;
			if (!RGB_blink)
			{
				RGB_last_state = RGB_state;
				RGB_blink = true;
			}
		}
		return;
	}
	else {
		//Serial.println("encode");
	}

}

void Handle::RGB_handle(ec11_task_result_type ec_type, int16_t ec_value)
{
	if (ec_type == ec11_task_is_key)
	{
		//Serial.println("key");
		if (ec_value == sw_long)
		{

		}
		switch (ec_value)
		{
		case sw_long:
		{
			task_flag = !task_flag;
			if (!RGB_blink)
			{
				RGB_last_state = RGB_state;
				RGB_blink = true;
			}
			//Serial.println("RGB_blink");
			break;
		}
		case sw_click:
		{
			RGB_state_change();
		}
		default:
			break;
		}
	}
	else {
		light = light + ec_value * 10;
		if (light > 205)
			light = 205;
		else if (light < 5)
			light = 10;
		strip.setBrightness(light);
		//Serial.print(light);
		//Serial.println("encode");
	}
}

void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value)  //按键事件中断处理
{
	//
	if (task_flag)
	{
		handle.key_handle(ec_type, ec_value);
	}
	else
	{
		handle.RGB_handle(ec_type, ec_value);
	}

	key_value = ec_value;
	ectype = ec_type;
}
void Handle::key_loop(int count)
{
	if (count % 25 == 0)
	{
		if (ectype == ec11_task_is_encode)
		{
			if (key_value > 0)
				digitalWrite(key_pin1, LOW);
			else if (key_value < 0)
				digitalWrite(key_pin2, LOW);
			//else
			//{
			//	digitalWrite(key_pin1, HIGH);
			//	digitalWrite(key_pin2, HIGH);
			//}

		}
		else if (ectype == ec11_task_is_key)
		{
			digitalWrite(key_pin3, LOW);
		}
		else
		{
			digitalWrite(key_pin1, HIGH);
			digitalWrite(key_pin2, HIGH);
			digitalWrite(key_pin3, HIGH);

		}
		key_value = 0;
		ectype = ec11_task_is_none;
	}
}

void Handle::RGB_loop(int count)
{
	if (RGB_state == RGB_off)
	{

		return;
	}
	if (RGB_blink)
	{
		if (count % 40 == 0)
			RGB_blink1();
		return;
	}
	switch (RGB_state)
	{
	case RGB_loop_1:
	{
		if (count % 2 == 0)
		{
			RGB_loop1();
		}
		break;
	}
	case RGB_loop_2:
	{
		if (count % 200 == 0)
		{
			RGB_loop2();
		}
		break;
	}
	case RGB_loop_3:
	{
		if (count % 30 == 0)
		{
			RGB_loop3();
		}
		break;
	}
	default:
		break;
	}

}

void Update_IT_callback()  //定时器中断处理函数  1ms
{
	static int count = 0;
	if (task_flag)
	{
		handle.key_loop(count);
	}

	handle.RGB_loop(count);

	if (handle.get_rgb_state() != RGB_off)
		strip.show();  //刷新灯带
	count++;
	count %= 1000;
	//if (count % 100 == 0)
	//{
	//	Serial.println(count);
	//}
}



//RGB循环
void  Handle::RGB_loop1()
{
	static int j = 0;
	//for (int j = 0; j < 255; j += 2) {
	for (int i = 0; i < LEDS_COUNT; i++) {
		strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
	}
	//}
	j += 2;
	j %= 255;
}

void Handle::RGB_loop2()
{
	static int count = 0;
	if (count % 3 == 0)
		strip.setAllLedsColorData(255, 0, 0);
	else if (count % 3 == 1)
		strip.setAllLedsColorData(0, 255, 0);
	else
		strip.setAllLedsColorData(0, 0, 255);
	count++;
	count %= 3;
}
void Handle::RGB_loop3()
{
	static int j = 0;
	//for (int j = 0; j < 255; j += 2) {
	//for (int i = 0; i < LEDS_COUNT; i++) {
	strip.setAllLedsColorData(strip.Wheel((j * 256 / LEDS_COUNT + j) & 255));

	j += 1;
	j %= 255;
}



void Handle::RGB_blink1()
{
	//使RGB灯闪烁
	static int blink_count = 0;
	if (blink_count % 2 == 0)
		strip.setAllLedsColor(0, 0, 0);
	else
		strip.setAllLedsColor(255, 255, 255);
	blink_count++;
	if (blink_count == 4)
	{
		RGB_blink = false;
		blink_count = 0;
	}
}

RGB_State Handle::get_rgb_state()
{
	return RGB_state;
}


void Handle::RGB_state_change()
{
	if (RGB_state == RGB_loop_1)
	{
		RGB_state = RGB_loop_2;
	}
	else if (RGB_state == RGB_loop_2)
	{
		RGB_state = RGB_loop_3;
	}
	else if (RGB_state == RGB_loop_3)
	{
		RGB_state = RGB_off;
		strip.setAllLedsColor(0, 0, 0); //关闭灯带
	}
	else
	{
		RGB_state = RGB_loop_1;
	}
}