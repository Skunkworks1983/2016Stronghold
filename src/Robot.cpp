#include <CameraServer.h>
#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/Turning/ArcTurn.h>
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
#include <Subsystems/Shooter.h>
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

	SmartDashboard::PutNumber("leftSpeed",
			CommandBase::shooter->getLeft()->PIDGet());
	SmartDashboard::PutNumber("rightSpeed",
			CommandBase::shooter->getRight()->PIDGet());
	SmartDashboard::PutNumber("time", GetFPGATime());

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
	Scheduler::GetInstance()->RemoveAll();
	LOG_INFO("AutonomousInit Called");

	SensorManager::getSensorManager()->ZeroYaw();
	AutoBase::readValues();

	cmd = AutoBase::getSelectedAuto();

	cmd->Start();

	//ArcTurn *turn = new ArcTurn(-90, -.75, -.5);
	//turn->Start();

	//GoToBatter *gotoBatter = new GoToBatter(eStartPos::four);
	//gotoBatter->Start();

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
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	//LOG_INFO("Gyro %f",	SensorManager::getSensorManager()->getSensor(SENSOR_GYRO_ID)->PIDGet());

//	LOG_INFO("Yaw %f Roll %f Pitch %f",
//			SensorManager::getSensorManager()->getYaw(),
//			SensorManager::getSensorManager()->getRoll(),
//			SensorManager::getSensorManager()->getPitch());
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

