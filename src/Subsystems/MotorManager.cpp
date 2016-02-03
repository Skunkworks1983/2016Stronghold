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

			if (ptr->priority <= allowedPriority) {
				ptr->talon->Set(speed);
			} else {
				ptr->talon->Set(0);
			}
			break;
		}
	}

}


int MotorManager::setPIDValues(int ID, double P, double I, double D) {
	Motors[ID]->SetPID(P, I, D);
	return ID;
}

void setPosition(int PID, float position) {

}

double MotorManager::GetPosition(int ID) {
	return this->Motors[ID]->GetPosition();
}

void MotorManager::setPriority(Priority priorityArg) {

	std::vector<Motor>::iterator ptr = motors.begin();
	std::vector<Motor>::iterator end = motors.end();

	allowedPriority = priorityArg;

	for (; ptr != end; ++ptr) {
		if (ptr->priority > priorityArg) {
			ptr->talon->Set(0);
		} else {
			ptr->talon->Set(ptr->speed);
		}
	}

}

void Motor::setC(Priority priorityArg, float voltage) {
	if (priority == 0) {
		return;
	}
	if (this->priority >= priorityArg) {
		this->C = pow((((voltage - 5) / (priority * 2))), 2);
	}
}


void MotorManager::setCForAll(Priority p1, Priority p2,Priority p3,Priority p4){

	setC(p1, 8);
	setC(p2, 6);
	setC(p3, 4);
	setC(p4, 2);


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
	priority = prioArg;
	talon = new CANTalon(port);

}

Motor::~Motor() {

}

