/*
 * File:   main.c
 * Author: YH31
 *16F877A MSSP模块之I2C 主模式（Master mode）
 * Created on May 13, 2020, 2:06 PM
 */
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#include "I2C.h"
#include "lcd.h"
#include "eeprom_ext.h"
void main(void) {
    i2c_init();
    initLcd();
    
    char status=eeprom_wb(0x00,0x19);
    
   
    
    char result=eeprom_rb(0x00);
    showLcd(&result,0);
    while(1);
    return;
}
