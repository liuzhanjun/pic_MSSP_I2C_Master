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

    //选择主模式
    SSPCONbits.SSPM3 = 1;
    SSPCONbits.SSPM2 = 0;
    SSPCONbits.SSPM1 = 0;
    SSPCONbits.SSPM0 = 0;
    //
  

    //初始化状态寄存器
    SSPSTAT = 0x80; //使用标准100Khz到1Mhz之间
    //   
    //配置时钟频率Fclock=Fosc/(4*(SSPADD+1))  
    //这里我们假设用I2C时钟频率100Khz,单片机时钟频率Fosc=20Mhz
    SSPADD = 0x31;
    //     SSPADD=0x9F;
    //初始化SSPCON2
    SSPCON2 = 0x00;
    //    中断使能
    //    GIE = 0;
    //    PEIE = 1;
    //    SSPIE = 1;
    //清除中断标志
    SSPIF = 0;
    SSPCONbits.SSPEN = 1; //SSP使能，将RC3,RC4作为串口引脚
}

void i2c_start() {
    //使能启动条件 产生 I2C 启动信号 
    //需要判断MSSP是否处于空闲
    //使用SSPSTAT下的RW和SEN,RSEN,PEN,RCEN或 ACKEN进行或运算的结果表示MSSP是否处于活动模式
    while (SSPSTATbits.R_nW | SSPCON2bits.SEN);
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN == 1); //等待启动完毕
   
    SSPIF = 0;
}

char i2c_write(uint8_t data) {
    while (!BF) {
        SSPBUF = data;
    }
    while (SSPIF == 0) {
    }; //等待发送完毕
    //清除中断标记
    char ack = 1;
    ack = SSPCON2bits.ACKDT;
    SSPIF = 0; //软件清零
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
    while (SSPCON2bits.PEN == 1); //等待停止为完成
    SSPIF = 0;
}
