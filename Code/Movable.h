/*
 * Movable.h
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#ifndef CODE_MOVABLE_H_
#define CODE_MOVABLE_H_

class Movable {
private:
	float xPos, xTarget;
	float yPos, yTarget;
	float speed;
	float rPos, rTarget, rSpeed;

public:
	Movable();

	void setRotationSpeed(float speed);
	void setSpeed(float speed);

	void rotateTo(float angle);
	void headTo(float angle);
	void rotateBy(float angle);

	void moveTo(float x, float y);
	void moveBy(float x, float y);

	void flush();

	bool isReady();

	float getX();
	float getY();
	float getR();
};



#endif /* CODE_MOVABLE_H_ */
