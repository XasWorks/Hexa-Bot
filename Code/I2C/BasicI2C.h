
#include "I2CStatCodes.h"

class BasicI2C {

protected:
  void clearTWINT();
  void ACK();
  void NACK();
  void start();
  void stop();
  void load(uint8_t data);
  uint8_t readSR();

}
