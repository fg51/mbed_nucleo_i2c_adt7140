#include "adt7410.h"


#define TEMP_REG_ADDR (0x00)
#define CONFIG_REG_ADDR (0x03)
#define RESET (0x2F)

// configuration register values
// only a partial list, don't use them all
#define ONE_SPS_MODE (0x40)

namespace adt7410 {

const uint32_t kADT7410_frequency = 100E+3;


static const uint16_t kBUS_ADDR = 0x90;

inline static float convert_to_degC(const char high, const char low);


float read_temperature(I2C &i2c)
{
  // set address pointer to temperature register
  const uint32_t kWrite_length = 1;
  const char wReg[kWrite_length] = {TEMP_REG_ADDR};
  i2c.write(kBUS_ADDR, wReg, kWrite_length);

  // read temperature register, two bytes
  const uint32_t kRead_length = 2;
  char rReg[kRead_length] = {0, 0};
  i2c.read(kBUS_ADDR, rReg, kRead_length);

  return convert_to_degC(rReg[0], rReg[1]);
}


inline static float convert_to_degC(const char high, const char low)
{
  // temperature returned is only 13 bits
  // discard alarm flags in lower bits
  const int _raw_temperature = (high << 8) | (low);
  const int raw_temperature  = _raw_temperature >> 3;

  // handle positive and negative temperatures
  // results in two's complement
  return (raw_temperature & 0x1000) ? (float) (raw_temperature - 8192) / 16 : (float) raw_temperature / 16;
}


void set_config(I2C &i2c, char regVal)
{
  const uint32_t kLENGTH = 2;
  const char wReg[kLENGTH] = {CONFIG_REG_ADDR, regVal};
  i2c.write(kBUS_ADDR, wReg, kLENGTH);
  return;
}

char get_config(I2C &i2c)
{
  const uint32_t kLENGTH = 1;

  char wReg[kLENGTH] = {CONFIG_REG_ADDR};
  // need to add repeat to supress stop
  i2c.write(kBUS_ADDR, wReg, kLENGTH, 1); //NOTE: 1 is repeate number

  char rReg[kLENGTH] = {0};
  i2c.read(kBUS_ADDR, rReg, kLENGTH);
  return rReg[0];
}

}
