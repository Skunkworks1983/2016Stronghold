#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <Commands/Command.h>
#include <Subsystems/SensorManager.h>
#include "Subsystems/Climber.h"


// Redeclare static classes
class Drivebase;
class Collector;
class OI;
class Shooter;

class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static OI *oi;
	static Drivebase *drivebase;
	static Collector *collector;

	static Shooter *shooter;
	static SensorManager *sensorManager;
	static Climber *climber;

};

#endif
