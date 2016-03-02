#include <Commands/Climbing/MoveServo.h>
#include <Commands/Climbing/RotateArm.h>
#include <Commands/Climbing/RunWinch.h>
#include <Commands/Climbing/SafeRotateArm.h>
#include <Commands/Driving/HoldAgainstTower.h>
#include <Commands/MultiTool/CollectorMove.h>

SafeRotateArm::SafeRotateArm(float target)
{
	//AddSequential(new HoldAgainstTower(.2));
	//AddSequential(new CollectorMove(CollectorPosition::cCollect));
	AddSequential(new MoveServo(MoveServo::OUT));
	AddSequential(new RotateArm(target));
	AddSequential(new RunWinch(.5, .25));
}
