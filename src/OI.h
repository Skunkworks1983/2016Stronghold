#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick *leftStick, *rightStick;
public:
	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
};

#endif
