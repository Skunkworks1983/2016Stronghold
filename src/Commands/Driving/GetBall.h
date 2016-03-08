/*
 * GetBall.h
 *
 *  Created on: Mar 7, 2016
 *      Author: S-4020395
 */

#ifndef SRC_COMMANDS_DRIVING_GETBALL_H_
#define SRC_COMMANDS_DRIVING_GETBALL_H_

#include <CommandBase.h>

class GetBall: public CommandBase {
private:
	float speedTranslate;
public:
	GetBall(float speedTranslate);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_DRIVING_GETBALL_H_ */
