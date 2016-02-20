#ifndef ResetEncoders_H
#define ResetEncoders_H

#include "../../CommandBase.h"
#include "WPILib.h"


class ResetEncoders: public CommandBase
{
public:
	ResetEncoders();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
