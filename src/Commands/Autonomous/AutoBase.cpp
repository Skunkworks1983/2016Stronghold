#include <Commands/Autonomous/AutoBase.h>
#include <Commands/GoAndScoreHighGoal.h>
#include <Commands/HighGoalPosThree.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <cstdbool>
#include <fstream>
#include <iostream>
#include <vector>

eObstacle AutoBase::obstacle = BLANK;
eStartPos AutoBase::startPos = spy;
eGoalPos AutoBase::goalPos = high;

AutoBase::AutoBase() {
	AutoBase("AutoBase-Blank");
}

AutoBase::AutoBase(char *style) :
		CommandGroup(style) {

}

AutoBase::~AutoBase() {
}

void AutoBase::readValues() {
	readDIPSwitchedObstacle(&obstacle);
	readDIPSwitchedPosition(&startPos);

	//startPos = posOne;
	//obstacle = Obstacle_rockwall;
	goalPos = high;
}

float AutoBase::getTurnAngle() {
	float ret_val = 0;

	switch (startPos) {
	case spy:
		ret_val = 0.0;
		break;
	case lowBar:
		ret_val = 60;
		break;
	case posZero:
		ret_val = 60;
		break;
	case posOne:
		ret_val = 40;
		break;
	case posTwo:
		ret_val = -10;
		break;
	case posThree:
		ret_val = -60;
		break;
	}

	LOG_INFO("GETTURN ANGLE RETURNING %f", ret_val);

	return ret_val;
}

float AutoBase::getSecondTurnAngle() {
	float ret_val = 0;

	switch (startPos) {
	case spy:
		ret_val = 0.0;
		break;
	case lowBar:
		ret_val = 0.0;
		break;
	case posZero:
		ret_val = 0;
		break;
	case posOne:
		ret_val = -40;
		break;
	case posTwo:
		ret_val = 10;
		break;
	case posThree:
		ret_val = 0;
		break;
	}

	LOG_INFO("GETSECONDTURN ANGLE RETURNING %f", ret_val);

	return ret_val;
}

float AutoBase::getFirstDistance() {
	switch (startPos) {
	case spy:
		return 0;
	case lowBar:
		return -5.25;
	case posZero:
		return -7.35;
	case posOne:
		return 0;
	case posTwo:
		return 0;
	case posThree:
		return -8.5;
	}
	return 0;
}

float AutoBase::getMiddleDistance() {
	switch (startPos) {
	case spy:
		return -0.0;
	case lowBar:
		return -2.0;
	case posZero:
		return -2.0;
	case posOne:
		return -1.0;
	case posTwo:
		return -2.0;
	case posThree:
		return -2.0;
	}
	return -2.0;
}

AutoBase *AutoBase::readFromTextFile(std::string file) {
	char* title;
	std::string line;
	std::ifstream myfile(file);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			std::cout << line << '\n';
		}
		myfile.close();
	} else {
		std::cout << "Unable to open file";
	}
	AutoBase *auto_base = new AutoBase(title);

	return auto_base;
}

TurnData *AutoBase::getTurnData() {
	TurnData *d = new TurnData();
	float angle = 0;

	switch (startPos) {
	case spy:
		angle = 0.0;
		break;
	case lowBar:
		angle = 60;
		break;
	case posZero:
		angle = 60;
		break;
	case posOne:
		angle = 40;
		break;
	case posTwo:
		angle = -5;
		break;
	case posThree:
		angle = -50;
		break;
	}

	d->angle = angle;

	float power = 0;

	switch (startPos) {
	case spy:
		power = -.5;
		break;
	case lowBar:
		power = -.7;
		break;
	case posZero:
		power = -.7;
		break;
	case posOne:
		power = -.5;
		break;
	case posTwo:
		power = -.5;
		break;
	case posThree:
		power = -.75;
		break;
	}

	d->power = power;

	float percentage = 0;

	switch (startPos) {
	case spy:
		percentage = 0.3;
		break;
	case lowBar:
		percentage = -.25;
		break;
	case posZero:
		percentage = -.25;
		break;
	case posOne:
		percentage = -0.5;
		break;
	case posTwo:
		percentage = 0.2;
		break;
	case posThree:
		percentage = -0.7;
		break;
	}

	d->percentage = percentage;

	return d;
}

TurnData *AutoBase::getSecondTurnData() {
	TurnData *d = new TurnData();
	float angle = 0;

	switch (startPos) {
	case spy:
		angle = 0.0;
		break;
	case lowBar:
		angle = 0.0;
		break;
	case posZero:
		angle = 0;
		break;
	case posOne:
		angle = -30;
		break;
	case posTwo:
		angle = 5;
		break;
	case posThree:
		angle = 0;
		break;
	}

	d->angle = angle;

	float power = 0;

	switch (startPos) {
	case spy:
		power = -.5;
		break;
	case lowBar:
		power = -.5;
		break;
	case posZero:
		power = -.5;
		break;
	case posOne:
		power = -.5;
		break;
	case posTwo:
		power = -.5;
		break;
	case posThree:
		power = -.5;
		break;
	}

	d->power = power;

	float percentage = 0;

	switch (startPos) {
	case spy:
		percentage = 0.3;
		break;
	case lowBar:
		percentage = 0.3;
		break;
	case posZero:
		percentage = 0.3;
		break;
	case posOne:
		percentage = -0.5;
		break;
	case posTwo:
		percentage = 0.2;
		break;
	case posThree:
		percentage = 0.3;
		break;
	}

	d->percentage = percentage;

	return d;
}

