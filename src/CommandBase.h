#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <Commands/Command.h>

class Collector;
class Drivebase;
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
};

#endif
