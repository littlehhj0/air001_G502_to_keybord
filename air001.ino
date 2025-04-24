#include "User.h"
int i = 0;

// 编写一个函数，调用时使用定时器实现触发某个引脚的一次翻转信号输出，用于模拟按键
#define key_pin1 PB_3
#define key_pin2 PB_1
#define key_pin3 PB_4
#define LEDS_COUNT  8

int light = 10;   //定义灯光亮度

AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);




void setup() {
	Serial.begin(115200);
	Serial.println("begin");
	pinMode(key_pin1, OUTPUT);
	pinMode(key_pin2, OUTPUT);
	// pinMode(key_pin3, OUTPUT);
	digitalWrite(key_pin1, HIGH);
	digitalWrite(key_pin2, LOW);

	HardwareTimer* MyTim1 = new HardwareTimer(TIM1);
	MyTim1->setMode(3, TIMER_DISABLED);
	MyTim1->setOverflow(1000, HERTZ_FORMAT);   //1ms
	MyTim1->setCaptureCompare(3, 50, PERCENT_COMPARE_FORMAT);
	MyTim1->attachInterrupt(Update_IT_callback);
	MyTim1->resume();
	ec11.begin(PA_6, PB_0, PB_2, ui_key_callb);
	ec11.speed_up(true);
	ec11.speed_up_max(20);
	strip.begin();
	strip.setBrightness(10);
}

void loop() {
	delay(1000);
}
