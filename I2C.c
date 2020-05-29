/*
 * File:   I2C.c
 * Author: YH31
 *
 * Created on May 13, 2020, 2:09 PM
 */


#include "I2C.h"

void delay() {
    NOP();
    NOP();
    NOP();
    NOP();
}

void i2c_init() {

    //ѡ����ģʽ
    SSPCONbits.SSPM3 = 1;
    SSPCONbits.SSPM2 = 0;
    SSPCONbits.SSPM1 = 0;
    SSPCONbits.SSPM0 = 0;
    //
  

    //��ʼ��״̬�Ĵ���
    SSPSTAT = 0x80; //ʹ�ñ�׼100Khz��1Mhz֮��
    //   
    //����ʱ��Ƶ��Fclock=Fosc/(4*(SSPADD+1))  
    //�������Ǽ�����I2Cʱ��Ƶ��100Khz,��Ƭ��ʱ��Ƶ��Fosc=20Mhz
    SSPADD = 0x31;
    //     SSPADD=0x9F;
    //��ʼ��SSPCON2
    SSPCON2 = 0x00;
    //    �ж�ʹ��
    //    GIE = 0;
    //    PEIE = 1;
    //    SSPIE = 1;
    //����жϱ�־
    SSPIF = 0;
    SSPCONbits.SSPEN = 1; //SSPʹ�ܣ���RC3,RC4��Ϊ��������
}

void i2c_start() {
    //ʹ���������� ���� I2C �����ź� 
    //��Ҫ�ж�MSSP�Ƿ��ڿ���
    //ʹ��SSPSTAT�µ�RW��SEN,RSEN,PEN,RCEN�� ACKEN���л�����Ľ����ʾMSSP�Ƿ��ڻģʽ
    while (SSPSTATbits.R_nW | SSPCON2bits.SEN);
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN == 1); //�ȴ��������
   
    SSPIF = 0;
}

char i2c_write(uint8_t data) {
    while (!BF) {
        SSPBUF = data;
    }
    while (SSPIF == 0) {
    }; //�ȴ��������
    //����жϱ��
    char ack = 1;
    ack = SSPCON2bits.ACKDT;
    SSPIF = 0; //�������
    return ack;
}

char i2c_read(char ack) {

    char result = 0;
    while (SSPSTATbits.R_nW | SSPCON2bits.RCEN);
    SSPCON2bits.RCEN = 1;
    while (!BF) {
    };
    result = SSPBUF;
    while (SSPIF) {
        SSPIF = 0;
    }
    SSPCON2bits.ACKDT = ack;
    while (SSPIF) {
        SSPIF = 0;
    }

    return result;
}

void i2c_stop() {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN == 1); //�ȴ�ֹͣΪ���
    SSPIF = 0;
}
