#include <Commands/Climbing/RotateArm.h>
#include <Commands/Climbing/RunWinch.h>
#include <Commands/Driving/HoldAgainstTower.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <Commands/MultiTool/StopCollectorPID.h>
#include <OI.h>
#include <Services/Logger.h>
#include <SmartDashboard/SmartDashboard.h>
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
	op = new Joystick(OI_OPERATOR_PORT);

	//collector
	collectBall = new JoystickButton(gamepad, 5);
	collectorUp = new JoystickButton(rightStick, 2);
	collectorDown = new JoystickButton(rightStick, 1);
	stopPID = new JoystickButton(rightStick, 3);

	//aiming
	aimAtGoal = new JoystickButton(gamepad, 6);

	holdAgainst = new JoystickButton(rightStick, 1);

	//shooting
	shootLow = new JoystickButton(leftStick, 1);
	shootHigh = new JoystickButton(op, 8);
	spinUpShooter = new JoystickButton(op, 9);

	//climbing
	rotateArm = new JoystickButton(leftStick, 3);
	engageWinch = new JoystickButton(leftStick, 2);
	reverseWinch = new JoystickButton(leftStick, 4);

	registerButtonListeners();
}

OI::~OI() {
#if USE_GAMEPAD
	delete gamepad;
#else
	delete leftStick;
	delete rightStick;
#endif
	delete op;
	delete portcullisBreach;
	delete chevalBreach;
	delete generalBreach;
	delete collectBall;
	delete collectorUp;
	delete aimAtGoal;
	delete shootLow;
	delete shootHigh;
	delete spinUpShooter;
	delete rotateArm;
	delete engageWinch;
	delete collectorDown;
	delete reverseWinch;
}

double OI::getLeftStickY() {
#if USE_GAMEPAD
	return -gamepad->GetY()*fabs(gamepad->GetY());
#else
	return -leftStick->GetY() * fabs(leftStick->GetY());
#endif
}

double OI::getRightStickY() {
#if USE_GAMEPAD
	return -gamepad->GetAxis(Joystick::AxisType::kThrottleAxis)*fabs(gamepad->GetAxis(Joystick::AxisType::kThrottleAxis));
#else
	return -rightStick->GetY() * fabs(rightStick->GetY());
#endif
}

void OI::registerButtonListeners() {
	char str[1024];
	sprintf(str, "RegisterButtonListeners called");
	writeToLogFile(LOGFILE_NAME, str);
	rotateArm->WhenPressed(new RotateArm(CLIMBER_ARM_UP_POSITION));
	SmartDashboard::PutData("Climber Down",
			new RotateArm(CLIMBER_ARM_DOWN_POSITION));

	//engageWinch->WhenPressed(new RunWinchToSetPoint(CLIMBER_WINCH_UP_POSITION, .25));
	engageWinch->WhileHeld(new RunWinch(.50));
	reverseWinch->WhileHeld(new RunWinch(-.1));

	shootLow->WhileHeld(
			new ActivateRollers(Collector::rollerDirection::KBackward));
	collectorUp->WhenPressed(new CollectorMove(TOP));
	//collectorDown->WhenPressed(new CollectorMove(FLOOR));
	//collectorDown->WhileHeld(new ActivateRollers(Collector::rollerDirection::KForward));
	stopPID->WhenPressed(new StopCollectorPID());

	holdAgainst->WhenPressed(new HoldAgainstTower(-.2));
}

bool OI::isJoystickButtonPressed(int control, int button) {
	return false;
}
