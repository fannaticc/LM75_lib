/*
 * File:   main.c
 * Author: Raphael
 */
#include <xc.h>
#include <pic18f2523.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "my_delays.h"
#include "hd44780.h"
#include "my_i2c.h"
#include "lm75.h"
//#include "usart.h"

//==============================================================================
//Control Buttons.
//==============================================================================
#define BUTTON1 PORTAbits.RA0  //Select
#define BUTTON2 PORTAbits.RA1  //Add data
#define BUTTON3 PORTAbits.RA2  //AM-PM
#define BUTTON4 PORTAbits.RA3  //12-24 format
#define BUTTON5 PORTAbits.RA4  //Dec data
//==============================================================================

void main(void)
{
    unsigned char temp[10];
    
    ADCON1 = 0b00001111; // Set all pins in digital mode.
    CMCON = 0b00000111; // Disable all comparators.
    
    PORTA = 0b11111111;
    PORTB = 0;
    PORTC = 0; //Clear all PORTS.
    TRISA = 0b00111111; // Set RA0, RA1, RA2, RA3 and RA4 as inputs.
    
    CMCON = 0b00000111;
    
    I2C_Close(); // Close the  I2C Bus.
    //I2C_Init(49); // I2C 100kHz, 20MHz-CRYSTAL.
    I2C_Init(9); // I2C 100kHz, 4MHz-CRYSTAL.
    
    Lcd_Init(); // Start LCD.
    Lcd_Command(LCD_CLEAR);
    Lcd_Command(LCD_CURSOR_OFF);
    
    Lcd_Text(1, 1, "Sensor LM75");
    Lcd_Text(2, 1, "Temp=");
    while(1)
    {
        sprintf(temp, "%3.1f", LM75_Read_Temp());
        Lcd_Text(2, 6, temp);
        Lcd_CharCP(178); // Depends on your display character set.
        Lcd_CharCP('C');
        Delay_ms(100);
    }
}