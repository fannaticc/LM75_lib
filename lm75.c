/* 
 * File:   lm75.h
 * Author: Raphael
 *
 * Created on 25 de Março de 2017, 02:24
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "lm75.h"
#include "my_i2c.h"


void LM75_Set_Pointer(unsigned char pointer_val)
{
    I2C_Start();
    I2C_WriteByte(LM75_ADR);    // Send the ADR to the talk device.
    I2C_WriteByte(pointer_val); // Set the pointer to read temperature.
    I2C_Stop();
}

unsigned char LM75_Read_1_byte()
{
    unsigned char byte0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR + 1); // Send the ADR to the talk device.
    byte0 = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    return byte0;
}

int LM75_Read_2_byte()
{
    unsigned char LSB = 0;
    unsigned char MSB = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR + 1); // Send the ADR to the talk device.
    MSB = I2C_ReadByte(1); // Read the data
    LSB = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    return (((unsigned int)MSB << 8) | (LSB));
}

//==============================================================================
//Sets Information in the RTC.
//byte0: Sets "Word Address".
//byte1: Sets the information.
//==============================================================================
void LM75_Read_Temp_s(unsigned char *byte0)
{
    unsigned char MSB = 0;
    unsigned char LSB = 0;
    float temp = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR);    // Send the ADR to the talk device.
    I2C_WriteByte(TEMPERATURE); // Set the pointer to read temperature.
    I2C_RepeatedStart();        // Repeat the start condition.
    I2C_WriteByte(LM75_ADR + 1); // Put the device in transmition mode.
    MSB = I2C_ReadByte(1); // Read the data
    LSB = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    temp = LM75_regdata2float((((unsigned int)MSB << 8) | (LSB)));

    sprintf(byte0, "%3.1f", temp);
}

float LM75_Read_Temp()
{
    unsigned char LSB = 0;
    unsigned char MSB = 0;
    int word0 = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR);    // Send the ADR to the talk device.
    I2C_WriteByte(TEMPERATURE); // Set the pointer to read temperature.
    I2C_RepeatedStart();        // Repeat the start condition.
    I2C_WriteByte(LM75_ADR + 1); // Put the device in transmition mode.
    MSB = I2C_ReadByte(1); // Read the data and ACK.
    LSB = I2C_ReadByte(0); // Read the data no ACK.
    I2C_Stop();
    
    word0 = (((unsigned int)MSB << 8) | (LSB)); // Put the two nibbles in one word
    
    return LM75_regdata2float(word0); // Convert as a float.
}

void LM75_Set_Config(unsigned char byte0)
{
    I2C_Start();
    I2C_WriteByte(LM75_ADR);
    I2C_WriteByte(CONFIGURATION);
    I2C_WriteByte(byte0);
    I2C_Stop();
}


unsigned char LM75_Read_Config()
{
    unsigned char byte0 = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR); 
    I2C_WriteByte(CONFIGURATION); // Set the pointer to read temperature.
    I2C_RepeatedStart();
    I2C_WriteByte(LM75_ADR + 1); 
    byte0 = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    return byte0;
}


void LM75_Set_Thyst(float thyst_val)
{
    int word0 = 0;
    
    word0 = LM75_float2regdata(thyst_val);
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR);
    I2C_WriteByte(THYST);
    I2C_WriteByte((unsigned char)((word0 >> 8) & 0xFF));
    I2C_WriteByte((unsigned char)(word0 & 0xFF));
    I2C_Stop();
}


float LM75_Read_Thyst()
{
    unsigned char LSB = 0;
    unsigned char MSB = 0;
    int thyst = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR);
    I2C_WriteByte(THYST); // Set the pointer to read temperature.
    I2C_RepeatedStart();
    I2C_WriteByte(LM75_ADR + 1); 
    MSB = I2C_ReadByte(1); // Read the data
    LSB = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    thyst = (((unsigned int)MSB << 8) | (LSB));
    
    return LM75_regdata2float(thyst);
}


void LM75_Set_Tos(float tos_val)
{
    int word0 = 0;
    
    word0 = LM75_float2regdata(tos_val);
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR); // Sen the LM75 address.
    I2C_WriteByte(TOS); // Set the register pointer to TOS.
    I2C_WriteByte((unsigned char)((word0 >> 8) & 0xFF)); // Transmit the MSB.
    I2C_WriteByte((unsigned char)(word0 & 0xFF)); // transmit the LSB.
    I2C_Stop();
    
}


float LM75_Read_Tos()
{
    unsigned char LSB = 0;
    unsigned char MSB = 0;
    int tos = 0;
    
    I2C_Start();
    I2C_WriteByte(LM75_ADR);    
    I2C_WriteByte(TOS); // Set the pointer to read temperature.
    I2C_RepeatedStart();
    I2C_WriteByte(LM75_ADR + 1); 
    MSB = I2C_ReadByte(1); // Read the data
    LSB = I2C_ReadByte(0); // Read the data
    I2C_Stop();
    
    tos = (((unsigned int)MSB << 8) | (LSB));
    
    return LM75_regdata2float(tos);
}

float LM75_regdata2float(int regdata)
{
  return ((float)(int)regdata / 32) / 8;
    /*if (regdata >> 15) 
    {
        temp -= 0x100;
    }
    return temp;*/
}

int LM75_float2regdata(float temp)
{
  // First multiply by 8 and coerce to integer to get +/- whole numbers
  // Then coerce to word and bitshift 5 to fill out MSB
  return (int)((int)(temp * 8) << 5);
}