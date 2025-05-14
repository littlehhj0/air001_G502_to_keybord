#include "User.h"

eeprom_flash eeprom;

void eeprom_flash::data_init()
{
    // EEPROM初始化数据
    write_flg = 2;
    handle.light = 10;
    handle.RGB_state = RGB_loop_3;
    handle.RGB_last_state = RGB_loop_1;
    handle.RGB_blink = false;
    handle.task_flag = true;
    for (int x = first_download_add; x < eeprom_size; x++)
        EEPROM.write(x, 0);
}

void eeprom_flash::read_all_data()
{

    ec11.int_close();
    if (EEPROM.read(first_download_add))
    {
        data_init();
    }
    else
    {
        EEPROM.get(RGB_state_add, handle.RGB_state);
        EEPROM.get(RGB_last_state_add, handle.RGB_last_state);
        EEPROM.get(RGB_blink_add, handle.RGB_blink);
        EEPROM.get(light_add, handle.light);
        EEPROM.get(task_flag_add, handle.task_flag);
    }
    ec11.int_work();
}


void eeprom_flash::write_task()
{
    if (write_flg == 2)
    {
        write_flg = 0;
        ec11.int_close();
        Serial.println("EE WRITE");

        EEPROM.update(RGB_state_add, handle.RGB_state);
        EEPROM.update(RGB_last_state_add, handle.RGB_last_state);
        EEPROM.update(RGB_blink_add, handle.RGB_blink);
        EEPROM.update(light_add, handle.light);
        EEPROM.update(task_flag_add, handle.task_flag);
        
        Serial.println("END");
        ec11.int_work();
    }
}
