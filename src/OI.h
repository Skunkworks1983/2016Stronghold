#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include <Joystick.h>
#include <cstring>
#include <RobotMap.h>
#include <Buttons/JoystickButton.h>

class OI
{
private:
	Joystick *leftStick, *rightStick;
	Button *breachButton;
public:
	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
};

#endif
