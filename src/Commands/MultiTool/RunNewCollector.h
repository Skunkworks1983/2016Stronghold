#ifndef RunNewCollector_H
#define RunNewCollector_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class RunNewCollector: public CommandGroup
{
private:
	bool reverse;
public:
	RunNewCollector(float timeout = 0, bool reverse = false);
};

#endif
