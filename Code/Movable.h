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
private:
	float xPos, xTarget;
	float yPos, yTarget;
	float speed;
	float rPos, rTarget, rSpeed;

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
