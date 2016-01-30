#include "OI.h"

OI::OI()
{
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);
	breachButton = new JoystickButton(leftStick, OI_BUTTON_BREACH_PORT);
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
