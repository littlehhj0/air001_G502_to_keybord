#include "User.h"


int i = 0;
extern Handle handle;
extern void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value);
// 编写一个函数，调用时使用定时器实现触发某个引脚的一次翻转信号输出，用于模拟按键
extern void Update_IT_callback();
AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);


void setup() {
	Serial.begin(115200);
	Serial.println("begin");
	pinMode(key_pin1, OUTPUT);
	pinMode(key_pin2, OUTPUT);
	pinMode(key_pin3, OUTPUT);
	digitalWrite(key_pin1, HIGH);
	digitalWrite(key_pin2, HIGH);
	digitalWrite(key_pin3, HIGH);
	eeprom.read_all_data();
	ec11.begin(PB_1, PA_6, PB_3, ui_key_callb);
	ec11.speed_up(true);
	ec11.speed_up_max(10);
	ec11.speed_up_feel(75);
	HardwareTimer* MyTim1 = new HardwareTimer(TIM16);
	MyTim1->setMode(2, TIMER_DISABLED);
	MyTim1->setOverflow(5000, MICROSEC_FORMAT);   //1ms
	MyTim1->setCaptureCompare(2, 100);
	MyTim1->attachInterrupt(Update_IT_callback);
	MyTim1->resume();

	strip.begin();
	strip.setBrightness(handle.light);
}

void loop() {
	//Serial.println("count");
	delay(10);
	eeprom.write_task();


}
