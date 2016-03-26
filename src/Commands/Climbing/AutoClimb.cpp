#include <Commands/Climbing/AutoClimb.h>
#include <Commands/Climbing/AutoRotateArm.h>
#include <Commands/Climbing/MoveServo.h>
#include <Commands/Climbing/RunWinch.h>

AutoClimb::AutoClimb(float target)
{
	AddSequential(new MoveServo(MoveServo::OUT)); 			//Remove Servo
	AddSequential(new AutoRotateArm(target));	  			//Rotate arm until stopped
	AddSequential(new RunWinch(WINCH_SETPOINT, .75));		//Run the winch
}
