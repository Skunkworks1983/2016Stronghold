#include <assert.h>
#include <CANTalon.h>
#include <DriverStation.h>
#include <PIDSource.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <cmath>
#include <cstdio>
#include <iterator>

MotorManager::MotorManager() {
	allowedPriority = PRIORITY_ACCESSORIES;
	char str[1024];
	sprintf(str, "MotorManager Constructor #%u", count++);
	writeToLogFile(LOGFILE_NAME, str);

#if USE_DRIVEBASE
	initDriveBase();
#endif
#if USE_COLLECTOR
	initCollector();
#endif
#if USE_CLIMBER
	initClimber();
#endif
#if USE_SHOOTER
	initShooter();
#endif
}

void MotorManager::initClimber() {
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_ARM_MOTOR_PORT,
	RS775_MAX_CURRENT, ARM);

	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_1_PORT,
	RS775_MAX_CURRENT, WINCH, true);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_2_PORT,
	RS775_MAX_CURRENT, WINCH, true);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_3_PORT,
	RS775_MAX_CURRENT, WINCH, true);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_4_PORT,
	RS775_MAX_CURRENT, WINCH, true);
}

void MotorManager::initDriveBase() {
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_1_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_2_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_3_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_1_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_2_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_3_PORT,
	CIM_MAX_CURRENT, DRIVEBASE);

	char str[1024];
	sprintf(str, "Created DriveBase Motors");
	writeToLogFile(LOGFILE_NAME, str);
}

void MotorManager::initShooter() {
	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_1_PORT,
	MINI_CIM_MAX_CURRENT, SHOOTER);
	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_2_PORT,
	MINI_CIM_MAX_CURRENT, SHOOTER);
}

void MotorManager::initCollector() {
	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS,
	COLLECTOR_ROLLER_MOTOR_1_PORT, RS775_MAX_CURRENT, ROLLER);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS,
	COLLECTOR_ROTATOR_MOTOR_LEFT_PORT, RS775_MAX_CURRENT, COLLECTOR_ROTATOR,
	false);
	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS,
	COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT, RS775_MAX_CURRENT, COLLECTOR_ROTATOR,
	true);
}

void MotorManager::initPIDS() {
#if USE_COLLECTOR
	std::vector<Motor*> rotationCollectorMotors;
	rotationCollectorMotors.push_back(
			getMotor(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT));
	rotationCollectorMotors.push_back(
			getMotor(COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT));

	MotorGroup * groupCollectorRotation = new MotorGroup(
			rotationCollectorMotors);
	createPID(groupCollectorRotation, SENSOR_COLLECTOR_ROTATION_ENCODER_ID,
	PID_ID_COLLECTOR,
	COLLECTOR_ROTATION_P, COLLECTOR_ROTATION_I, COLLECTOR_ROTATION_D,
	COLLECTOR_ROTATION_F, false);
	/*
	 std::vector<Motor*> rollerMotors;
	 rollerMotors.push_back(getMotor(COLLECTOR_ROLLER_MOTOR_1_PORT));

	 MotorGroup * groupRoller = new MotorGroup(rollerMotors);
	 createPID(groupRoller, COLLECTOR_ROLLER_ENCODER_PORT, PID_ID_ROLLER, 0.0075,
	 0, 0, 0, true);*/

#endif
#if USE_DRIVEBASE

	/*std::vector<Motor*> DrivebaseLeftMotors;
	 DrivebaseLeftMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_1_PORT));
	 DrivebaseLeftMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_2_PORT));
	 DrivebaseLeftMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_3_PORT));
	 MotorGroup * groupDrivebaseLeft = new MotorGroup(DrivebaseLeftMotors);
	 createPID(groupDrivebaseLeft, SENSOR_DRIVE_BASE_LEFT_ENCODER_ID,
	 PID_ID_DRIVEBASE_LEFT,
	 DRIVEBASE_LEFT_P, DRIVEBASE_LEFT_I, DRIVEBASE_LEFT_D,
	 DRIVEBASE_LEFT_F, false);

	 std::vector<Motor*> DrivebaseRightMotors;
	 DrivebaseRightMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_1_PORT));
	 DrivebaseRightMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_2_PORT));
	 DrivebaseRightMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_3_PORT));
	 MotorGroup * groupDrivebaseRight = new MotorGroup(DrivebaseRightMotors);

	 createPID(groupDrivebaseRight, SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID,
	 PID_ID_DRIVEBASE_RIGHT,
	 DRIVEBASE_RIGHT_P, DRIVEBASE_RIGHT_I, DRIVEBASE_RIGHT_D,
	 DRIVEBASE_RIGHT_F, false);*/

#if USE_GYRO
	MotorGroup * groupGyroTurnMotors = new MotorGroup(driveBaseMotors);
	createPID(groupGyroTurnMotors, SENSOR_GYRO_ID, PID_ID_TURN_DEGREE,
			TURN_GYRO_P, TURN_GYRO_I, TURN_GYRO_D, TURN_GYRO_F, false);
#endif

#if USE_CAMERA
	MotorGroup * groupCamera = new MotorGroup(driveBaseMotors);
	createPID(groupCamera, SENSOR_CAMERA_ID, PID_ID_CAMERA,
			MOVE_TOWARD_CAMERA_P,
			MOVE_TOWARD_CAMERA_I, MOVE_TOWARD_CAMERA_D, MOVE_TOWARD_CAMERA_F,
			false);
#endif

#endif
#if USE_CLIMBER
	std::vector<Motor*> winchMotors;
	winchMotors.push_back(getMotor(CLIMBER_WINCH_MOTOR_1_PORT));
	winchMotors.push_back(getMotor(CLIMBER_WINCH_MOTOR_2_PORT));
	winchMotors.push_back(getMotor(CLIMBER_WINCH_MOTOR_3_PORT));
	winchMotors.push_back(getMotor(CLIMBER_WINCH_MOTOR_4_PORT));
	MotorGroup * winchMotorGroup = new MotorGroup(winchMotors);
	createPID(winchMotorGroup, SENSOR_CLIMBER_WINCH_ENCODER, PID_ID_WINCH,
			CLIMBER_WINCH_P, CLIMBER_WINCH_I, CLIMBER_WINCH_D, CLIMBER_WINCH_F, false);

	std::vector<Motor*> armMotors;
	armMotors.push_back(getMotor(CLIMBER_ARM_MOTOR_PORT));
	MotorGroup * groupArmMotors = new MotorGroup(armMotors);
	double p = 0.000014;
	//double p = .00007;
	double i = 0.000004;
	double d = 0.00005;
	double f = 0;
	createPID(groupArmMotors, SENSOR_CLIMBER_ARM_ENCODER, PID_ID_ARM, p, i, d,
			f, false);
	//createPID(groupArmMotors, SENSOR_CLIMBER_ARM_ENCODER, PID_ID_ARM, CLIMBER_ARM_P, CLIMBER_ARM_I, CLIMBER_ARM_D, CLIMBER_ARM_F, false);
#endif
#if USE_SHOOTER
	std::vector<Motor*> shooterMotor1;
	shooterMotor1.push_back(getMotor(SHOOTER_MOTOR_1_PORT));
	MotorGroup * groupShooterMotor1 = new MotorGroup(shooterMotor1);
	createPID(groupShooterMotor1, SHOOTER_1_ENCODER_PORT, PID_ID_SHOOTER_1,
			SHOOTER_1_P, SHOOTER_1_I, SHOOTER_1_D, SHOOTER_1_F, false);

	std::vector<Motor*> shooterMotor2;
	shooterMotor2.push_back(getMotor(SHOOTER_MOTOR_2_PORT));
	MotorGroup * groupShooterMotor2 = new MotorGroup(shooterMotor2);
	createPID(groupShooterMotor2, SHOOTER_2_ENCODER_PORT, PID_ID_SHOOTER_2,
			SHOOTER_2_P, SHOOTER_2_I, SHOOTER_2_D, SHOOTER_2_F, false);
#endif
}

