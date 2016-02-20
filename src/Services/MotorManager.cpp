#include <CANTalon.h>
#include <DriverStation.h>
#include <PIDSource.h>
#include <stddef.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <TuningValues.h>
#include <RobotMap.h>
#include <cmath>
#include <iterator>

MotorManager::MotorManager(){
	allowedPriority = PRIORITY_ACCESSORIES;

	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_1_PORT, CIM_MAX_CURRENT, DRIVEBASE); //Motors will not stall protect agains
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_2_PORT, CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_3_PORT, CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_1_PORT, CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_2_PORT, CIM_MAX_CURRENT, DRIVEBASE);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_3_PORT, CIM_MAX_CURRENT, DRIVEBASE);

	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_1_PORT, RS775_MAX_CURRENT, WINCH);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_2_PORT, RS775_MAX_CURRENT, WINCH);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_3_PORT, RS775_MAX_CURRENT, WINCH);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_WINCH_MOTOR_4_PORT, RS775_MAX_CURRENT, WINCH);

	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_ARM_MOTOR_PORT, RS775_MAX_CURRENT, ARM);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, COLLECTOR_ROTATOR_MOTOR_1_PORT, RS775_MAX_CURRENT, COLLECTOR_ROTATOR);
	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, COLLECTOR_ROTATOR_MOTOR_2_PORT, RS775_MAX_CURRENT, COLLECTOR_ROTATOR);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, COLLECTOR_ROLLER_MOTOR_1_PORT, RS775_MAX_CURRENT, ROLLER);

	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_1_PORT, MINI_CIM_MAX_CURRENT, SHOOTER);
	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_2_PORT, MINI_CIM_MAX_CURRENT, SHOOTER);

	std::vector<Motor*> RotationCollectorMotors = std::vector<Motor*>();
	RotationCollectorMotors.push_back(getMotor(COLLECTOR_ROTATOR_MOTOR_1_PORT));
	RotationCollectorMotors.push_back(getMotor(COLLECTOR_ROTATOR_MOTOR_2_PORT));
	MotorGroup * groupCollectorRotation = new MotorGroup(
			RotationCollectorMotors);
	createPID(groupCollectorRotation, SENSOR_COLLECTOR_ROTATION_ENCODER_ID, PID_ID_COLLECTOR,
			COLLECTOR_ROTATION_P, COLLECTOR_ROTATION_I, COLLECTOR_ROTATION_D,
			COLLECTOR_ROTATION_F, false);

	std::vector<Motor*> RollerMotors = std::vector<Motor*>();
	RollerMotors.push_back(getMotor(COLLECTOR_ROLLER_MOTOR_1_PORT));
	MotorGroup * groupRoller = new MotorGroup(RollerMotors);
	createPID(groupRoller, COLLECTOR_ROLLER_ENCODER_PORT, PID_ID_ROLLER, 0.0075,0,0,0,true);

	std::vector<Motor*> ShooterMotor1 = std::vector<Motor*>();
	ShooterMotor1.push_back(getMotor(SHOOTER_MOTOR_1_PORT));
	MotorGroup * groupShooterMotor1 = new MotorGroup(ShooterMotor1);
	createPID(groupShooterMotor1, SHOOTER_1_ENCODER_PORT, PID_ID_SHOOTER_1,
			SHOOTER_1_P, SHOOTER_1_I, SHOOTER_1_D, SHOOTER_1_F, false);

	std::vector<Motor*> ShooterMotor2 = std::vector<Motor*>();
	ShooterMotor2.push_back(getMotor(SHOOTER_MOTOR_2_PORT));
	MotorGroup * groupShooterMotor2 = new MotorGroup(ShooterMotor2);
	createPID(groupShooterMotor2, SHOOTER_2_ENCODER_PORT, PID_ID_SHOOTER_2,
			SHOOTER_2_P, SHOOTER_2_I, SHOOTER_2_D, SHOOTER_2_F, false);

	std::vector<Motor*> driveBaseMotors = std::vector<Motor*>();
	driveBaseMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_1_PORT));
	driveBaseMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_2_PORT));
	driveBaseMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_3_PORT));
	driveBaseMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_1_PORT));
	driveBaseMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_2_PORT));
	driveBaseMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_3_PORT));
	MotorGroup * groupGyroTurnMotors = new MotorGroup(driveBaseMotors);
	createPID(groupGyroTurnMotors, SENSOR_GYRO_ID, PID_ID_TURN_DEGREE,
			TURN_GYRO_P, TURN_GYRO_I, TURN_GYRO_D, TURN_GYRO_F, false);

	MotorGroup * groupCamara = new MotorGroup(driveBaseMotors);
	createPID(groupCamara, SENSOR_CAMERA_ID, PID_ID_CAMERA, MOVE_TOWARD_CAMERA_P,
			MOVE_TOWARD_CAMERA_I, MOVE_TOWARD_CAMERA_D, MOVE_TOWARD_CAMERA_F, false);

}

