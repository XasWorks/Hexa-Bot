#ifndef _BRIGHT_H
#define _BRIGHT_H

#include "Code/TWI/TWIHandler.h"
#include "Code/ComsCodes.h"

class BrightnessSensor : public TWI_M_Job {
private:
  uint16_t brightness = 0;

public:
  BrightnessSensor();

  void update();

  uint16_t getBrightness();

  void beginOperation();
  void endOperation();
};

#endif
