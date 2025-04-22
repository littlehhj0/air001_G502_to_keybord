#include "User.h"
int i = 0;
int flag = 0;
int key_value = 0;
// 编写一个函数，调用时使用定时器实现触发某个引脚的一次翻转信号输出，用于模拟按键
#define key_pin1 PB_3
#define key_pin2 PB_1
// #define key_pin3 PA_4

#define LEDS_COUNT  8

// AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);
ec11_task_result_type ectype;
void Update_IT_callback()  //定时器中断处理函数
{
    if (ectype == ec11_task_is_encode) {  //编码器事件
        if(key_value>0)
			    digitalWrite(key_pin1, LOW);
		    else if(key_value<0)
			    digitalWrite(key_pin2, HIGH);
      key_value=0;
      ectype=ec11_task_is_none;
    }
    else
    {
		digitalWrite(key_pin1, HIGH);
		digitalWrite(key_pin2, LOW);
    }
}

void ui_key_callb(ec11_task_result_type ec_type, int16_t ec_value)  //按键事件中断处理
{
	// if (ec_type == ec11_task_is_key) {    //按键事件
  //   flag = 1;
  //   switch (ec_value) {
  //     case sw_long:
  //       break;
  //     case sw_double:
  //       break;
  //     default:
  //       break;
  //   }
	// }
	// else {    //编码器事件
  //   flag = 2;
  // }
  key_value = ec_value;
  ectype=ec_type;
}

void setup() {
  // HardwareTimer *MyTim = new HardwareTimer(TIM3);  // TIM3 is MCU hardware peripheral instance, its definition is provided in CMSIS
  Serial.begin(115200);
  Serial.println("begin");
  // MyTim->setPWM(3, PB_0, 1, 50); // 5 Hertz, 10% dutycycle
  // MyTim->resume();


  // MyTim->setMode(3, TIMER_DISABLED);
  // MyTim->setOverflow(1000, HERTZ_FORMAT);   //1Hz
  // MyTim->setCaptureCompare(3, 50, PERCENT_COMPARE_FORMAT);
  // MyTim->attachInterrupt(Update_IT_callback);
  // MyTim->resume();

  pinMode(key_pin1, OUTPUT);
  pinMode(key_pin2, OUTPUT);
  // pinMode(key_pin3, OUTPUT);
  digitalWrite(key_pin1, HIGH);
  digitalWrite(key_pin2, LOW);
  // digitalWrite(key_pin3, LOW);

  //pinMode(PF_0, INPUT_PULLUP);

 HardwareTimer* MyTim1 = new HardwareTimer(TIM1);
 MyTim1->setMode(3, TIMER_DISABLED);
 MyTim1->setOverflow(40, HERTZ_FORMAT);   //25Hz
 MyTim1->setCaptureCompare(3, 50, PERCENT_COMPARE_FORMAT);
 MyTim1->attachInterrupt(Update_IT_callback);
 MyTim1->resume();
  ec11.begin(PA_6, PB_0, PB_2, ui_key_callb);
  ec11.speed_up(true);
  ec11.speed_up_max(20);
  // strip.begin();
  // strip.setBrightness(20);  
}

void loop() {
  // Serial.println(i);
  // delay(1000);
  // i=i+2;
  // if (flag) {
  //   if (flag == 1)
  //     Serial.print("key:");

  //   else Serial.print("encode:");
  //   Serial.println(key_value);
  //   key_value = 0;
  //   flag = 0;
  // }
  // for (int j = 0; j < 255; j += 2) {
  //   for (int i = 0; i < LEDS_COUNT; i++) {
  //     strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
  //   }
  //   strip.show();
    delay(10);
  // }  
}
