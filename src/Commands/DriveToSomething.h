/*
 * DriveToSomething.h
 *
 *  Created on: Jan 19, 2016
 *      Author: s-2507264
 */


#ifndef SRC_COMMANDS_DRIVETOSOMETHING_H_
#define SRC_COMMANDS_DRIVETOSOMETHING_H_

#include<Subsystems/DriveBase.h>
#include<CommandBase.h>

class DriveToSomething: public CommandBase {
private:
	float distance;
	int speed;
public:
	DriveToSomething(float distance,int speed);
		void Initialize();
		void Execute();
		bool IsFinished();
		void End();
		void Interrupted();

};



#endif /* SRC_COMMANDS_DRIVETOSOMETHING_H_ */
