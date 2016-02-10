#include "MotorManager.h"
#include "../RobotMap.h"
#include "WPILib.h"

MotorManager::MotorManager() :
		Subsystem("MotorManager") {
	/*Motors[DRIVEBASE_LEFTMOTOR_1_PORT] = new CANTalon(
	 *DRIVEBASE_LEFTMOTOR_1_PORT);
	 *Motors[DRIVEBASE_LEFTMOTOR_2_PORT] = new CANTalon(
	 *DRIVEBASE_LEFTMOTOR_2_PORT);
	 *Motors[DRIVEBASE_LEFTMOTOR_3_PORT] = new CANTalon(
	 *DRIVEBASE_LEFTMOTOR_3_PORT);
	 Motors[DRIVEBASE_RIGHTMOTOR_1_PORT] = new CANTalon(
	 DRIVEBASE_RIGHTMOTOR_1_PORT);
	 Motors[DRIVEBASE_RIGHTMOTOR_2_PORT] = new CANTalon(
	 DRIVEBASE_RIGHTMOTOR_2_PORT);
	 Motors[DRIVEBASE_RIGHTMOTOR_3_PORT] = new CANTalon(
	 DRIVEBASE_RIGHTMOTOR_3_PORT);
	 */

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

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, MULTI_TOOL_MOTRO_1_PORT);
	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, MULTI_TOOL_MOTRO_2_PORT);

	addMotor(Priority::PRIORITY_PRIMARY_ACTUATORS, COLLECTOR_MOTOR_PORT);

	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_1_PORT);
	addMotor(Priority::PRIORITY_SECONDARY_ACTUATORS, SHOOTER_MOTOR_2_PORT);

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

float MotorManager::getSpeed(int ID){
return this->Motors[ID]->GetSpeed();
}
int MotorManager::setPIDValues(int ID, double P, double I, double D){
	Motors[ID]->SetPID(P, I, D);
	return ID;
}

void setPosition(int PID, float position) {

}

double MotorManager::GetPosition(int ID) {
	return this->Motors[ID]->GetPosition();
}
double MotorManager::GetSpeed(int ID){
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
		if (voltage > POWER_BROWNOUT_VOLTAGE+POWER_DRIVEBASE_VOLTAGE_WIDTH) {
			this->C = 1;
		} else {
			this->C = pow((((voltage - POWER_BROWNOUT_VOLTAGE) / (POWER_DRIVEBASE_VOLTAGE_WIDTH))), 2);
		}
	} else if (this->motorPriority >= priorityArg) {
		    this->C = pow((((voltage - POWER_BROWNOUT_VOLTAGE) / (motorPriority * POWER_VOLTAGE_WIDTH))), 2);
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

CANTalon * MotorManager::addMotor(Priority priority, int Port) {
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

