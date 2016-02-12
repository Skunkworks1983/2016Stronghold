#include <Commands/ChevDeFris.h>
#include <Commands/GeneralBreach.h>
#include <Commands/PortcullisAuto.h>
#include <OI.h>
#include <Subsystems/Collector.h>
#include <cmath>
#include <cstdbool>

OI::OI()
{
	leftStick = new Joystick(OI_JOYSTICK_LEFT_PORT);
	rightStick = new Joystick(OI_JOYSTICK_RIGHT_PORT);
	op = new Joystick(OI_OPERATOR_PORT);

	//breaching
	portcullisBreach = new JoystickButton(op, OI_PORTCULLIS_BREACH_PORT);
	chevalBreach = new JoystickButton(op, OI_CHEVAL_BREACH_PORT);
	generalBreach = new JoystickButton(op, OI_GENERAL_BREACH_PORT);

	//collector
	collectBall = new JoystickButton(op, OI_COLLECT_BALL_PORT);
	collectorUp = new JoystickButton(op, OI_COLLECTOR_UP_PORT);

	//aiming
	aimAtGoal = new JoystickButton(op, OI_AIM_AT_GOAL_PORT);

	//shooting
	shootLow = new JoystickButton(op, OI_SHOOT_LOW_PORT);
	shootHigh = new JoystickButton(op, OI_SHOOT_HIGH_PORT);
	spinUpShooter = new JoystickButton(op, OI_SPIN_UP_SHOOTER_PORT);

	//climbing
	rotateArm = new JoystickButton(op, OI_ROTATE_ARM_PORT);
	engageWinch = new JoystickButton(op, OI_ENGAGE_WINCH_PORT);
}

OI::~OI() {
	delete leftStick;
	delete rightStick;
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

}

double OI::getLeftStickY() {
	return leftStick->GetY()*fabs(leftStick->GetY());
}

double OI::getRightStickY() {
	return rightStick->GetY()*fabs(rightStick->GetY());
}

void OI::registerButtonListener()
{
	portcullisBreach->WhenPressed(new PortcullisAuto(0.1, 0, 0));
	//change values later - Superior DeSilva)
	chevalBreach->WhenPressed(new ChevDeFris(0.1, 0, 0));
	//change values later
	generalBreach->WhenPressed(new GeneralBreach(0.1, 0));
	//collectBall->WhenPressed(new );
	//collectorUp->WhenPressed(new );
	//aimAtGoal->WhenPressed(new);
//	shootLow->WhenPressed(new);
	//shootHigh->WhenPressed(new);
//	spinUpShooter->WhenPressed(new);
//	attachHook->WhenPressed(new);
	//engageWinch->WhenPressed(new);

}

bool OI::isJoystickButtonPressed(int control, int button)
{
	return false;
}
