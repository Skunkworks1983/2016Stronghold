#ifndef MANAGE_POWER_H
#define MANAGE_POWER_H

#include <CommandBase.h>
#include <cstdbool>



class MotorManager;

class ManagePower: public CommandBase {
private:
	// Data
	MotorManager *      manager = NULL;

	double  m_voltage;



	// Helpers
	void UpdateVoltagages();

public:
	ManagePower();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
