/*
 * DriveToSomething.h
 *
 *  Created on: Jan 19, 2016
 *      Author: s-2507264
 */


#ifndef SRC_COMMANDS_DRIVETOSOMETHING_H_
#define SRC_COMMANDS_DRIVETOSOMETHING_H_
#include <Subsystems/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <CommandBase.h>

class DriveToSomething: public CommandBase {
private:
	float distance;
	float speed;
	float dt;
	float distant;
public:
	DriveToSomething(float distance,float speed);
		void Initialize();
		void Execute();
		bool IsFinished();
		void End();
		void Interrupted();
		~DriveToSomething();


};



#endif /* SRC_COMMANDS_DRIVETOSOMETHING_H_ */
