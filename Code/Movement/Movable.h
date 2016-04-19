/*
 * Movable.h
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#ifndef CODE_MOVABLE_H_
#define CODE_MOVABLE_H_

#include <math.h>
#include <util/atomic.h>

#define DEG_TO_RAD 0.017453293


//Interface class for everything that can move. Robot wheels, Drone coordinates, etc.
class Movable {
protected:
	volatile float xPos = 0, xTarget = 0;
	volatile float yPos = 0, yTarget = 0;
	float speed = 0;
	volatile float rPos = 0, rTarget = 0, rSpeed = 0;

public:
	Movable();

	//Set the rotation speed in degrees / second
	virtual void setRotationSpeed(float speed);
	//Set the movement speed in mm / second
	virtual void setSpeed(float speed);

	//Rotate it towards a specific direction in degrees
	virtual void rotateTo(float angle);
	//Rotate the robot by the specified amount of degrees.
	virtual void rotateBy(float angle);

	//Move the robot to a specific position in mm
	virtual void moveTo(float x, float y);
	//Move the robot by the specified amount of mm.
	virtual void moveBy(float x, float y);

	//Move the robot forwards by the specified amount of mm towards the direction the robot is currently facing.
	virtual void moveTowards(float dist);
	//Move the robot forwards towards the specified direction in degrees by "dist" mm.
	virtual void moveTowards(float dist, float angle);

	//Wait for all functions to finish. Abstract method
	virtual void flush();

	//Returns true if the robot is finished with everything important and can move again.
	virtual bool isReady();
	//Returns true if the robot is at its wanted position
	virtual bool atPosition();
	//Returns true if the robot is at its wanted rotation
	virtual bool atRotation();

	//Return the current X positon in mm.
	virtual float getX();
	//Return the current Y position in mm.
	virtual float getY();
	//Return the current rotation in degrees.
	virtual float getR();
};



#endif /* CODE_MOVABLE_H_ */
