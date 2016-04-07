#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Power/StallProtection.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <Utility.h>
#include <cstdbool>

uint64_t Robot::teleStart = 0;
uint64_t Robot::autoStart = 0;

void Robot::RobotInit() {
	LOG_INFO("START OF NEW RUN \t START OF NEW RUN");
	LOG_INFO("RobotInit Called");
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();
	//FollowerHandler::getInstance()->startup();

	MotorManager::getMotorManager()->initPIDS();

	CommandBase::init();

	SensorManager::getSensorManager()->initGyro();
	CameraReader::getCameraReader()->startUp();
	//managePower = new ManagePower();
	//managePower->Start();

	StallProtection *stall = new StallProtection();
	stall->Start();

	//cmd = AutoBase::doLowBarandScore();


	LOG_INFO("END OF ROBOTINIT");
}

void Robot::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);
	//MotorManager::getMotorManager()->disablePID(PID_ID_TURN_DEGREE_RIGHT);
}

void Robot::DisabledPeriodic() {

}

void Robot::AutonomousInit() {
	CommandBase::drivebase->setDriverControl(false);
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("AutonomousInit Called");
	//turnDegree->Start();
	SensorManager::getSensorManager()->ZeroYaw();
	AutoBase::readValues();
	cmd = AutoBase::getSelectedAuto();
	//cmd = AutoBase::doRoughT();

	cmd->Start();

	oldTime = GetFPGATime();
	autoStart = GetFPGATime();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	//LOG_INFO("Autonomous TimeDiff = %ud", GetFPGATime() - oldTime);

	oldTime = GetFPGATime();

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
	teleStart = GetFPGATime();
	CameraReader::getCameraReader()->tele = true;
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {

}

uint64_t Robot::getAutoStartTime() {
	return autoStart;
}

uint64_t Robot::getTeleStartTime() {
	return teleStart;
}

START_ROBOT_CLASS(Robot);