AutoBase *AutoBase::createSelectedAuto(eObstacle obstacle, eStartPos startPos,
		eGoalPos goalPos) {
	AutoBase *auto_base = new AutoBase("SelectedAuto");

	switch (obstacle) {
	case BLANK:
		return auto_base;
	case Obstacle_lowbar:
		auto_base->AddSequential(AutoBase::doLowB());
		break;

	case Obstacle_cheval:
		auto_base->AddSequential(AutoBase::doCheval());
		break;

	case Obstacle_moat:
		auto_base->AddSequential(AutoBase::doMoat());
		break;

	case Obstacle_rough:
		auto_base->AddSequential(AutoBase::doRoughT());
		break;

	case Obstacle_ramparts:
		auto_base->AddSequential(AutoBase::doRamP());
		break;

	case Obstacle_rockwall:
		auto_base->AddSequential(AutoBase::doRockW());
		break;

	case Obstacle_portcullis:
		auto_base->AddSequential(AutoBase::doPortC());
		break;
	}
	if (goalPos == eGoalPos::high && obstacle != BLANK) {
		if (startPos == eStartPos::posThree) {
			auto_base->AddSequential(new HighGoalPosThree());
		} else {
			auto_base->AddSequential(new GoAndScoreHighGoal());
		}
	}

	return auto_base;
}

AutoBase * AutoBase::getSelectedAuto() {
	return createSelectedAuto(obstacle, startPos, goalPos);
}

void AutoBase::readDIPSwitchedObstacle(eObstacle *obstacle) {
	LOG_INFO("Read Switched Obstacle start");
	std::vector<DigitalInput *> digitalInputs; // initialize digital input

	for (int i = 0; i < 3; i++) {
		digitalInputs.push_back(new DigitalInput(i));
	}

	//calculate obstacle
	*obstacle = (eObstacle) 0;
	int adder = 1;
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		bool isSet = !digitalInputs[i]->Get();
		LOG_INFO("index %u bool %u", i, isSet);
		if (isSet) {
			*obstacle = (eObstacle) ((*obstacle) | adder);
		}
		adder = adder << 1;
	}
	LOG_INFO("obstacle selected %d", (*obstacle));
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		delete digitalInputs[i];
	}
}

void AutoBase::readDIPSwitchedPosition(eStartPos *startPos) {
	LOG_INFO("Read Switched Obstacle start");
	std::vector<DigitalInput *> digitalInputs; // initialize digital input

	for (int i = 4; i < 7; i++) {
		digitalInputs.push_back(new DigitalInput(i));
	}
	//left obstacle, right position
	//calculate obstacle
	*startPos = (eStartPos) 0;
	int adder = 1;
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		bool isSet = !digitalInputs[i]->Get();
		LOG_INFO("index %u bool %u", i, isSet);
		if (isSet) {
			*startPos = (eStartPos) ((*startPos) | adder);
		}
		adder = adder << 1;
	}
	LOG_INFO("position selected %d", (*startPos));
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		delete digitalInputs[i];
	}
}

void AutoBase::readDIPSwitches(eObstacle *obstacle, eStartPos *sp,
		eGoalPos *goal) {
	std::vector<DigitalInput *> digitalInputs; // initialize digital input
	for (int i = DIP_START; i < DIP_END; ++i) {
		digitalInputs.push_back(new DigitalInput(i));
	}

	//calculate position
	*sp = (eStartPos) 0; // start Position
	int adder = 1;
	for (int i = DIP_CHANNEL_POSITION_START; i < DIP_CHANNEL_POSITION_END;
			++i) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*sp = (eStartPos) ((*sp) | adder);
		}
		adder = adder << 1;
	}
	LOG_INFO("position selected %d", (*sp));

	//calculate obstacle
	*obstacle = (eObstacle) 0;
	adder = 1;
	for (int i = DIP_CHANNEL_OBSTACLE_START; i < DIP_CHANNEL_OBSTACLE_END;
			i++) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*obstacle = (eObstacle) ((*obstacle) | adder);
		}
		adder = adder << 1;
	}
	LOG_INFO("obstacle selected %d", (*obstacle));
	//calculate goal
	/**goal = (eGoalPos) 0; // start Position
	 adder = 1;
	 for (int i = DIP_CHANNEL_GOAL_START; i < DIP_CHANNEL_GOAL_END; i++) {
	 bool isSet = digitalInputs[i]->Get();
	 if (isSet) {
	 *goal = (eGoalPos) ((*goal) | adder);
	 }
	 adder = adder << 1;
	 }*/
	LOG_INFO("goal selected %d", (*goal));

	for (unsigned i = 0; i < digitalInputs.size(); ++i) {
		delete digitalInputs[i];
	}
}