Motor * MotorManager::getMotor(unsigned ID) {
	if (ID < 0 || motors.count(ID) < 1) {
		char str[1024];
		sprintf(str, "Null motor at ID %u", ID);
		writeToLogFile(LOGFILE_NAME, str);
		return NULL;
	}
	//char str[1024];
	//sprintf(str, "Returning getMotor(%u)", ID);
	//writeToLogFile(LOGFILE_NAME, str);
	return motors[ID];
}

MotorManager::~MotorManager() {
	for (unsigned i = 0; i < motors.size(); i++) {
		delete motors[i];
	}
}

void MotorManager::setPosition(unsigned pidID, float position) {

}

void MotorManager::resetPID(unsigned ID){
	pidControllerMap[ID]->Reset();
}

void MotorManager::setSpeed(unsigned ID, float speed) {
	if (motors[ID]->stoppedStartTime == 0) {

		if (motors[ID]->isReversed()) {
			speed = -speed;
		}
		motors[ID]->speed = speed;

		if (motors[ID]->talon != NULL) {
			if (motors[ID]->motorPriority >= allowedPriority) {
				motors[ID]->talon->Set(speed * motors[ID]->C);
			} else {
				motors[ID]->talon->Set(speed);
			}
		}

	}
}

void MotorManager::setSpeedForAll() {
	std::map<unsigned, Motor*>::iterator ptr = motors.begin();
	std::map<unsigned, Motor*>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		setSpeed((*ptr).second->port, (*ptr).second->speed);
	}
}

void MotorManager::setPID(unsigned ID, double P, double I, double D) {
	if (motors[ID]->talon != NULL) {
		motors[ID]->talon->SetPID(P, I, D);
	} else {

	}
}

double MotorManager::GetPosition(unsigned ID) {
	if (motors[ID]->talon != NULL) {
		return this->motors[ID]->talon->GetEncPosition();
	} else {
		return 0.0;
	}
}

double MotorManager::GetSpeed(unsigned ID) {
	if (motors[ID]->talon != NULL) {
		return this->motors[ID]->talon->GetSpeed();
	} else {
		return 0.0;
	}
}

