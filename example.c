/* 
 * File: example.c
 *
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 *
 * LCD library example code.
 */

// You can change the _XTAL_FREQ if you want, but don't forget to change it in the lcd.c too
#define _XTAL_FREQ 8000000

// In this example the configuration bits are set specifically for the PIC16F876A, if you use a different microcontroller you may have to update them
// Tip: MplabX has a tool to easily auto generate the pragma directives (Main Menu, Window -> PIC Memory Views -> Configuration Bits)
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF    // Flash Program Memory Code Protection bit (Code protection off)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>

#include "lcd.h"

int main ( void ) {

    LCD lcd = { &PORTC, 2, 3, 4, 5, 6, 7 }; // PORT, RS, EN, D4, D5, D6, D7

    LCD_Init(lcd);

    for ( ;; ) {

        LCD_Clear();
        LCD_Set_Cursor(1,0);
        LCD_putrs("  HELLO WORLD!  ");

		LCD_Set_Cursor(1,0);
		for ( char c = 'A'; c < 'Q'; ++c ) { // Print characters A-P
			 LCD_putc(c);
			 for ( unsigned char i = 0; i < 30; ++i ) { // 300ms Delay
			 	__delay_ms(10);
			 }
		}
		
		for ( unsigned char i = 0; i < 100; ++i ) { // 1s Delay
		 	__delay_ms(10);
		 }

	}

    return (EXIT_SUCCESS);
}

