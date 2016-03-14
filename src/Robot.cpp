#include <CommandBase.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cstdio>

void Robot::RobotInit() {
	char startup[1024];
	sprintf(startup, "START OF NEW RUN \t START OF NEW RUN");
	Logger::getLogger()->log(startup, Info);
	char str[1024];
	sprintf(str, "RobotInit Called");
	Logger::getLogger()->log(str, Info);
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
	//cmd = AutoBase::getSelectedAuto();
	cmd = AutoBase::doLowBarandScore();
	sprintf(str, "END OF ROBOTINIT");
	Logger::getLogger()->log(str, Info);
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
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "AutonomousInit Called");
	Logger::getLogger()->log(str, Info);
	//turnDegree->Start();
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

	 char str[1024];
	 sprintf(str, "LeftEncoder %f, RightEncoder %f", left, right);
	 Logger::getLogger()->log(str, Debug);*/

	//SmartDashboard::PutNumber("AbsoluteRollerEncoder", Sensor);
}

void Robot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	char str[1024];
	sprintf(str, "TeleOp Called");
	Logger::getLogger()->log(str, Info);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {

}

START_ROBOT_CLASS(Robot);

