#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <Commands/Command.h>
#include <Subsystems/Drivebase.h>

// Redeclare static classes
class Drivebase;
class Shooter;
class OI;
class Climber;

class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static OI *oi;
	static Drivebase *drivebase;
	static Shooter *shooter;
	static Climber *climber;
};

#endif
