#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/IndexToOuterWorks.h>
#include <Commands/Driving/AutoDriving/MoveBackUntilRoll.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/TimeOut.h>
#include <RobotMap.h>
#include <cstdbool>

IndexToOuterWorks::IndexToOuterWorks() {
	AddSequential(new PIDTurn(0, true, 2.5));
	//AddSequential(new DriveForwardStraight(-3.0, -.4, .25, true));

	AddSequential(new TimeOut(.35));

	LOG_INFO("GetObstacle=%u", AutoBase::getObstacle());
	if (AutoBase::getObstacle() != Obstacle_cheval
			&& AutoBase::getObstacle() != Obstacle_lowbar) {
		AddSequential(new MoveBackUntilRoll(1.75));
	}
	//AddSequential(new DriveForwardStraightAccurate(-1.25, -.5));
}
