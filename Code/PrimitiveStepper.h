#include <avr/io.h>
#include <math.h>

class PrimitiveStepper {
private:
	//Port of the stepper motor
	volatile uint8_t *PORT;
	//Pin of the stepper motor. Stepping signals are issued at pin, dir signals at pin+1
	volatile uint8_t pin;

	//Speed of the ISR. Required to set the stepping speed correctly.
	volatile uint16_t updateSpeed;

	//Steps the motor still has to make.
	volatile int32_t stepsToGo;
	//How many "virtual" steps the system currently has. Allows for finer speeds.
	volatile uint16_t virtualSteps;
	//How many stes per ISR the motor has to make. Software comma at 1<<15, allowing for finer speeds.
	volatile uint16_t stepSpeed;
	//Total steps the motor has made. Useful for absolute positioning.
	volatile int32_t totalSteps;

	void step(uint8_t dir);

public:

	//Main constructor of the Stepper motor. P is the port, p the first of the two pins required for the motor.
	//updateFrequency specifies the ISR speed that the motor runs on.
	PrimitiveStepper(volatile uint8_t *P, uint8_t pin,
			volatile uint16_t updateFrequency);

	//ISR Function to update the stepper motor (Stepping it when required)
	void update();

	//Set the speed in steps per Second. Primitive, not influenced by steps/mm.
	void setSpeed(uint16_t stepsPerSecond);
	//Move the motor by a certain amount of steps. Primitive, not influenced by steps/mm.
	void move(int32_t steps);
	//Wait for every motor move of this motor to finish.
	void flush();

	//Reset the motor and abort all movements
	void reset();
};
