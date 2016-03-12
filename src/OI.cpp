#include <Commands/Climbing/MoveServo.h>
#include <Commands/Climbing/RunWinch.h>
#include <Commands/Climbing/SafeRotateArm.h>
#include <Commands/MultiTool/ResetCollectorEncoder.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunCollector.h>
#include <OI.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
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

	//driverbuttons
	stopShooterPID = new JoystickButton(leftStick, 3);
	holdAgainstTower = new JoystickButton(leftStick, 2);
	driverShooterDown = new JoystickButton(rightStick, 1);
	driverShooterUp = new JoystickButton(rightStick, 2);

	//operatorbuttons
	collect = new JoystickButton(op, 8);
	shooterDown = new JoystickButton(op, 7);
	shooterUp = new JoystickButton(op, 6);
	shooterPass = new JoystickButton(op, 5);
	shooter45 = new JoystickButton(op, 4);
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
	manualShooterDown = new JoystickButton(op, 22);
	manualShooterUp = new JoystickButton(op, 24);
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
	delete shooterDown;
	delete shooterUp;
	delete shooterPass;
	delete shooter45;
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
	delete manualShooterDown;
	delete manualShooterUp;
	delete portcullis;

	delete stopShooterPID;
	delete driverShooterDown;
	delete driverShooterUp;
	delete holdAgainstTower;
}

double OI::getLeftStickY() {
#if USE_GAMEPAD
	return gamepad->GetY() * fabs(gamepad->GetY());
#else
	return -leftStick->GetY() * fabs(leftStick->GetY());
#endif
}

double OI::getRightStickY() {
#if USE_GAMEPAD
	return gamepad->GetAxis(Joystick::AxisType::kThrottleAxis)
	* fabs(gamepad->GetAxis(Joystick::AxisType::kThrottleAxis));
#else
	return -rightStick->GetY() * fabs(rightStick->GetY());
#endif
}

void OI::registerButtonListeners() {
	char str[1024];
	sprintf(str, "RegisterButtonListeners called");
	Logger::getLogger()->log(str, Info);

	/**
	 * Driver Buttons
	 */
	driverShooterDown->WhileHeld(new RunCollector(Shooter::KForward));
	driverShooterDown->WhenPressed(new RotateShooter(cCollect));
	driverShooterUp->WhenPressed(new RotateShooter(cTOP));
	//holdAgainstTower->WhenPressed(new HoldAgainstTower(.2));

	/**
	 * Operator Buttons
	 */

	collect->WhileHeld(new RunCollector(Shooter::KForward));
	shooterDown->WhenPressed(new RotateShooter(cCollect));

	shooterUp->WhenPressed(new RotateShooter(cTOP));

	shooterPass->WhileHeld(new RunCollector(Shooter::KBackward));
	shooter45->WhenPressed(new RotateShooter(c45));
	lowFire->WhenPressed(new RunCollector(Shooter::KBackward));
	//lowArm->WhenPressed();	//no need for this at the moment
	lowAim->WhenPressed(new RotateShooter(cLowBar));
	//highFire->WhenPressed();
	//highAim;
	//highAimPosition1;
	highLineUp->WhenPressed(new ResetShooterRotationEncoder());
	//highLineUp->WhenPressed(new RotateTowardCameraTarget());
	const double climber_arm_up_debug = 3125;
	climberArmsUp->WhenPressed(new SafeRotateArm(climber_arm_up_debug));
	winchEngage->WhileHeld(new RunWinch(.75));
	//manualOveride;	no effect currently
	manualWinchReverse->WhileHeld(new RunWinch(-.1));
	manualShooterDown->WhenPressed(new MoveServo(MoveServo::eServoPosition::OUT));
	manualShooterUp->WhenPressed(new MoveServo(MoveServo::eServoPosition::IN));
	portcullis->WhileHeld(new RunCollector(Shooter::KBackward));

	sprintf(str, "RegisterButtonListeners Ended");
	Logger::getLogger()->log(str, Debug);
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
