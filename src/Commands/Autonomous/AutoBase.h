#ifndef AutoBase_H
#define AutoBase_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "RobotMap.h"

class AutoBase: public CommandGroup
{
public:
	AutoBase();
	AutoBase(char *style);
	~AutoBase();
	enum goalPosition
	{
		high,
		low
	};
	enum startingPosition
	{
		spy,
		lowBar,
		posZero,
		posOne,
		posTwo,
		posThree
	};
	static AutoBase *doCheval(startingPosition sp, goalPosition gp);
	static AutoBase *doMoat(startingPosition sp, goalPosition gp);
	static AutoBase *doRockW(startingPosition sp, goalPosition gp);
	static AutoBase *doRamP(startingPosition sp, goalPosition gp);
	static AutoBase *doRoughT(startingPosition sp, goalPosition gp);
	static AutoBase *doPortC(startingPosition sp, goalPosition gp);
	static AutoBase *doSpy(startingPosition sp, goalPosition gp);
	static AutoBase *doLowB(startingPosition sp, goalPosition gp);

};

#endif
