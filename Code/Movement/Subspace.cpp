
#include "Subspace.h"

Coordinates Subspace::rotate(Coordinates coords, float angle) {
	Coordinates newCoords;

	newCoords.xCoord = coords.xCoord * cos(angle * DEG_TO_RAD) - coords.yCoord * sin(angle * DEG_TO_RAD);
	newCoords.yCoord = coords.yCoord * cos(angle * DEG_TO_RAD) + coords.xCoord * sin(angle * DEG_TO_RAD);

	return newCoords;
}
Coordinates Subspace::offset(Coordinates coords) {
	Coordinates newCoords;

	newCoords = this->rotate(coords, this->rOrig);

	newCoords.xCoord += this->xOrig;
	newCoords.yCoord += this->yOrig;

	return newCoords;
}
Coordinates Subspace::unoffset(Coordinates coords) {
	Coordinates newCoords;

	coords.xCoord -= this->xOrig;
	coords.yCoord -= this->yOrig;

	newCoords = this->rotate(coords, -this->rOrig);

	return newCoords;
}

void Subspace::updateXYR() {
	Coordinates coords;
	coords.xCoord = destination->getX();
	coords.yCoord = destination->getY();

	coords = this->unoffset(coords);

	this->xPos = coords.xCoord;
	this->yPos = coords.yCoord;
	this->rPos = destination->getR() - this->rOrig;
}

Subspace::Subspace(Movable *destination) {
  this->destination = destination;

  this->xOrig = destination->getX();
  this->yOrig = destination->getY();
  this->rOrig = destination->getR();
}

void Subspace::setRotationSpeed(float speed) {
	this->destination->setRotationSpeed(speed);
}
void Subspace::setSpeed(float speed) {
	this->destination->setSpeed(speed);
}

void Subspace::rotateTo(float angle) {
	this->destination->rotateTo(angle + this->rOrig);
}
void Subspace::rotateBy(float angle) {
	this->destination->rotateBy(angle);
}

void Subspace::moveTo(float x, float y) {
	Coordinates newCoords;
	newCoords.xCoord = x;
	newCoords.yCoord = y;

	newCoords = this->offset(newCoords);

	destination->moveTo(newCoords.xCoord, newCoords.yCoord);
}
void Subspace::moveBy(float x, float y) {
	Coordinates newCoords;
	newCoords.xCoord = x;
	newCoords.yCoord = y;

	newCoords = this->rotate(newCoords, this->rOrig);

	destination->moveBy(newCoords.xCoord, newCoords.yCoord);
}

void Subspace::moveTowards(float distance) {
	destination->moveTowards(distance, this->rOrig + destination->getR());
}
void Subspace::moveTowards(float distance, float direction) {
	destination->moveTowards(distance, this->rOrig + direction);
}

bool Subspace::atPosition() {
	return destination->atPosition();
}
bool Subspace::atRotation() {
	return destination->atRotation();
}
void Subspace::flush() {
	this->destination->flush();
}

float Subspace::getX() {
	this->updateXYR();
	return this->xPos;
}
float Subspace::getY() {
	this->updateXYR();
	return this->yPos;
}
float Subspace::getR() {
	return this->rOrig + destination->getR();
}
