#ifndef _SUBSPACE_H
#define _SUBSPACE_H

#include "Movable.h"

struct Coordinates {
	float xCoord;
	float yCoord;
};

class Subspace : public Movable {
private:
	float xOrig = 0, yOrig = 0;
	float rOrig = 0;

	Movable *destination = 0;

	Coordinates rotate(Coordinates coord, float angle);
	Coordinates offset(Coordinates coord);
	Coordinates unoffset(Coordinates coord);

	void updateXYR();

public:
	Subspace(Movable *destination);

	void setRotationSpeed(float speed);
	void setSpeed(float speed);

	void rotateTo(float angle);
	void rotateBy(float angle);

	void moveTo(float x, float y);
	void moveBy(float x, float y);

	void moveTowards(float distance);
	void moveTowards(float distance, float direction);

	bool atPosition();
	bool atRotation();
	void flush();

	float getX();
	float getY();
	float getR();
};


#endif
