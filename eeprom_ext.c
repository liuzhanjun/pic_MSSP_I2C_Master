/*
 * File:   eeprom_ext.c
 * Author: YH31
 *
 * Created on May 15, 2020, 10:56 AM
 */


#include "eeprom_ext.h"
#include "lcd.h"


char eeprom_wb(int16_t addr, int8_t data) {

    //第一步发送地址
    char ack = 0;
    i2c_start();
    //发送 eeprom总线地址，24C04的总线地址是1010xxx+W/R;,  w=0
    char ah = (addr & 0x0100) >> 8;
    if (ah) {
        ack = i2c_write(0xA2);
    } else {
        ack = i2c_write(0xA0);
    }
    if (ack) {
        //该地址没有设备
        return 0;
    }
    //发送eeprom的内存地址
    ack = i2c_write(addr & 0xFF); //发送内存地址
    if (ack) {
        //发送失败，内存地址错误
        return 1;
    }
    ack = i2c_write(data); //发送数据
    if (ack) {
        //发送失败
        return 2;
    }
    i2c_stop(); //发送停止
    return 3;
}

char eeprom_rb(int16_t addr) {
    char result = 0;
    char ah = (addr & 0x0100) >> 8;
    //连接设备
    char ack = 0;
    i2c_start();
    //    发送 eeprom总线地址，24C04的总线地址是1010xxx+W/R;,  w=0
    if (ah) {
        ack = i2c_write(0xA2);
    } else {
        ack = i2c_write(0xA0);
    }
    if (ack) {
        //该地址没有设备
        return 0;
    }
    ack = i2c_write(addr & 0xFF); //发送内存地址
    if (ack) {
        //内存地址错误
        return 1;
    }

    //读取数据
    i2c_start();
    //    发送 eeprom总线地址，24C04的总线地址是1010xxx+W/R;,  w=1
    if (ah) {
        i2c_write(0xA3);
    } else {
        i2c_write(0xA1);
    }
    //读取信息
    result=i2c_read(1);
    i2c_stop();
    return result;

}