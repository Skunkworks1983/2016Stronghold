#include <Commands/Climbing/RunWinch.h>
#include <Commands/Climbing/SafeRotateArm.h>
#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <Commands/MultiTool/ManualCollectorMove.h>
#include <OI.h>
#include <Services/Logger.h>
#include <Subsystems/Collector.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdbool>
#include <cstdio>

OI::OI() {
#if USE_GAMEPAD
	gamepad = new Joystick(OI_JOYSTICK_GAMEPAD);
#else
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);
#endif
	op = new Joystick(OI_JOYSTICK_OPERATOR_PORT);

	collect = new JoystickButton(op, 8);
	collectorDown = new JoystickButton(op, 7);
	collectorUp = new JoystickButton(op, 6);
	collectorPass = new JoystickButton(op, 5);
	collector45 = new JoystickButton(op, 4);
	lowFire = new JoystickButton(op, 1);
	lowArm = new JoystickButton(op, 2);
	lowAim = new JoystickButton(op, 3);
	highFire = new JoystickButton(op, 17);
	highAim = new JoystickButton(op, 18);
	highAimPosition1 = new JoystickButton(op, 19);
	highAimPosition2 = new JoystickButton(op, 20);
	highLineUp = new JoystickButton(op, 23);
	climberArmsUp = new JoystickButton(op, 10);
	winchEngage = new JoystickButton(op, 11);
	manualOveride = new JoystickButton(op, 9);
	manualWinchReverse = new JoystickButton(op, 21);
	manualCollectorDown = new JoystickButton(op, 22);
	manualCollectorUp = new JoystickButton(op, 24);
	portcullis = new JoystickButton(op, 12);

	registerButtonListeners();
}

OI::~OI() {
#if USE_GAMEPAD
	delete gamepad;
#else
	delete leftStick;
	delete rightStick;
#endif
	delete collect;
	delete collectorDown;
	delete collectorUp;
	delete collectorPass;
	delete collector45;
	delete lowFire;
	delete lowArm;
	delete lowAim;
	delete highFire;
	delete highAim;
	delete highAimPosition1;
	delete highAimPosition2;
	delete highLineUp;
	delete climberArmsUp;
	delete winchEngage;
	delete manualOveride;
	delete manualWinchReverse;
	delete manualCollectorDown;
	delete manualCollectorUp;
	delete portcullis;
}

double OI::getLeftStickY() {
#if USE_GAMEPAD
	return gamepad->GetY() * fabs(gamepad->GetY());
#else
	return leftStick->GetY() * fabs(leftStick->GetY());
#endif
}

double OI::getRightStickY() {
#if USE_GAMEPAD
	return gamepad->GetAxis(Joystick::AxisType::kThrottleAxis)
	* fabs(gamepad->GetAxis(Joystick::AxisType::kThrottleAxis));
#else
	return rightStick->GetY() * fabs(rightStick->GetY());
#endif
}

void OI::registerButtonListeners() {
	char str[1024];
	sprintf(str, "RegisterButtonListeners called");
	writeToLogFile(LOGFILE_NAME, str);

	//collect->WhileHeld(new ActivateRollers(Collector::KForward));
	/*collectorDown->WhenPressed(new CollectorMove(cCollect));
	collectorUp->WhenPressed(new CollectorMove(cTOP));
	collectorPass->WhileHeld(new ActivateRollers(Collector::KBackward));
	collector45->WhenPressed(new CollectorMove(c45));
	lowFire->WhenPressed(new ActivateRollers(Collector::KBackward));
	//lowArm->WhenPressed();	//no need for this at the moment
	lowAim->WhenPressed(new CollectorMove(cLowBar));
	//highFire->WhenPressed();
	//highAim;
	//highAimPosition1;
	//highAimPosition2;
	highLineUp->WhenPressed(new RotateTowardCameraTarget());*/
	climberArmsUp->WhileHeld(new SafeRotateArm(CLIMBER_ARM_UP_POSITION));
	//winchEngage->WhileHeld(new RunWinch(.5));
	//manualOveride;	no effect currently
	manualWinchReverse->WhileHeld(new RunWinch(-.1));
	/*manualCollectorDown->WhileHeld(new ManualCollectorMove(-.2));
	manualCollectorUp->WhileHeld(new ManualCollectorMove(.2));
	portcullis->WhileHeld(new ActivateRollers(Collector::KBackward));*/

	sprintf(str, "RegisterButtonListeners Ended");
	writeToLogFile(LOGFILE_NAME, str);
}

bool OI::isJoystickButtonPressed(int control, int button) {
	switch (control) {
	case OI_JOYSTICK_LEFT_PORT:
		return leftStick->GetRawButton(button);
	case OI_JOYSTICK_RIGHT_PORT:
		return rightStick->GetRawButton(button);
	case OI_JOYSTICK_OPERATOR_PORT:
		return op->GetRawButton(button);
#if USE_GAMEPAD
		case OI_JOYSTICK_GAMEPAD_PORT:
		return gamepad->GetRawButton(button);
#endif
	}
	return false;
}
