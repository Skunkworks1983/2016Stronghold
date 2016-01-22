#ifndef IMotor_H
#define IMotor_H

#include "Talon.h" //To declare Talon

class IMotor
{
private:
	Talon * m_talon;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	IMotor(uint32_t channel);
	void InitDefaultCommand();
	void Set(double);
};

#endif
