/*
 * File: lcd.c
 *
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 *
 * LCD library source file.
 */
 
#define _XTAL_FREQ 8000000

#include <stdbool.h>
#include <xc.h>
#include "lcd.h"

LCD lcd;

void LCD_Out ( char c ) {
    
    if ( c & 1 ){
        *(lcd.PORT) |= 1 << lcd.D4;
    }
    else {
         *(lcd.PORT) &= ~(1 << lcd.D4);
    }

    if ( c & 2 ) {
        *(lcd.PORT) |= 1 << lcd.D5;
    }
    else {
        *(lcd.PORT) &= ~(1 << lcd.D5);
    }

    if ( c & 4 ) {
        *(lcd.PORT) |= 1 << lcd.D6;
    }
    else {
        *(lcd.PORT) &= ~(1 << lcd.D6);
    }

    if ( c & 8 ) {
         *(lcd.PORT) |= 1 << lcd.D7;
    }
    else {
         *(lcd.PORT) &= ~(1 << lcd.D7);
    }

}

void LCD_Write ( unsigned char c ) {

    *(lcd.PORT) &= ~(1 << lcd.RS); // => RS = 0
    LCD_Out(c);

    *(lcd.PORT) |= 1 << lcd.EN;    // => E = 1
    __delay_ms(4);
    *(lcd.PORT) &= ~(1 << lcd.EN); // => E = 0

}

bool LCD_Init ( LCD display ) {

    lcd = display;

    /*
     * TODO:
     * The function should clear only the appropriate bits, not the whole PORT
     *
     * TODO:
     * "#if defined" needs to support more microcontrollers that have PORTD and PORTE
     */
    if ( lcd.PORT == &PORTA ) {
        TRISA = 0x00;
    }
    else if ( lcd.PORT == &PORTB ) {
        TRISB = 0x00;
    }
    else if ( lcd.PORT == &PORTC ) {
        TRISC = 0x00;
    }
    #if defined(_16F877) || defined(_16F877A)
    else if ( lcd.PORT == &PORTD ) {
        TRISD = 0x00;
    }
    else if ( lcd.PORT == &PORTE ) {
        TRISE = 0x00;
    }
    #endif
    else {
        return false;
    }

    // Give some time to the LCD to start function properly
    __delay_ms(20);

    // Send reset signal to the LCD
    LCD_Write(0x03);
    __delay_ms(5);
    LCD_Write(0x03);
    __delay_ms(16);
    LCD_Write(0x03);

    // Specify the data lenght to 4 bits
    LCD_Write(0x02);

    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCD_Cmd(0x28);

    // Set cursor to move from left to right
    LCD_Cmd(0x06);

    LCD_Display(true, false, false); // Turn on display and set cursor off

    LCD_Clear();
    
    return true;
}

void LCD_putc ( char c ) {

   *(lcd.PORT) |= 1 << lcd.RS;   // => RS = 1
    LCD_Out((c & 0xF0) >> 4);    //Data transfer

    *(lcd.PORT) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PORT) &= ~(1 << lcd.EN);

    LCD_Out(c & 0x0F);

    *(lcd.PORT) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PORT) &= ~(1 << lcd.EN);

}

void LCD_puts ( char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
        LCD_putc(a[i]);
    }

}

void LCD_putrs ( const char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
        LCD_putc(a[i]);
    }

}
