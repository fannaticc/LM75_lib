/* 
 * File:   lm75.h
 * Author: Raphael
 *
 * Created on 25 de Março de 2017, 02:24
 */

#ifndef LM75_H
#define	LM75_H

#define LM75_ADR        0b10010000 // all a0 to a2 clear.
//#define LM75_ADR        0b10011110 // all a0 to a2 set.

#define TEMPERATURE     0x00 // Temperature adress
#define CONFIGURATION   0x01 // Configuration adress
#define THYST           0x02 // Hysteresis adress
#define TOS             0x03 // OS adress

#define CONFIG_SHUTDOWN b0
#define CONFIG_COMP/INT b1
#define CONFIG_OS_POL   b2
#define CONFIG_FAULTb3  b3
#define CONFIG_FAULTb4  b4

#define N_FAULT1        0b00000000
#define N_FAULT2        0b00001000
#define N_FAULT4        0b00010000
#define N_FAULT6        0b00011000

float LM75_regdata2float(int regdata);
int LM75_float2regdata(float temp);

unsigned char LM75_Read_Config();     // Read the actual configuration byte.
float LM75_Read_Temp();               // Read a temperature and return as a float.
float LM75_Read_Thyst();              // Read the hysteresis byte.
float LM75_Read_Tos();                // Read the OS byte.

unsigned char LM75_Read_1_byte();
int LM75_Read_2_byte();

void LM75_Read_Temp_s(unsigned char *byte0); // Put the temp into a indicated pointer vector.
void LM75_Set_Config(unsigned char byte0); // Set the confuguration byte.
void LM75_Set_Thyst(float thyst_val); // Set the hysteresis byte.
void LM75_Set_Tos(float tos_val);     // Set the OS byte.

void LM75_Set_Pointer(unsigned char pointer_val);

#endif	/* LM75_H */

