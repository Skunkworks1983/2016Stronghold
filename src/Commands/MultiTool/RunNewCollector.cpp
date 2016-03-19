#include <Commands/MultiTool/RunCollector.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/Shooting/RunShooter.h>
#include <Commands/TimeOut.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

RunNewCollector::RunNewCollector(float timeout, bool reverse) :
		reverse(reverse) {
	AddParallel(
			new RunCollector(
					this->reverse ? Shooter::KForward : Shooter::KBackward,
					1.0, timeout));
	AddParallel(new RunShooter((this->reverse ? -1 : 1) * -.50), timeout);
}
