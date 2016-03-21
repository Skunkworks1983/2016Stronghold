#include <Commands/MultiTool/RunCollector.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/Shooting/RunShooter.h>
#include <Commands/TimeOut.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

RunNewCollector::RunNewCollector(float timeout, bool reverse) :
		reverse(reverse) {
//	if (reverse) {
//		AddParallel(
//				new RunCollector(Shooter::KForward, reverse ? -1.0 : 1.0,
//						timeout));
//		AddParallel(new RunShooter(this->reverse ? -0.5 : 0.5), timeout);
//	} else {
		AddParallel(new RunCollector(Shooter::KBackward, 1.0, timeout));
		AddParallel(new RunShooter(-0.5, .2, timeout));

}
