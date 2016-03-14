#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include <Joystick.h>
#include <cstring>
#include <RobotMap.h>
#include <Buttons/JoystickButton.h>

class OI {
private:
	Joystick *gamepad = NULL;
	Joystick *leftStick = NULL;
	Joystick *rightStick = NULL;
	Joystick *op = NULL;

	JoystickButton *collect = NULL;
	JoystickButton *shooterDown = NULL;
	JoystickButton *shooterUp = NULL;
	JoystickButton *shooterPass = NULL;
	JoystickButton *shooter45 = NULL;
	JoystickButton *lowFire = NULL;
	JoystickButton *lowArm = NULL;
	JoystickButton *lowAim = NULL;
	JoystickButton *highFire = NULL;
	JoystickButton *highArm = NULL;
	JoystickButton *highArmPosition1 = NULL;
	JoystickButton *highArmPosition2 = NULL;
	JoystickButton *highLineUp = NULL;
	JoystickButton *climberArmsUp = NULL;
	JoystickButton *winchEngage = NULL;
	JoystickButton *manualOveride = NULL;
	JoystickButton *manualWinchReverse = NULL;
	JoystickButton *manualShooterDown = NULL;
	JoystickButton *manualShooterUp = NULL;
	JoystickButton *portcullis = NULL;

	JoystickButton *stopShooterPID = NULL;
	JoystickButton *driverShooterDown = NULL;
	JoystickButton *driverShooterUp = NULL;
	JoystickButton *holdAgainstTower = NULL;

public:
	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
	void registerButtonListeners();bool isJoystickButtonPressed(int control,
			int button);
};

#endif
