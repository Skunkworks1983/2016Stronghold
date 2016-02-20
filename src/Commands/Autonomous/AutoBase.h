#ifndef AutoBase_H
#define AutoBase_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "RobotMap.h"
#include <vector>
#include <DigitalInput.h>

class AutoBase: public CommandGroup
{
private:

	enum eGoalPos
	{
		high,
		low
	};

	enum eStartPos
	{
		spy,
		lowBar,
		posZero,
		posOne,
		posTwo,
		posThree
	};

	enum eObstacle
	{
		Obstacle_lowBar,
		Obstacle_cheval,
		Obstacle_moat,
		Obstacle_rough,
		Obstacle_ramppart,
		Obstacle_rockwall,
		Obstacle_portcullis
	};



	static AutoBase *createSelectedAuto(eObstacle obstacle, eStartPos startPos, eGoalPos goalPos);
	static void readDIPSwitches(eObstacle *obstacle, eStartPos *sp, eGoalPos *goal);
	static AutoBase *doCheval(); //Cheval de Frise
	static AutoBase *doMoat(); // the U-shape
	static AutoBase *doRockW(); //Rock Wall
	static AutoBase *doRamP(); // Ramparts
	static AutoBase *doRoughT(); //Tough Terrain
	static AutoBase *doPortC(); //Portcullis
	static AutoBase *doSpy(); //Spy box
	static AutoBase *doLowB(); // Low Bar

	AutoBase();
	AutoBase(char *style);
	~AutoBase();
public:
	static AutoBase *getSelectedAuto();

};

#endif
;
