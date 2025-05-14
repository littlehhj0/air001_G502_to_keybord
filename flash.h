#ifndef _flash_H_
#define _flash_H_

#include <EEPROM.h>
#include <Arduino.h>



#define eeprom_size 128 //EEPROM大小


#define first_download_add 0 //初次烧录固件后判定初始化设置参数
#define RGB_state_add 10 //RGB状态
#define RGB_last_state_add 20 //RGB上次状态
#define RGB_blink_add 30 //RGB闪烁状态
#define light_add 40 //灯光亮度 
#define task_flag_add 50 //按键1

class eeprom_flash{
    public:

    void data_init();//数据初始化
    void read_all_data();//读取所有数据
    void write_task();
    uint8_t write_flg = 0;
    uint8_t write_t = 11;
};


extern eeprom_flash eeprom;






#endif
