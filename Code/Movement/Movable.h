/*
 * Movable.h
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#ifndef CODE_MOVABLE_H_
#define CODE_MOVABLE_H_

//Interface class for everything that can move. Robot wheels, Drone coordinates, etc.
class Movable {
protected:
	volatile float xPos = 0, xTarget = 0;
	volatile float yPos = 0, yTarget = 0;
	volatile float speed = 0;
	volatile float rPos = 0, rTarget = 0, rSpeed = 0;

public:
	Movable();

	//Set the rotation speed (in degrees / second)  and the movement speed (in mm / second)
	void setRotationSpeed(float speed);
	void setSpeed(float speed);

	//Rotate to or by a specific angle. "headTo" is a special case in which the total amount of rotations is ignored, thusly using the fastest way to head towards "angle"
	void rotateTo(float angle);
	void headTo(float angle);
	void rotateBy(float angle);

	//Move the robot to or by a specific position or distance in mm.
	void moveTo(float x, float y);
	void moveBy(float x, float y);

	//Move the motor either towards current heading direction, or specified direction
	void moveTowards(float dist);
	void moveTowards(float dist, float angle);

	//Wait for all functions to finish. Abstract method
	void flush();

	//Returns true if the robot is finished with everything important and can move again.
	bool isReady();

	//Return the different corrdinates (in mm) or current rotation (in degrees)
	float getX();
	float getY();
	float getR();
};



#endif /* CODE_MOVABLE_H_ */
