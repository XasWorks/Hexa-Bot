#ifndef _SUBSPACE_H
#define _SUBSPACE_H

#include "Movable.h"

class Subspace : Movable {
private:
  float xOrig = 0, yOrig = 0;
  float rOrig = 0;

Movable *destination = 0;

public:
  Subspace(Movable *destination);
}


#endif
