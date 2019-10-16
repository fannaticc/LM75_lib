/* 
 * File:   usart.h
 * Author: Raphael
 *
 * Created on 25 de Março de 2017, 12:48
 */


#include "usart.h"


void EUSART_Initialize(void)
{
    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN disabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x80;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

    // Baud Rate = 9600; SP1BRGL 25; 
    SP1BRGL = 0x19;

    // Baud Rate = 9600; SP1BRGH 0; 
    SP1BRGH = 0x00;

}


uint8_t EUSART_Read(void)
{

   RC1STAbits.SREN = 1;
    while(!PIR3bits.RCIF)
    {
    }

    
    if(1 == RC1STAbits.OERR)
    {
        // EUSART error - restart

        RC1STAbits.SPEN = 0; 
        RC1STAbits.SPEN = 1; 
    }

    return RC1REG;
}

void EUSART_Write(uint8_t txData)
{
    while(0 == PIR3bits.TXIF)
    {
    }

    TX1REG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART_Read();
}

void putch(char txData)
{
    EUSART_Write(txData);
}