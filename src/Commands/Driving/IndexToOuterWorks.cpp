#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/IndexToOuterWorks.h>
#include <Commands/Driving/MoveBackUntilRoll.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <cstdbool>

IndexToOuterWorks::IndexToOuterWorks() {
	//AddSequential(new ArcTurn(0, -.75, -.75, true));
	AddSequential(
			new PIDTurn(AutoBase::getObstacle() == Obstacle_cheval ? 179 : 0,
					true));
	AddSequential(new MoveBackUntilRoll(3.0));
}
