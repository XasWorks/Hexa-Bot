
#include "BrightnessSensor.h"

BrightnessSensor::BrightnessSensor() {
}

void BrightnessSensor::update() {
  this->jobStatus = 2;
}

void BrightnessSensor::beginOperation() {
  TWI_Handler::IO.buf.queue(0b11110);
  TWI_Handler::IO.buf.queue(COMS_BRIGHT);
}
void BrightnessSensor::endOperation() {
  this->jobStatus--;
  switch(this->jobStatus) {
    case 1:
      TWI_Handler::IO.buf.queue(0b11111);
      TWI_Handler::IO.readLength = 1;
    break;

    case 0:
      this->brightness = TWI_Handler::IO.buf.read();
    break;
  }
}

uint8_t BrightnessSensor::getBrightness() {
	return this->brightness;
}
