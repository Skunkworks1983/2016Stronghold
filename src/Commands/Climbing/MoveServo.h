#ifndef SRC_COMMANDS_CLIMBING_MOVESERVO_H_
#define SRC_COMMANDS_CLIMBING_MOVESERVO_H_

#include <CommandBase.h>
#include <cstdbool>

class MoveServo : public CommandBase{
public:
	enum eServoPosition {
		IN, OUT
	};
	MoveServo(eServoPosition pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	eServoPosition pos;
};

#endif /* SRC_COMMANDS_CLIMBING_MOVESERVO_H_ */
