#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/Power/StallProtection.h>
#include <Commands/Scheduler.h>
#include <Robot.h>
#include <RobotBase.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Services/ShooterMotor.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>
#include <Subsystems/Shooter.h>
#include <TuningValues.h>
#include <Utility.h>
#include <cstdbool>

#include "../navx-mxp/cpp/include/AHRS.h"

uint64_t Robot::teleStart = 0;
uint64_t Robot::autoStart = 0;

void Robot::RobotInit() {
	LOG_INFO("START OF NEW RUN \t START OF NEW RUN");
	LOG_INFO("RobotInit Called");
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	MotorManager::getMotorManager()->initPIDS();

	CommandBase::init();

	SensorManager::getSensorManager()->initGyro();
	CameraReader::getCameraReader()->startUp();
	//managePower = new ManagePower();
	//managePower->Start();

	StallProtection *stall = new StallProtection();
	stall->Start();

	//CameraServer::GetInstance()->SetQuality(50);
	//std::shared_ptr<USBCamera> camera(new USBCamera("cam0", false));

	//camera->SetBrightness(50);
	//camera->SetExposureManual(50);

	//CameraServer::GetInstance()->StartAutomaticCapture("cam0");

	SensorManager::getSensorManager()->getGyro()->ZeroYaw();
	SensorManager::getSensorManager()->getGyro()->Reset();

	AutoBase::readValues();
	LOG_INFO("END OF ROBOTINIT");
}

void Robot::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
	MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);

	CommandBase::drivebase->setLeftSpeed(0.0);
	CommandBase::drivebase->setRightSpeed(0.0);

	CommandBase::shooter->turnOnLight(false);
}

void Robot::DisabledPeriodic() {

}

void Robot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("AutonomousInit Called");

	CommandBase::drivebase->setBrakeMode(true);

	MotorManager::getMotorManager()->disablePID(PID_ID_DRIVEBASE_ROT);

	//actually reset the gyro
	SensorManager::getSensorManager()->getGyro()->ZeroYaw();
	SensorManager::getSensorManager()->getGyro()->Reset();
	AutoBase::readValues();

	cmd = AutoBase::getSelectedAuto();
	cmd->Start();

	//GoToBatter *gotoBatter = new GoToBatter();
	//gotoBatter->Start();

	//	PIDTurn *turn = new PIDTurn(180,false);
	//	turn->Start();

	//	DriveTowardsTower *tower = new DriveTowardsTower(-.3, .08);
	//	tower->Start();

	//	HoldAgainstTower *tower = new HoldAgainstTower(.1);
	//	tower->Start();

	//DriveForwardStraight *driveForward = new DriveForwardStraight(9, .3);
	//driveForward->Start();

	oldTime = GetFPGATime();
	autoStart = GetFPGATime();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	oldTime = GetFPGATime();
}

void Robot::TeleopInit() {
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("TeleOp Called");
	teleStart = GetFPGATime();
	CameraReader::getCameraReader()->tele = true;
	CommandBase::drivebase->setBrakeMode(false);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	SmartDashboard::PutNumber("GyroAngle",
			SensorManager::getSensorManager()->getAngle());

	//LOG_INFO("GyroAngle %f",	SensorManager::getSensorManager()->getAngle());

	/*LOG_INFO("X %f Y %f Z %f worldX %f worldY %f worldZ %f",
			SensorManager::getSensorManager()->getRawX(),
			SensorManager::getSensorManager()->getRawY(),
			SensorManager::getSensorManager()->getRawZ(),
			SensorManager::getSensorManager()->GetAccelX(),
			SensorManager::getSensorManager()->GetAccelY(),
			SensorManager::getSensorManager()->GetAccelZ());*/
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

