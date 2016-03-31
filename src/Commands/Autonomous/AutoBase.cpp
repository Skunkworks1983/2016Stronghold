#include <Commands/Autonomous/AutoBase.h>
#include <Commands/GoAndScoreHighGoal.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <cstdbool>
#include <fstream>
#include <iostream>
#include <vector>

AutoBase::AutoBase() {
	AutoBase("AutoBase-Blank");
}

AutoBase::AutoBase(char *style) :
		CommandGroup(style) {

}

AutoBase::~AutoBase() {
}

float AutoBase::getTurnAngle() {
	eStartPos startPos;
	readDIPSwitchedPosition(&startPos);

	startPos = eStartPos::lowBar;

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
		ret_val = 20;
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

AutoBase *AutoBase::readFromTextFile(std::string file) {
	char* title;
	std::string line;
	std::ifstream myfile(file);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			std::cout << line << '\n';
		}
		myfile.close();
	}

	else
		std::cout << "Unable to open file";

	AutoBase *auto_base = new AutoBase(title);

	return auto_base;
}

AutoBase *AutoBase::createSelectedAuto(eObstacle obstacle, eStartPos startPos,
		eGoalPos goalPos) {
	AutoBase *auto_base = new AutoBase("SelectedAuto");
	switch (obstacle) {
	case BLANK:
		break;
	case Obstacle_lowBar:
		auto_base->AddSequential(AutoBase::doLowB());
		break;

	case Obstacle_cheval:
		auto_base->AddSequential(AutoBase::doLowBarandScore());
		//auto_base->AddSequential(AutoBase::doCheval());
		break;

	case Obstacle_moat:
		auto_base->AddSequential(AutoBase::doMoat());
		break;

	case Obstacle_rough:
		auto_base->AddSequential(AutoBase::doRoughT());
		break;

	case Obstacle_ramppart:
		auto_base->AddSequential(AutoBase::doRoughT());
		break;

	case Obstacle_rockwall:
		//auto_base->AddSequential(AutoBase::doRockW());
		break;

	case Obstacle_portcullis:
		auto_base->AddSequential(AutoBase::doPortC());
		break;
	}
	if(goalPos == eGoalPos::high){
		auto_base->AddSequential(new GoAndScoreHighGoal());
	}

	return auto_base;
}

AutoBase * AutoBase::getSelectedAuto() {
	eObstacle obstacle = BLANK;
	eStartPos startPos = posZero;
	eGoalPos goalPos = high;

	//readDIPSwitches(&obstacle, &startPos, &goalPos);
	readDIPSwitchedObstacle(&obstacle);
	readDIPSwitchedPosition(&startPos);

	obstacle = eObstacle::Obstacle_lowBar;
	startPos = eStartPos::lowBar;
	goalPos = eGoalPos::high;

	return createSelectedAuto(obstacle, startPos, goalPos);
}

void AutoBase::readDIPSwitchedObstacle(eObstacle *obstacle) {
	LOG_INFO("Read Switched Obstacle start");
	std::vector<DigitalInput *> digitalInputs; // initialize digital input

	for (int i = 1; i < 4; i++) {
		digitalInputs.push_back(new DigitalInput(i));
	}

	//calculate obstacle
	*obstacle = (eObstacle) 0;
	int adder = 1;
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		bool isSet = digitalInputs[i]->Get();
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

	//calculate obstacle
	*startPos = (eStartPos) 0;
	int adder = 1;
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		bool isSet = digitalInputs[i]->Get();
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

