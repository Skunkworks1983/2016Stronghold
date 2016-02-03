#include "MotorManager.h"
#include "../RobotMap.h"
#include "WPILib.h"

MotorManager::MotorManager() :
		Subsystem("MotorManager")
{
	Motors[DRIVEBASE_LEFTMOTOR_1_PORT] = new CANTalon(DRIVEBASE_LEFTMOTOR_1_PORT);
	Motors[DRIVEBASE_LEFTMOTOR_2_PORT] = new CANTalon(DRIVEBASE_LEFTMOTOR_2_PORT);
	Motors[DRIVEBASE_LEFTMOTOR_3_PORT] = new CANTalon(DRIVEBASE_LEFTMOTOR_3_PORT);
	Motors[DRIVEBASE_RIGHTMOTOR_1_PORT] = new CANTalon(DRIVEBASE_RIGHTMOTOR_1_PORT);
	Motors[DRIVEBASE_RIGHTMOTOR_2_PORT] = new CANTalon(DRIVEBASE_RIGHTMOTOR_2_PORT);
	Motors[DRIVEBASE_RIGHTMOTOR_3_PORT] = new CANTalon(DRIVEBASE_RIGHTMOTOR_3_PORT);
}

MotorManager::~MotorManager() {
	for (int i=0; i< MAX_MANAGED_MOTORS;i++)
	{
		if (Motors[i]!=NULL)
		{
			delete Motors[i];
			Motors[i]=0;
		}
	}
}

void MotorManager::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}




void MotorManager::setPosition(int pid, float position){

}
void MotorManager::setSpeed(int ID, float speed) {
	Motors[ID]->Set(speed);
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
MotorManager * MotorManager::getMotorManager() {
	static MotorManager motorManager;
	return &motorManager;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
