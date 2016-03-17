#include <CommandBase.h>
#include <OI.h>
#include <RobotMap.h>
#include <stddef.h>
#include <Services/Logger.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Drivebase.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/Collector.h>

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
Drivebase* CommandBase::drivebase = NULL;
Shooter* CommandBase::shooter = NULL;
Climber* CommandBase::climber = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name) {
}

CommandBase::CommandBase() :
		Command() {

}

void CommandBase::init() {
	oi = new OI();
#if USE_DRIVEBASE
	drivebase = new Drivebase();
#endif
#if USE_CLIMBER
	climber = new Climber();
#endif
#if USE_SHOOTER
	shooter = new Shooter();
#endif
#if USE_LOGGING
	Logger::getLogger()->log("Robot initialized", Info);
#endif
}
