#include <Commands/Climbing/MoveServo.h>
#include <Commands/Climbing/RunWinch.h>
#include <Commands/Climbing/SafeRotateArm.h>
#include <Commands/Climbing/StopArmPID.h>
#include <Commands/Driving/Turning/ArcTurnToCamera.h>
#include <Commands/MultiTool/ResetCollectorEncoder.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunCollector.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/MultiTool/StopCollectorPID.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/IndexBall.h>
#include <Commands/Shooting/PIDShot.h>
#include <OI.h>
#include <Subsystems/Shooter.h>
#include <cmath>
#include <cstdbool>

OI::OI() {
#if USE_GAMEPAD
	gamepad = new Joystick(0);
#else
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);

	op = new Joystick(OI_JOYSTICK_OPERATOR_PORT);
#endif
	//driverbuttons
	stopShooterPID = new JoystickButton(leftStick, 2);
	driverTankDriveOneCIM = new JoystickButton(leftStick, 1);
	driverShooterDown = new JoystickButton(rightStick, 1);
	driverShooterUp = new JoystickButton(rightStick, 2);
	rotateToCamera = new JoystickButton(rightStick, 3);

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
	highArm = new JoystickButton(op, 18);
	highArmPosition1 = new JoystickButton(op, 19);
	highArmPosition2 = new JoystickButton(op, 20);
	highLineUp = new JoystickButton(op, 23);
	climberArmsUp = new JoystickButton(op, 10);
	winchEngage = new JoystickButton(op, 11);
	manualOveride = new JoystickButton(op, 9);
	manualWinchReverse = new JoystickButton(op, 21);
	manualShooterDown = new JoystickButton(op, 22);
	manualShooterUp = new JoystickButton(op, 24);
	portcullis = new JoystickButton(op, 12);
//ayy lmao you register my buttons ;)
	registerButtonListeners(/* woah look at dat chees*/);
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
	delete highArm;
	delete highArmPosition1;
	delete highArmPosition2;
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
	delete rotateToCamera;
	delete driverTankDriveOneCIM;
}

double OI::getLeftStickY() {
#if USE_GAMEPAD
	return -gamepad->GetY() * fabs(gamepad->GetY());
#else
	return -leftStick->GetY() * fabs(leftStick->GetY());
#endif
}

double OI::getRightStickY() {
#if USE_GAMEPAD
	return -gamepad->GetRawAxis(5) * fabs(gamepad->GetRawAxis(5));
	//return gamepad->GetAxis(Joystick::AxisType::kNumAxisTypes) * fabs(gamepad->GetAxis(Joystick::AxisType::kNumAxisTypes));
	//return gamepad->GetAxis(Joystick::AxisType::kThrottleAxis)* fabs(gamepad->GetAxis(Joystick::AxisType::kThrottleAxis));
#else
	return -rightStick->GetY() * fabs(rightStick->GetY());
#endif
}

void OI::registerButtonListeners() {
#if USE_GAMEPAD

#else
	/**
	 * Driver Buttons
	 */
	driverShooterDown->WhileHeld(new RunNewCollector());
	driverShooterDown->WhenPressed(new RotateShooter(cCollect));
	driverShooterUp->WhenPressed(new RotateShooter(cTOP));
	rotateToCamera->WhenPressed(new ArcTurnToCamera(.75, -.5));
	stopShooterPID->WhenPressed(new StopShooterRotationPID());

	/**
	 * Operator Buttons
	 */

	collect->WhileHeld(new RunNewCollector(false));
	shooterDown->WhenPressed(new RotateShooter(cCollect));

	shooterUp->WhenPressed(new RotateShooter(cTOP));

	shooterPass->WhileHeld(new RunNewCollector(true));
	shooter45->WhenPressed(new RotateShooter(c45));

	lowFire->WhileHeld(new AutoRunCollector());
	lowArm->WhenPressed(new IndexBall());	//no need for this at the moment
	lowAim->WhenPressed(new RotateShooter(c60));

	const double shot_speed = 70.0;

	highArm->WhileHeld(new PIDShot(shot_speed, shot_speed));
	highArmPosition1->WhileHeld(new PIDShot(shot_speed - 3, shot_speed - 3));
	highArmPosition2->WhileHeld(new PIDShot(shot_speed - 6, shot_speed - 6));
	highFire->WhileHeld(new RunCollector(Shooter::KForward, 1.0));
	//highAimPosition1;
	highLineUp->WhenPressed(new ResetShooterRotationEncoder());
	//highLineUp->WhenPressed(new RotateTowardCameraTarget());
	const double climber_arm_up_debug = 3125;
	climberArmsUp->WhileHeld(new SafeRotateArm(climber_arm_up_debug));
	climberArmsUp->WhenReleased(new StopArmPID());
	winchEngage->WhileHeld(new RunWinch(1.0));
	//manualOveride;	no effect currently
	manualWinchReverse->WhileHeld(new RunWinch(-.2));
	manualShooterDown->WhenPressed(
			new MoveServo(MoveServo::eServoPosition::OUT));
	manualShooterUp->WhenPressed(new MoveServo(MoveServo::eServoPosition::IN));
	portcullis->WhileHeld(new RunNewCollector(true));
#endif
}

bool OI::isJoystickButtonPressed(int control, int button) {
	switch (control) {
#if USE_GAMEPAD
	case 0:
		return gamepad->GetRawButton(button);
#else
		case OI_JOYSTICK_LEFT_PORT:
		return leftStick->GetRawButton(button);
		case OI_JOYSTICK_RIGHT_PORT:
		return rightStick->GetRawButton(button);
		case OI_JOYSTICK_OPERATOR_PORT:
		return op->GetRawButton(button);
#endif
	}
	return false;
}
