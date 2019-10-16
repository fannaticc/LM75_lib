/* 
 * File:   usart.h
 * Author: Raphael
 *
 * Created on 25 de Março de 2017, 12:48
 */

#ifndef USART_H
#define	USART_H

void EUSART_Initialize(void);
unsigned char EUSART_Read(void);
void EUSART_Write(uint8_t txData);

#endif	/* USART_H */

