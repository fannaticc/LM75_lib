/* 
 * File:   my_delays.c
 * Author: Raphael
 * 
 */

#include <xc.h>
#include "config.h"
#include "my_delays.h"

void Delay_ms(unsigned int count)
{
    unsigned int i;
    
    for(i = 0; i < count; i ++)
    {
        __delay_ms(1);
    }
}

void Delay_us(unsigned int count)
{
    unsigned int i;
    
    for(i = 0; i < count; i ++)
    {
        __delay_us(1);
    }
}