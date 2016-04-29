#ifndef HoldAgainstTower_H
#define HoldAgainstTower_H

#include <CommandBase.h>
#include <cstdbool>

class HoldAgainstTower: public CommandBase {
private:
	float speed;
public:
	HoldAgainstTower(float speed); //distance to drive (ENCODER TICKS), speed at which to drive, whether or not to orient after drive is complete
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
