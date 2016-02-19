#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotBase.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Commands/Debug/EncoderOutput.h>
#include <Commands/Debug/ResetEncoders.h>
#include <Commands/Power/StallProtection.h>
#include <RobotMap.h>


class Robot: public IterativeRobot {
private:
	LiveWindow *lw;
	EncoderOutput * encoderOutput;
	StallProtection * stallProtect;

	void RobotInit()
	{
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		if(DEBUG) {
			SmartDashboard::PutData("Reset Encoders", new ResetEncoders());
			encoderOutput = new EncoderOutput();
			encoderOutput->Start();
		}
		stallProtect = new StallProtection(); //Possibly temporary
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

