/*
 * samples:
 *  - status LED
 *  - user button
 *  - i2c with adt7410
 */
#include "mbed.h"

#include "adt7410.h"

#define TURN_OFF_LED (0)
#define TURN_ON__LED (1)


DigitalOut myled(LED1);     /// LED1 is LD2 in F446
Serial pc(USBTX, USBRX);    /// tx, rx
DigitalIn mybutton(USER_BUTTON);

// I2C master(sda, scl);
I2C i2c(PB_9, PB_8);  /// SDA3, SCL3
/// I2C_SCL  = PB_8
/// I2C_SDA  = PB_9
/// SPI_MOSI = PA_7
/// SPI_MISO = PA_6
/// SPI_SCK  = PA_5
/// SPI_CS   = PB_6


int main() {
  pc.printf("Hello nucleo\r\n");
  pc.printf("SystemCoreClock: %d Hz\r\n", SystemCoreClock);

  i2c.frequency(adt7410::kADT7410_frequency);
  float temperature = adt7410::read_temperature(i2c);
  pc.printf("%f [degC]\r\n", temperature);

  while(1) {
    if (mybutton == 0) { // Button is pressed
      myled = TURN_OFF_LED;  // LED is OFF
      wait(0.2);  // 200 ms

      continue;
    }
    myled = TURN_ON__LED;  // LED is ON
    wait(0.2);  // 200 ms
    myled = TURN_OFF_LED;  // LED is OFF
    wait(1.0);  // 1 sec
  }
}
