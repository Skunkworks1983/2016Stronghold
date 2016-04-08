#ifndef StopShooterPID_H
#define StopShooterPID_H

#include <CommandBase.h>
#include <cstdbool>

class StopShooterRotationPID: public CommandBase {
public:
	StopShooterRotationPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
