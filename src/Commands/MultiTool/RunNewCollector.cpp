#include <Commands/MultiTool/RunCollector.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/Shooting/RunShooter.h>
#include <Subsystems/Shooter.h>

RunNewCollector::RunNewCollector() {
	AddParallel(new RunCollector(Shooter::KBackward, 1.0));
	AddParallel(new RunShooter(-.25));
}
