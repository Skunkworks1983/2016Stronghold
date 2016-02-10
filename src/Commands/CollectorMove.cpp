#include "CollectorMove.h"

CollectorMove::CollectorMove(int target)
{
	P = 0.0075;
	I = 0; //TODO: Tune for competition robot, currently tuned to totebot sorta
	D = 0;
	this->degree = degree;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID
	sensorManager = SensorManager::getSensorManager();
	pidController = new PIDController(P, I, D, this, this);
	motorManager = MotorManager::getMotorManager();
	pidController->SetAbsoluteTolerance(5.0f);
	this->target = target;
	initialCollectorPosition = collector->getRotatorPosition();
	pidController->SetContinuous(true);
	pidController->SetInputRange(-2147483648, 2147483647); //takes 38 hours to overflow, but worth it
}

void CollectorMove::Initialize()
{

}

void CollectorMove::Execute()
{
	pidController->SetSetpoint(target);
	pidController->Enable();


	}

double CollectorMove::PIDGet() {
	return (collector->getRotatorPosition() - initialCollectorPosition);
}

void CollectorMove::PIDWrite(float output) {
	collector->setRotatorSpeed(output);
}

bool CollectorMove::IsFinished()
{
	return pidController->OnTarget();
}

void CollectorMove::End()
{

	collector->setRotatorSpeed(0.0);
	pidController->Disable();
}


void CollectorMove::Interrupted()
{

}
