#include <Commands/Climbing/MoveServo.h>
#include <Commands/Climbing/RotateArm.h>
#include <Commands/Climbing/SafeRotateArm.h>
#include <Commands/MultiTool/ResetCollectorEncoder.h>
#include <TuningValues.h>

SafeRotateArm::SafeRotateArm(float target)
{
	//AddSequential(new CollectorMove(CollectorPosition::cCollect));
	//AddSequential(new MoveServo(MoveServo::OUT));
	AddSequential(new RotateArm(target));
}
