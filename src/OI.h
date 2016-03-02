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
	JoystickButton *collectorDown = NULL;
	JoystickButton *collectorUp = NULL;
	JoystickButton *collectorPass = NULL;
	JoystickButton *collector45 = NULL;
	JoystickButton *lowFire = NULL;
	JoystickButton *lowArm = NULL;
	JoystickButton *lowAim = NULL;
	JoystickButton *highFire = NULL;
	JoystickButton *highAim = NULL;
	JoystickButton *highAimPosition1 = NULL;
	JoystickButton *highAimPosition2 = NULL;
	JoystickButton *highLineUp = NULL;
	JoystickButton *climberArmsUp = NULL;
	JoystickButton *winchEngage = NULL;
	JoystickButton *manualOveride = NULL;
	JoystickButton *manualWinchReverse = NULL;
	JoystickButton *manualCollectorDown = NULL;
	JoystickButton *manualCollectorUp = NULL;
	JoystickButton *portcullis = NULL;

	JoystickButton *stopCollectorPID = NULL;
	JoystickButton *driverCollectorDown = NULL;
	JoystickButton *driverCollectorUp = NULL;
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
