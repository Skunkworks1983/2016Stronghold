#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotBase.h>
#include <SerialPort.h>

#include "../navx-mxp/cpp/include/AHRS.h"

class Robot: public IterativeRobot {
private:
	LiveWindow *lw;
	AHRS *gyro;

	void RobotInit() {
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		gyro = new AHRS(SerialPort::kMXP); /* Alternatives:  SPI::kMXP, I2C::kMXP or SerialPort::kUSB */
	}

	void DisabledPeriodic() {
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() {

	}

	void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.

	}

	void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

