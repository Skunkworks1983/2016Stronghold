#ifndef StopCollectorPID_H
#define StopCollectorPID_H

/*#include "../CommandBase.h"
 #include "WPILib.h"

 class CollectorMove: public CommandBase
 {
 public:
 CollectorMove();
 void Initialize();
 void Execute();
 bool IsFinished();
 void End();
 void Interrupted();
 };

 #endif
 */

#include <CommandBase.h>
#include <cstdbool>

class StopCollectorPID: public CommandBase {
public:
	StopCollectorPID();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_TURNDEGREE_H_ */
