#include "LineFollow.h"
#include <RobotMap.h>
#include "Subsystems/Drivebase.h"

LineFollow::LineFollow() {
	Requires(drivebase);

	pid = new PIDController(LINE_FOLLOW_P, LINE_FOLLOW_I, LINE_FOLLOW_D, this, this);
	lightsensor = new AnalogInput(1);

}
LineFollow::~LineFollow(){

	delete pid;
	delete lightsensor;

}
// Called just before this Command runs the first time
void LineFollow::Initialize() {
	pid->Enable();


}

// Called repeatedly when this Command is scheduled to run
void LineFollow::Execute() {



}

// Make this return true when this Command no longer needs to run execute()
bool LineFollow::IsFinished() {
	//TODO: Come back to this
	return false;



}

// Called once after isFinished returns true
void LineFollow::End() {

	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LineFollow::Interrupted() {
 End();
}

double LineFollow::PIDGet(){

return lightsensor->GetValue();

}

void LineFollow::PIDWrite(double output){
	Requires(drivebase);
	//TODO: come back to this math
	drivebase->setLeftSpeed(output);
	drivebase->setRightSpeed(1-output);


}

