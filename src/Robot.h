#ifndef ROBOT_H_
#define ROBOT_H_

#include <IterativeRobot.h>

class AutoBase;

class ManagePower;

class Robot: public IterativeRobot {
private:
	ManagePower *managePower;
	int count;
	AutoBase *cmd;
public:
	void RobotInit();
	void DisabledPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
	void AutonomousPeriodic();
	void AutonomousInit();
};





#endif /* ROBOT_H_ */
