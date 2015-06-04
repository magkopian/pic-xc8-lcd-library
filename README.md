## Description:
This is an LCD Library for 8 bit PIC microcontrollers written for the XC8 compiler.
The library consists of two files, the `lcd.c` and the `lcd.h`. There is also the `example.c` file which contains a simple demo usage of library.

## Hardware Support
The library has been tested with 16x2 and 20x4 LCD displays but is should work with any display up to 4 rows.
As for the supported microcontrollers, currently the library has been tested only with the PIC16F876A, but it should work with most 8 bit PIC microcontrollers.

## Simple Usage Example
```c
LCD lcd = { &PORTC, 2, 3, 4, 5, 6, 7 };
LCD_Init(lcd);

LCD_Clear();
LCD_Set_Cursor(1,0);
LCD_putrs("  HELLO WORLD!  ");
```
