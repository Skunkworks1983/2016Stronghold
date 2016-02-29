#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include <Joystick.h>
#include <cstring>
#include <RobotMap.h>
#include <Buttons/JoystickButton.h>

class OI {
private:
	Joystick *gamepad;
	Joystick *leftStick;
	Joystick *rightStick;
	Joystick *op;

	JoystickButton *collect;
	JoystickButton *collectorDown;
	JoystickButton *collectorUp;
	JoystickButton *collectorPass;
	JoystickButton *collector45;
	JoystickButton *lowFire;
	JoystickButton *lowArm;
	JoystickButton *lowAim;
	JoystickButton *highFire;
	JoystickButton *highAim;
	JoystickButton *highAimPosition1;
	JoystickButton *highAimPosition2;
	JoystickButton *highLineUp;
	JoystickButton *climberArmsUp;
	JoystickButton *winchEngage;
	JoystickButton *manualOveride;
	JoystickButton *manualWinchReverse;
	JoystickButton *manualCollectorDown;
	JoystickButton *manualCollectorUp;
	JoystickButton *portcullis;

	JoystickButton *stopCollectorPID;
	JoystickButton *driverCollectorDown;
	JoystickButton *driverCollectorUp;
	JoystickButton *holdAgainstTower;

public:
	OI();
	~OI();
	double getLeftStickY();
	double getRightStickY();
	void registerButtonListeners();
	bool isJoystickButtonPressed(int control,
			int button);
};

#endif
