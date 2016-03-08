#include <Commands/Climbing/MoveServo.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Climber.h>
#include <TuningValues.h>
#include <cmath>

MoveServo::MoveServo(eServoPosition pos) :
		CommandBase("MoveServo"), pos(pos) {
	Requires(climber);
	SetTimeout(.5);
}

void MoveServo::Initialize() {
	SmartDashboard::PutBoolean("MoveServoRunning", true);
	switch (pos) {
	case IN:
		climber->setServoAngle(CLIMBER_SERVO_IN_ANGLE);
		break;
	case OUT:
		climber->setServoAngle(CLIMBER_SERVO_OUT_ANGLE);
		break;
	}
}

void MoveServo::Execute() {
	SmartDashboard::PutNumber("MoveServoAngle", climber->getServoAngle());
}

bool MoveServo::IsFinished() {
	/*switch (pos) {
	case IN:
		return fabs(climber->getServoAngle() - CLIMBER_SERVO_IN_ANGLE) < 5;
	case OUT:
		return fabs(climber->getServoAngle() - CLIMBER_SERVO_OUT_ANGLE) < 5;
	}*/
	return IsTimedOut();
}

void MoveServo::End() {
	SmartDashboard::PutBoolean("MoveServoRunning", false);
}

void MoveServo::Interrupted() {
	End();
}

