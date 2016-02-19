#include <Commands/ManagePower.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>

void Robot::RobotInit() {
	SensorManager::getSensorManager();
	MotorManager::getMotorManager();
	//SensorManager::getSensorManager()->initGyro();
	CommandBase::init();
	//lw = LiveWindow::GetInstance();
	managePower = new ManagePower();
	managePower->Start();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);

