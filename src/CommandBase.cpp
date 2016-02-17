#include <CommandBase.h>
#include <Services/Logger.h>
#include <OI.h>
#include <stddef.h>
#include <Subsystems/Shooter_Collector.h>
#include <Subsystems/Drivebase.h>
#include <Subsystems/Climber.h>


// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
Drivebase* CommandBase::drivebase = NULL;
Collector* CommandBase::collector = NULL;


Shooter* CommandBase::shooter = NULL;
SensorManager* CommandBase::sensorManager = NULL;
Climber* CommandBase::climber = NULL;

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

	sensorManager = SensorManager::getSensorManager();
	sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	climber = new Climber();

	writeToLogFile(LOGFILE_NAME, "Robot initialized");

}
