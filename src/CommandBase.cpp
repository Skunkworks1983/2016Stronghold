#include <CommandBase.h>
#include <OI.h>
#include <RobotMap.h>
#include <stddef.h>
#include <Services/Logger.h>
#include <Subsystems/Collector.h>
#include <Subsystems/Drivebase.h>


// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
Drivebase* CommandBase::drivebase = NULL;
Collector* CommandBase::collector = NULL;
Shooter* CommandBase::shooter = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name) {
}

CommandBase::CommandBase() :
		Command() {

}

void CommandBase::init() {
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	oi = new OI();
	drivebase = new Drivebase();
	collector = new Collector();
	writeToLogFile(LOGFILE_NAME, "Robot initialized");

}
