/*
 * File:   eeprom_ext.c
 * Author: YH31
 *
 * Created on May 15, 2020, 10:56 AM
 */


#include "eeprom_ext.h"
#include "lcd.h"


char eeprom_wb(int16_t addr, int8_t data) {

    //��һ�����͵�ַ
    char ack = 0;
    i2c_start();
    //���� eeprom���ߵ�ַ��24C04�����ߵ�ַ��1010xxx+W/R;,  w=0
    char ah = (addr & 0x0100) >> 8;
    if (ah) {
        ack = i2c_write(0xA2);
    } else {
        ack = i2c_write(0xA0);
    }
    if (ack) {
        //�õ�ַû���豸
        return 0;
    }
    //����eeprom���ڴ��ַ
    ack = i2c_write(addr & 0xFF); //�����ڴ��ַ
    if (ack) {
        //����ʧ�ܣ��ڴ��ַ����
        return 1;
    }
    ack = i2c_write(data); //��������
    if (ack) {
        //����ʧ��
        return 2;
    }
    i2c_stop(); //����ֹͣ
    return 3;
}

char eeprom_rb(int16_t addr) {
    char result = 0;
    char ah = (addr & 0x0100) >> 8;
    //�����豸
    char ack = 0;
    i2c_start();
    //    ���� eeprom���ߵ�ַ��24C04�����ߵ�ַ��1010xxx+W/R;,  w=0
    if (ah) {
        ack = i2c_write(0xA2);
    } else {
        ack = i2c_write(0xA0);
    }
    if (ack) {
        //�õ�ַû���豸
        return 0;
    }
    ack = i2c_write(addr & 0xFF); //�����ڴ��ַ
    if (ack) {
        //�ڴ��ַ����
        return 1;
    }

    //��ȡ����
    i2c_start();
    //    ���� eeprom���ߵ�ַ��24C04�����ߵ�ַ��1010xxx+W/R;,  w=1
    if (ah) {
        i2c_write(0xA3);
    } else {
        i2c_write(0xA1);
    }
    //��ȡ��Ϣ
    result=i2c_read(1);
    i2c_stop();
    return result;

}