#include <Commands/Shooting/PIDShot.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterMotor.h>
#include <cmath>
#include <cstdio>

#define SHOT_TOLERANCE .15

PIDShot::PIDShot(double leftSpeed, double rightSpeed) :
		leftSpeed(leftSpeed), rightSpeed(rightSpeed) {
	double p = .0024;	//works = .0018
	double i = 0.0;		//works = 0.0
	double d = 0.0006;	//works = 0.0
	left = new ShooterMotor(ShooterMotor::LEFT, p, i, d);
	right = new ShooterMotor(ShooterMotor::RIGHT, p, i, d);
}

// Called just before this Command runs the first time
void PIDShot::Initialize() {
	char str[1024];
	sprintf(str, "PIDShot Initialize called");
	Logger::getLogger()->log(str, Info);
	right->SetSetpoint(rightSpeed);
	left->SetSetpoint(leftSpeed);

	left->Enable();
	right->Enable();
}

// Called repeatedly when this Command is scheduled to run
void PIDShot::Execute() {
	/*char str[1024];
	 sprintf(str, "PIDShot target %f leftSpeed %f rightSpeed %f", speed,
	 shooter->getLeftShooterSpeed(), shooter->getRightShooterSpeed());
	 Logger::getLogger()->log(str, Info);*/

	const bool leftOnTarget = fabs(left->PIDGet() - leftSpeed) < SHOT_TOLERANCE;
	const bool rightOnTarget = fabs(
			right->PIDGet() - rightSpeed) < SHOT_TOLERANCE;

	if (leftOnTarget && rightOnTarget) {
		c++;
	} else {
		c = 0;
	}

	if (c > 15) {
		shooter->setUpToSpeed(true);
	} else {
		shooter->setUpToSpeed(false);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PIDShot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PIDShot::End() {
	char str[1024];
	sprintf(str, "PIDShot End called");
	Logger::getLogger()->log(str, Info);

	shooter->setShooterSpeed(0.0);
	left->Disable();
	right->Disable();
	left->Reset();
	right->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDShot::Interrupted() {
	End();
}
