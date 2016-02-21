#include <Commands/Climbing/RotateArm.h>
#include <Commands/MultiTool/ActivateRollers.h>
#include <Commands/MultiTool/CollectorMove.h>
#include <OI.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Collector.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdbool>

OI::OI()
{
#if USE_GAMEPAD
	gamepad = new Joystick(OI_JOYSTICK_GAMEPAD);
#else
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);
#endif
	op = new Joystick(OI_OPERATOR_PORT);

	//collector
	collectBall = new JoystickButton(gamepad, OI_COLLECT_BALL_PORT);
	collectorUp = new JoystickButton(gamepad, 1);
	collectorDown = new JoystickButton(gamepad, 2);

	//aiming
	aimAtGoal = new JoystickButton(op, OI_AIM_AT_GOAL_PORT);

	//shooting
	shootLow = new JoystickButton(gamepad, OI_SHOOT_LOW_PORT);
	shootHigh = new JoystickButton(op, OI_SHOOT_HIGH_PORT);
	spinUpShooter = new JoystickButton(op, OI_SPIN_UP_SHOOTER_PORT);

	//climbing
	rotateArm = new JoystickButton(gamepad, 3);
	engageWinch = new JoystickButton(op, OI_ENGAGE_WINCH_PORT);

	registerButtonListener();
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
}

double OI::getLeftStickY() {
#if USE_GAMEPAD
	return -gamepad->GetY()*fabs(gamepad->GetY());
#else
	return leftStick->GetY()*fabs(leftStick->GetY());
#endif
}

double OI::getRightStickY() {
#if USE_GAMEPAD
	return -gamepad->GetAxis(Joystick::AxisType::kThrottleAxis)*fabs(gamepad->GetAxis(Joystick::AxisType::kThrottleAxis));
#else
	return rightStick->GetY()*fabs(rightStick->GetY());
#endif
}

void OI::registerButtonListener()
{
	//portcullisBreach->WhenPressed(new PortcullisAuto(0.1, 0, 0));
	//change values later - Superior DeSilva)
	//chevalBreach->WhenPressed(new ChevDeFris(0.1, 0, 0));
	//change values later
	//generalBreach->WhenPressed(new GeneralBreach(0.1, 0));
	//collectBall->WhenPressed(new );
	//collectorUp->WhenPressed(new );
	//aimAtGoal->WhenPressed(new);
//	shootLow->WhenPressed(new);
	//shootHigh->WhenPressed(new);
//	spinUpShooter->WhenPressed(new);
//	attachHook->WhenPressed(new);
	//engageWinch->WhenPressed(new);
	rotateArm->WhenPressed(new RotateArm(CLIMBER_ARM_UP_POSITION));
	SmartDashboard::PutData("Climber Down", new RotateArm(CLIMBER_ARM_DOWN_POSITION));

	collectorDown->WhenPressed(new CollectorMove(1480));
	collectorUp->WhenPressed(new CollectorMove(0));
	collectBall->WhileHeld(new ActivateRollers(Collector::rollerDirection::KForward));
	shootLow->WhileHeld(new ActivateRollers(Collector::rollerDirection::KBackward));
}

bool OI::isJoystickButtonPressed(int control, int button)
{
	return false;
}
