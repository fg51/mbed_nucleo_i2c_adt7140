#ifndef D_ADT7410_H
#define D_ADT7410_H

#include "mbed.h"

namespace adt7410 {
extern const uint32_t kADT7410_frequency;

float read_temperature(I2C &i2c);
void set_config(I2C &i2c, char regVal);
char get_config(I2C &i2c);

}

#endif //#ifndef D_ADT7410_H