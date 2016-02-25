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
	Joystick *gamepad;
	Joystick *leftStick, *rightStick;
	Joystick *op;
public:
	//breaching buttons
	JoystickButton *portcullisBreach;
	JoystickButton *chevalBreach;
	JoystickButton *generalBreach;

	JoystickButton *stopPID;
	// collector buttons
	JoystickButton *collectBall;
	JoystickButton *collectorUp;
	JoystickButton *collectorDown;

	JoystickButton *holdAgainst;
	//aiming buttons
	JoystickButton *aimAtGoal;

	//shooting buttons
	JoystickButton *shootLow;
	JoystickButton *shootHigh;
	JoystickButton *spinUpShooter;

	//climbing buttons
	JoystickButton *rotateArm;
	JoystickButton *engageWinch;
	JoystickButton *reverseWinch;

	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
	void registerButtonListeners();
	bool isJoystickButtonPressed(int control, int button);
};

#endif