void MotorManager::setPriority(Priority priorityArg) {

	std::map<unsigned, Motor*>::iterator ptr = motors.begin();

	allowedPriority = priorityArg;

	for (; ptr != motors.end(); ++ptr) {
		if ((*ptr).second->talon != NULL) {

			if ((*ptr).second->motorPriority > priorityArg) {
				(*ptr).second->talon->Set(0);
			} else {
				(*ptr).second->talon->Set((*ptr).second->speed);
			}
		}
	}

}

void Motor::setC(Priority priorityArg, float voltage) {

	if (motorPriority == PRIORITY_FIRST) {
		if (voltage > POWER_BROWNOUT_VOLTAGE + POWER_DRIVEBASE_VOLTAGE_WIDTH) {
			this->C = 1;
		} else {
			this->C = pow(
					(((voltage - POWER_BROWNOUT_VOLTAGE)
							/ (POWER_DRIVEBASE_VOLTAGE_WIDTH))), 2);
		}
	} else if (this->motorPriority >= priorityArg) {
		this->C = pow(
				(((voltage - POWER_BROWNOUT_VOLTAGE)
						/ (motorPriority * POWER_VOLTAGE_WIDTH))), 2);
	}

}

void MotorManager::setCForAll() {
	std::map<unsigned, Motor*>::iterator ptr = motors.begin();
	std::map<unsigned, Motor*>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		(*ptr).second->setC(allowedPriority,
				DriverStation::GetInstance().GetBatteryVoltage());
	}

}

MotorManager * MotorManager::getMotorManager() {
	static MotorManager *motorManager = NULL;
	if (motorManager == NULL) {
		motorManager = new MotorManager();
	}
	return motorManager;
}

void MotorManager::addMotor(Priority priority, int Port, float maxCurrent,
		ESubsystem parentSubsystem, bool reversed) {
	Motor * motor = new Motor(priority, Port, maxCurrent, parentSubsystem,
			reversed);
	motors.insert(std::pair<int, Motor*>(Port, motor));
}

Motor::Motor(Priority prioArg, int portArg, float maxCurrent,
		ESubsystem parentSubsystem, bool reversed) :
		reversed(reversed), maxCurrent(maxCurrent), parentSubsystem(
				parentSubsystem) {
	overCurrentStartTime = 0;
	stoppedStartTime = 0;
	port = portArg;
	speed = 0;
	motorPriority = prioArg;

	if (SensorBase::CheckPWMChannel(port)) {	//TODO: make sure this works
		talon = new CANTalon(port);
	} else {
		char str[1024];
		sprintf(str, "Talon assignment failed on Port %d", port);
		writeToLogFile(LOGFILE_NAME, str);
	}
	C = 1;
}

bool Motor::isReversed() {
	return reversed;
}

Motor::~Motor() {

}

void MotorManager::createPID(MotorGroup * group, unsigned PIDSourceID,
		unsigned pidID, float P, float I, float D, float F, bool isSpeedMode) {

	if (pidControllerMap.count(pidID) == 0) {
		Sensor * sensor = SensorManager::getSensorManager()->getSensor(
				PIDSourceID);
		PIDController * pidcontroller = new PIDController(P, I, D, F, sensor,
				group);
		if (sensor->getLowRange() != sensor->getHighRange()) {
			pidcontroller->SetInputRange(sensor->getLowRange(),
					sensor->getHighRange());
		}
		pidcontroller->SetOutputRange(-1, 1);
		if (isSpeedMode == true) {
			pidcontroller->SetPIDSourceType(PIDSourceType::kRate);
		} else {
			pidcontroller->SetPIDSourceType(PIDSourceType::kDisplacement);
			pidControllerMap[pidID] = pidcontroller;
		}
	} else {
		//pidControllerMap[pidID]->Enable();
	}
}

void MotorManager::setPIDF(unsigned pidID, float P, float I, float D, float F) {
	pidControllerMap[pidID]->SetPID(P, I, D, F);
}

void MotorManager::enablePID(unsigned pidID, float setPoint) {
	pidControllerMap[pidID]->SetSetpoint(setPoint);
	pidControllerMap[pidID]->Enable();
}

void MotorManager::enablePID(unsigned pidID) {
	pidControllerMap[pidID]->Enable();
}

void MotorManager::disablePID(unsigned pidID) {
	pidControllerMap[pidID]->Disable();
}
MotorGroup::MotorGroup(std::vector<Motor*> motorgroup) {
	this->motorList = motorgroup;
}

MotorGroup::~MotorGroup() {
	for (unsigned i = 0; i < motorList.size(); i++) {
		delete motorList[i];
	}
	delete &motorList;
}

void MotorGroup::PIDWrite(float output) {
	std::vector<Motor*>::iterator it = motorList.begin();

	for (; it != motorList.end(); ++it) {
		/*if ((*it)->stoppedStartTime == 0) {
		 (*it)->talon->Set(output * (*it)->C);
		 }
		 (*it)->speed = output;*/
		if ((*it)->talon != NULL) {
			(*it)->talon->Set(
					((*it)->isReversed() ? -1 : 1) * output * (*it)->C);
		}
	}
}
