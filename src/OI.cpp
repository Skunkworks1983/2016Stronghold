#include "OI.h"
#include <Joystick.h>
#include <cstring>
#include <RobotMap.h>

OI::OI()
{
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);
}

OI::~OI() {
	delete leftStick;
	delete rightStick;
}

double OI::getLeftStickY() {
	return leftStick->GetY()*fabs(leftStick->GetY());
}

double OI::getRightStickY() {
	return rightStick->GetY()*fabs(rightStick->GetY());
}
