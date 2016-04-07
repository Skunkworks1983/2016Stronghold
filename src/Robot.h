#ifndef ROBOT_H_
#define ROBOT_H_

#include <IterativeRobot.h>
#include <stddef.h>
#include <cstdint>

class ManagePower;

class LiveWindow;

class DriveForwardStraight;

class AutoBase;

class MotorManager;
class SensorManager;

class Robot: public IterativeRobot {
private:
	MotorManager * motorManager  = NULL;
	SensorManager * sensorManager  = NULL;
	ManagePower *managePower  = NULL;
	int count;
	AutoBase *cmd  = NULL;
	uint64_t oldTime;
	static uint64_t autoStart;
	static uint64_t teleStart;
public:
	void RobotInit();
	void DisabledInit();
	void DisabledPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
	void AutonomousPeriodic();
	void AutonomousInit();
	static uint64_t getAutoStartTime();
	static uint64_t getTeleStartTime();
};

#endif /* ROBOT_H_ */
