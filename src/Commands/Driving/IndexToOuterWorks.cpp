#include <Commands/Driving/EnableBrakeMode.h>
#include <Commands/Driving/IndexToOuterWorks.h>
#include <Commands/Driving/MoveBackUntilRoll.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <cstdbool>

IndexToOuterWorks::IndexToOuterWorks() {
	AddSequential(new EnableBrakeMode(true, .5));
	AddSequential(new ArcTurn(0, .75, -.75, true));
	AddSequential(new MoveBackUntilRoll());
}
