#include <Commands/TurnOnLight.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

TurnOnLight::TurnOnLight(bool turnOn, bool toggle, double timeout) :
		turnOn(turnOn), toggle(toggle), timeout(timeout) {
	//no requires, simple digitalOut
}

// Called just before this Command runs the first time
void TurnOnLight::Initialize() {
	if (toggle) {
		shooter->turnOnLight(!shooter->getLightState());
	} else {
		shooter->turnOnLight(turnOn);
	}
	if (timeout > 0) {
		SetTimeout(timeout);
	}
}

// Called repeatedly when this Command is scheduled to run
void TurnOnLight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool TurnOnLight::IsFinished() {
	//if a timeout is passed in wait until that timeout is done to end
	//otherwise return true, light is on
	return timeout == 0 || IsTimedOut();
}

// Called once after isFinished returns true
void TurnOnLight::End() {
	if (timeout != 0) {
		//if it timedout there must be a reason so go back to opposite(original) state
		if(toggle){
			shooter->turnOnLight(!shooter->getLightState());
		}else{
			shooter->turnOnLight(!turnOn);
		}
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnOnLight::Interrupted() {
	End();
}