Motor *MotorManager::getMotor(unsigned ID) {
	if (ID < 0 || ID >= motors.size()) {
		return NULL;
	}
	return motors[ID];
}

MotorManager::~MotorManager() {
	for (unsigned i = 0; i < motors.size(); i++) {
		delete motors[i];
	}
}

void MotorManager::setPosition(unsigned pidID, float position) {

}

void MotorManager::setSpeed(unsigned ID, float speed) {
	if(motors[ID]->stoppedStartTime == 0) {
		std::vector<Motor*>::iterator ptr = motors.begin();

		for (; ptr != motors.end(); ++ptr) {
			if ((*ptr)->port == ID) {
				(*ptr)->speed = speed;

				if ((*ptr)->motorPriority >= allowedPriority) {
					(*ptr)->talon->Set(speed * (*ptr)->C);
				} else {
					(*ptr)->talon->Set(speed);
				}
				break;
			}
		}
	}
}
void MotorManager::setSpeedForAll() {
	std::vector<Motor*>::iterator ptr = motors.begin();
	std::vector<Motor*>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		setSpeed((*ptr)->port, (*ptr)->speed);
	}
}

void MotorManager::setPID(unsigned ID, double P, double I, double D) {
	motors[ID]->talon->SetPID(P, I, D);
}

double MotorManager::GetPosition(unsigned ID) {
	return this->motors[ID]->talon->GetEncPosition();
}

double MotorManager::GetSpeed(unsigned ID) {
	return this->motors[ID]->talon->GetSpeed();
}

void MotorManager::setPriority(Priority priorityArg) {

	std::vector<Motor*>::iterator ptr = motors.begin();
	std::vector<Motor*>::iterator end = motors.end();

	allowedPriority = priorityArg;

	for (; ptr != end; ++ptr) {
		if ((*ptr)->motorPriority > priorityArg) {
			(*ptr)->talon->Set(0);
		} else {
			(*ptr)->talon->Set((*ptr)->speed);
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
	std::vector<Motor*>::iterator ptr = motors.begin();
	std::vector<Motor*>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		(*ptr)->setC(allowedPriority,
				DriverStation::GetInstance().GetBatteryVoltage());
	}

}

MotorManager * MotorManager::getMotorManager() {
	static MotorManager motorManager;
	return &motorManager;
}

void MotorManager::addMotor(Priority priority, int Port, float maxCurrent, ESubsystem parentSubsystem) {
	Motor * motor = new Motor(priority, Port, maxCurrent, parentSubsystem);
	motors.push_back(motor);
}

Motor::Motor(Priority prioArg, int portArg, float maxCurrent, ESubsystem parentSubsystem) {
	this->maxCurrent = maxCurrent;
	this->parentSubsystem = parentSubsystem;
	overCurrentStartTime = 0;
	stoppedStartTime = 0;
	port = portArg;
	speed = 0;
	motorPriority = prioArg;
	talon = new CANTalon(port);
	C = 1;
}

Motor::~Motor() {

}

void MotorManager::createPID(MotorGroup * group, unsigned PIDSourceID, unsigned pidID,
		float P, float I, float D, float F, bool isSpeedMode) {

	if (pidControllerMap.count(pidID) < 1) {
		PIDController * pidcontroller = new PIDController(P, I, D, F,
				SensorManager::getSensorManager()->getSensor(PIDSourceID), group);
		if (isSpeedMode == true) {
			pidcontroller->SetPIDSourceType(PIDSourceType::kRate);
		} else {
			pidcontroller->SetPIDSourceType(PIDSourceType::kDisplacement);
			pidControllerMap[pidID] = pidcontroller;
		}
	} else {
		pidControllerMap[pidID]->Enable();
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

MotorGroup::~MotorGroup(){
	for(unsigned i = 0; i < motorList.size(); i++){
		delete motorList[i];
	}
	delete &motorList;
}


void MotorGroup::PIDWrite(float output) {
	for (unsigned i = 0; i < motorList.size(); i++) {
		if(motorList[i]->stoppedStartTime == 0) {
			motorList[i]->talon->Set(output * motorList[i]->C);
		}
		motorList[i]->speed = output;
	}
}
