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
	Joystick *leftStick, *rightStick, *op;
public:
	//breaching buttons
	JoystickButton *portcullisBreach;
	JoystickButton *chevalBreach;
	JoystickButton *generalBreach;

	// collector buttons
	JoystickButton *collectBall;
	JoystickButton *collectorUp;

	//aiming buttons
	JoystickButton *aimAtGoal;

	//shooting buttons
	JoystickButton *shootLow;
	JoystickButton *shootHigh;
	JoystickButton *spinUpShooter;

	//climbing buttons
	JoystickButton *rotateArm;
	JoystickButton *engageWinch;

	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
	void registerButtonListener();
	bool isJoystickButtonPressed(int control, int button);
};

#endif
