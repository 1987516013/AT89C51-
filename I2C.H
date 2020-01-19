#ifndef __I2C_H
#define __I2C_H
#include <reg51.h>
sbit SCL=P3^6;
sbit SDA=P3^7;
void PCF8591Send( char addr, char dat);
int  PCF8591Read( char addr);
#end if;
