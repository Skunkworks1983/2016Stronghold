#include "MotorManager.h"
#include "../RobotMap.h"
#include "WPILib.h"

MotorManager::MotorManager() :
		Subsystem("MotorManager") {
	allowedPriority = PRIORITY_ACCESSORIES;

	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_1_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_2_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_LEFTMOTOR_3_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_1_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_2_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, DRIVEBASE_RIGHTMOTOR_3_PORT);

	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_PULLY_MOTOR_1_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_PULLY_MOTOR_2_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_PULLY_MOTOR_3_PORT);
	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_PULLY_MOTOR_4_PORT);

	addMotor(Priority::PRIORITY_DRIVEBASE, CLIMBER_ARM_MOTOR_PORT);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, MULTI_TOOL_MOTOR_1_PORT);
	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, MULTI_TOOL_MOTOR_2_PORT);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, COLLECTOR_MOTOR_PORT);

	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_1_PORT);
	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_2_PORT);

	std::vector<Motor*> RotationCollectorMotors = std::vector<Motor*>();
	RotationCollectorMotors.push_back(getMotor(MULTI_TOOL_MOTOR_1_PORT));
	RotationCollectorMotors.push_back(getMotor(MULTI_TOOL_MOTOR_2_PORT));
	MotorGroup * groupCollectorRotation = new MotorGroup(
			RotationCollectorMotors);
	createPID(groupCollectorRotation, COLLECTOR_ENCODER_PORT, PID_ID_COLLECTOR,
			COLLECTOR_ROTATION_P, COLLECTOR_ROTATION_I, COLLECTOR_ROTATION_D,
			COLLECTOR_ROTATION_F, false);

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

	std::vector<Motor*> GyroTurnMotors = std::vector<Motor*>();
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_1_PORT));
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_2_PORT));
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_3_PORT));
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_1_PORT));
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_2_PORT));
	GyroTurnMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_3_PORT));
	MotorGroup * groupGyroTurnMotors = new MotorGroup(GyroTurnMotors);
	createPID(groupGyroTurnMotors, DRIVEBASE_ENCODER_1, PID_ID_TURN_DEGREE,
			TURN_GYRO_P, TURN_GYRO_I, TURN_GYRO_D, TURN_GYRO_F, false);
	//TODO:: PLS MAKE DIS BETTER THX - TACO
	std::vector<Motor*> CamaraMotors = std::vector<Motor*>();
	CamaraMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_1_PORT));
	CamaraMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_2_PORT));
	CamaraMotors.push_back(getMotor(DRIVEBASE_LEFTMOTOR_3_PORT));
	CamaraMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_1_PORT));
	CamaraMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_2_PORT));
	CamaraMotors.push_back(getMotor(DRIVEBASE_RIGHTMOTOR_3_PORT));
	MotorGroup * groupCamara = new MotorGroup(CamaraMotors);
	createPID(groupCamara, DRIVEBASE_ENCODER_2, PID_ID_CAMERA, CAMARA_P,
			CAMARA_I, CAMARA_D, CAMARA_F, false);

}
Motor *MotorManager::getMotor(int ID) {
	if (ID < 0 || ID >= motors.size()) {
		return NULL;
	}
	return &motors[ID];
}

MotorManager::~MotorManager() {
	for (int i = 0; i < MAX_MANAGED_MOTORS; i++) {
		if (Motors[i] != NULL) {
			delete Motors[i];
			Motors[i] = 0;
		}
	}
}

void MotorManager::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void MotorManager::setPosition(int pid, float position) {

}

void MotorManager::setSpeed(int ID, float speed) {
	std::vector<Motor>::iterator ptr = motors.begin();
	std::vector<Motor>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		if (ptr->port == ID) {
			ptr->speed = speed;

			if (ptr->motorPriority >= allowedPriority) {
				ptr->talon->Set(speed * ptr->C);
			} else {
				ptr->talon->Set(speed);
			}
			break;
		}
	}

}
void MotorManager::setSpeedForAll() {
	std::vector<Motor>::iterator ptr = motors.begin();
	std::vector<Motor>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		setSpeed(ptr->port, ptr->speed);
	}
}

float MotorManager::getSpeed(int ID) {
	return this->Motors[ID]->GetSpeed();
}
int MotorManager::setPIDValues(int ID, double P, double I, double D) {
	Motors[ID]->SetPID(P, I, D);
	return ID;
}

void setPosition(int PID, float position) {

}

double MotorManager::GetPosition(int ID) {
	return this->Motors[ID]->GetEncPosition();
}
double MotorManager::GetSpeed(int ID) {
	return this->Motors[ID]->GetSpeed();
}

void MotorManager::setPriority(Priority priorityArg) {

	std::vector<Motor>::iterator ptr = motors.begin();
	std::vector<Motor>::iterator end = motors.end();

	allowedPriority = priorityArg;

	for (; ptr != end; ++ptr) {
		if (ptr->motorPriority > priorityArg) {
			ptr->talon->Set(0);
		} else {
			ptr->talon->Set(ptr->speed);
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
	std::vector<Motor>::iterator ptr = motors.begin();
	std::vector<Motor>::iterator end = motors.end();

	for (; ptr != end; ++ptr) {
		ptr->setC(allowedPriority,
				DriverStation::GetInstance().GetBatteryVoltage());
	}

}

MotorManager * MotorManager::getMotorManager() {
	static MotorManager motorManager;
	return &motorManager;
}

void MotorManager::addMotor(Priority priority, int Port) {
	Motor * motor = new Motor(priority, Port);
	motors.push_back(*motor);
}

Motor::Motor(Priority prioArg, int portArg) {

	port = portArg;
	speed = 0;
	motorPriority = prioArg;
	talon = new CANTalon(port);

}

Motor::~Motor() {

}

void MotorManager::createPID(MotorGroup * group, int encoderID, int pidID,
		float P, float I, float D, float F, bool isSpeedMode) {

	if (pidControllerMap.count(pidID) < 1) {
		/*std::vector<Motor> motorlist;

		 for (int x = 0; x<motorID.size(); x++) {
		 motorlist.push_back(motors[motorID[x]]);
		 }
		 MotorGroup * group = new MotorGroup(motorlist);
		 */
		PIDController * pidcontroller = new PIDController(P, I, D, F,
				motors[encoderID].talon, group);
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
void MotorManager::setPIDF(int pidID, float P, float I, float D, float F) {
	pidControllerMap[pidID]->SetPID(P, I, D, F);
}

void MotorManager::enablePID(int pidID, float setPoint) {
	pidControllerMap[pidID]->SetSetpoint(setPoint);
	pidControllerMap[pidID]->Enable();
}
void MotorManager::disablePID(int pidID) {
	pidControllerMap[pidID]->Disable();
}
MotorGroup::MotorGroup(std::vector<Motor*> motorgroup) {
	this->motorlist = motorgroup;
}

void MotorGroup::PIDWrite(float output) {
	for (unsigned i = 0; i < motorlist.size(); i++) {
		motorlist[i]->talon->Set(output * motorlist[i]->C);
	}
}
