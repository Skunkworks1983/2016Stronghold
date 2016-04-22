#include <Commands/Driving/DriveForwardStraightAccurate.h>
#include <Commands/Driving/IndexToOuterWorks.h>
#include <Commands/Driving/MoveBackUntilRoll.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <cstdbool>

IndexToOuterWorks::IndexToOuterWorks() {
	AddSequential(new PIDTurn(0, true));
	AddSequential(new MoveBackUntilRoll(3.0));
	AddSequential(new DriveForwardStraightAccurate(-1.25, -.3));
}
