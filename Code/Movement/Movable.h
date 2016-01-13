/*
 * Movable.h
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#ifndef CODE_MOVABLE_H_
#define CODE_MOVABLE_H_

#include <util/atomic.h>

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
	void setRotationSpeed(float speed);
	//Set the movement speed in mm / second
	void setSpeed(float speed);

	//Rotate it towards a specific direction in degrees
	void rotateTo(float angle);
	//Make the robot face a specific direction in degrees, ranging from -180 to 180.
	void headTo(float angle);
	//Rotate the robot by the specified amount of degrees.
	void rotateBy(float angle);

	//Move the robot to a specific position in mm
	void moveTo(float x, float y);
	//Move the robot by the specified amount of mm.
	void moveBy(float x, float y);

	//Move the robot forwards by the specified amount of mm towards the direction the robot is currently facing.
	void moveTowards(float dist);
	//Move the robot forwards towards the specified direction in degrees by "dist" mm.
	void moveTowards(float dist, float angle);

	//Wait for all functions to finish. Abstract method
	void flush();

	//Returns true if the robot is finished with everything important and can move again.
	bool isReady();
	//Returns true if the robot is at its wanted position
	bool atPosition();
	//Returns true if the robot is at its wanted rotation
	bool atRotation();

	//Return the current X positon in mm.
	float getX();
	//Return the current Y position in mm.
	float getY();
	//Return the current rotation in degrees.
	float getR();
};



#endif /* CODE_MOVABLE_H_ */
