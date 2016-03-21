#include <CommandBase.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/TurnDegree.h>
#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>

void Robot::RobotInit() {
	LOG_INFO("START OF NEW RUN \t START OF NEW RUN");
	LOG_INFO("RobotInit Called");
	MotorManager::getMotorManager();
	SensorManager::getSensorManager();
	MotorManager::getMotorManager()->initPIDS();

	CommandBase::init();

	//SensorManager::getSensorManager()->initGyro();

	//managePower = new ManagePower();
	//managePower->Start();

	//turnDegree = new TurnDegree(90);

	//StallProtection *stall = new StallProtection();
	//stall->Start();
	//acc = new BuiltInAccelerometer(Accelerometer::kRange_16G);

	//cmd = AutoBase::doLowBarandScore();
	LOG_INFO("END OF ROBOTINIT");
}

void Robot::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	//MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);
	//MotorManager::getMotorManager()->disablePID(PID_ID_TURN_DEGREE_RIGHT);

}

void Robot::DisabledPeriodic() {
}

void Robot::AutonomousInit() {
	CommandBase::drivebase->setDriverControl(false);
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("AutonomousInit Called");
	//turnDegree->Start();
	cmd = AutoBase::getSelectedAuto();

	cmd->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	//CommandBase::shooter->setShooterSpeed(1.0);
	//CommandBase::shooter->setRightShooterSpeed(.3);

	/*double left = SensorManager::getSensorManager()->getSensor(
	 SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
	 double right = SensorManager::getSensorManager()->getSensor(
	 SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet();

	 LOG_DEBUG("LeftEncoder %f, RightEncoder %f", left, right);*/

	//SmartDashboard::PutNumber("AbsoluteRollerEncoder", Sensor);
}

void Robot::TeleopInit() {
	CommandBase::drivebase->setDriverControl(true);
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("TeleOp Called");
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {

}

START_ROBOT_CLASS(Robot);

