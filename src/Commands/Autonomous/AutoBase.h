#ifndef AutoBase_H
#define AutoBase_H

#include <Commands/CommandGroup.h>
#include <string>

class SensorManager;

enum eGoalPos {
	high, low
};

enum eStartPos {
	spy, lowBar, two, three, four, five
};

enum eObstacle {
	BLANK,
	Obstacle_lowbar,
	Obstacle_cheval,
	Obstacle_moat,
	Obstacle_rough,
	Obstacle_ramparts,
	Obstacle_rockwall,
	Obstacle_portcullis
};

struct TurnData {
	TurnData(float angle, float power, float percentage) {
		this->angle = angle;
		this->power = power;
		this->percentage = percentage;
	}

	TurnData() {
		angle = 0.0;
		power = 0.0;
		percentage = 0.0;
	}
	float angle;
	float power;
	float percentage;
};

class AutoBase: public CommandGroup {
private:
	static eStartPos startPos;
	static eObstacle obstacle;
	static eGoalPos goalPos;

	static float MoveAndTurnValues[4][5];


public:
	static void readAutoValues();

	static float getValue(unsigned x, unsigned y);
	static void setValue(unsigned x, unsigned y, float value);

	static AutoBase *getSelectedAuto();

	static AutoBase *readFromTextFile(std::string);
	static AutoBase *createSelectedAuto(eObstacle obstacle, eStartPos startPos,
			eGoalPos goalPos);
	static void readDIPSwitches(eObstacle *obstacle, eStartPos *sp,
			eGoalPos *goal);
	static void readDIPSwitchedObstacle(eObstacle *obstacle);
	static void readDIPSwitchedPosition(eStartPos *startPos);
	static AutoBase *doCheval(); //Cheval de Frise
	static AutoBase *doMoat(); // the U-shape
	static AutoBase *doRockW(); //Rock Wall
	static AutoBase *doRamP(); // Ramparts
	static AutoBase *doRoughT(); //Tough Terrain
	static AutoBase *doPortC(); //Portcullis
	static AutoBase *doSpy(); //Spy box
	static AutoBase *doLowB(); // Low Bar
	static AutoBase *doLowBarandScore(); // Low Bar and score
	static float getFirstTurnAngle();
	static float getSecondTurnAngle();
	static float getFirstDistance();
	static float getMiddleDistance();

	static eStartPos getStartPos();
	static eObstacle getObstacle();

	static TurnData *getTurnData();
	static TurnData *getSecondTurnData();

	static void readValues();

	AutoBase();
	AutoBase(char *style);
	~AutoBase();
};

#endif
