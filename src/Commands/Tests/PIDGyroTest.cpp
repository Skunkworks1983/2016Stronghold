#include <Commands/Tests/PIDGyroTest.h>
#include <PIDController.h>
#include <Subsystems/Drivebase.h>

PIDGyroTest::PIDGyroTest()
{
	degreeTurnRight = 30; //Can change to test different things
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();
	pidController = new PIDController(.005, 0, 0, this, this);
	pidController->SetInputRange(0, 360);
	pidController->SetContinuous(true);
	pidController->SetOutputRange(-1, 1);
	yawTurnTo = 0;
}

// Called just before this Command runs the first time
void PIDGyroTest::Initialize()
{
	yawTurnTo = sensorManager->getYaw() + (degreeTurnRight % 360);
	pidController->SetSetpoint(yawTurnTo);
}

// Called repeatedly when this Command is scheduled to run
void PIDGyroTest::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool PIDGyroTest::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PIDGyroTest::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDGyroTest::Interrupted()
{

}

double PIDGyroTest::PIDGet() {
	return sensorManager->getYaw();
}

void PIDGyroTest::PIDWrite(float output) {
	drivebase->setLeftSpeed(output);
	drivebase->setRightSpeed(-output);
} //When we create the PID controller, we are going to need to set the input range from 0 to 360, and then we are going to need to call "setContinuous(true);" and set the output range from -1 to 1
