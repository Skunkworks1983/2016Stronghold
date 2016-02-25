#include <Commands/Defences/GeneralBreach.h>
#include <Commands/Driving/DriveForward.h>

GeneralBreach::GeneralBreach(float distance, float speed)
{
	AddSequential(new DriveForward(distance, speed));
}
