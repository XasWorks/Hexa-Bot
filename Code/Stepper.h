#include <avr/io.h>
#include <math.h>

class Stepper {
private:
	volatile uint8_t *PORT;
	volatile uint8_t pin;

	volatile uint16_t updateSpeed;

	volatile int32_t stepsToGo;
	volatile uint16_t virtualSteps;
	volatile uint16_t stepSpeed;

public:

	Stepper(volatile uint8_t *P, uint8_t pin, volatile uint16_t updateFrequency);

	void update();

	void setSpeed(uint16_t stepsPerSecond);
	void move(int32_t steps);
	void flush();
};
