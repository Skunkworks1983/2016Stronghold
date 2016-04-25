#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/IndexToOuterWorks.h>
#include <Commands/GoScoreLowBar.h>
#include <Commands/GoScorePositionFive.h>
#include <Commands/GoScorePositionFour.h>
#include <Commands/GoScorePositionThree.h>
#include <Commands/GoScorePositionTwo.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <cstdbool>
#include <fstream>
#include <iostream>
#include <vector>

eObstacle AutoBase::obstacle = BLANK;
eStartPos AutoBase::startPos = spy;
eGoalPos AutoBase::goalPos = high;
float AutoBase::MoveAndTurnValues[4][5] = { { 6.87, 60, 420, 420 }, { 10.29, 60,
		420, 420 }, { 3.25, -30, 2, 0 }, { 10.79, 420, 420, -50 } };

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

	startPos = four;
	obstacle = Obstacle_cheval;
	goalPos = high;
}

AutoBase *AutoBase::createSelectedAuto(eObstacle obstacle, eStartPos startPos,
		eGoalPos goalPos) {
	AutoBase *auto_base = new AutoBase("SelectedAuto");

	switch (obstacle) {
	case BLANK:
		break;
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

	if (startPos != lowBar) {
		auto_base->AddSequential(new IndexToOuterWorks());
	}

	switch (startPos) {
	case lowBar:
		auto_base->AddSequential(new GoScoreLowBar());
		break;
	case two:
		auto_base->AddSequential(new GoScorePositionTwo());
		break;
	case three:
		auto_base->AddSequential(new GoScorePositionThree());
		break;
	case four:
		auto_base->AddSequential(new GoScorePositionFour());
		break;
	case five:
		auto_base->AddSequential(new GoScorePositionFive());
		break;
	}

	return auto_base;
}

AutoBase * AutoBase::getSelectedAuto() {
	return createSelectedAuto(obstacle, startPos, goalPos);
}

eStartPos AutoBase::getStartPos() {
	return startPos;
}

eObstacle AutoBase::getObstacle() {
	return obstacle;
}

float AutoBase::getFirstDistance() {
	if (startPos == spy) {
		return 0;
	}

	unsigned index = startPos - 1;

	return -getValue(0, index);
}

float AutoBase::getFirstTurnAngle() {
	if (startPos == spy) {
		return 0;
	}

	unsigned index = startPos - 1;

	return getValue(1, index)
			+ ((obstacle == Obstacle_cheval && getValue(1, index) != 420) ?
					180.0 : 0);
}

float AutoBase::getMiddleDistance() {
	if (startPos == spy) {
		return 0;
	}

	unsigned index = startPos - 1;

	return -getValue(2, index);
}

float AutoBase::getSecondTurnAngle() {
	if (startPos == spy) {
		return 0;
	}

	unsigned index = startPos - 1;

	return getValue(3, index)
			+ ((obstacle == Obstacle_cheval && getValue(1, index) != 420) ?
					180.0 : 0);
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
	LOG_INFO("goal selected %d", (*goal));

	for (unsigned i = 0; i < digitalInputs.size(); ++i) {
		delete digitalInputs[i];
	}
}

float AutoBase::getValue(unsigned x, unsigned y) {
	if (x >= 4 || y >= 5) {
		return 0;
	}
	return MoveAndTurnValues[x][y];
}

void AutoBase::setValue(unsigned x, unsigned y, float value) {
	if (x < 4 && y < 5) {
		MoveAndTurnValues[x][y] = value;
	} else {
		LOG_ERROR("Trying to write out of bounds %u %u are not valid", x, y);
	}
}

void AutoBase::readAutoValues() {
	char fileName[] = "/U/AutoValues.csv";

	std::ifstream file(fileName, std::ifstream::in);

	std::string line;
	unsigned y = 0;
	while (file.good() && y < 5) {
		for (unsigned x = 0; x < 3; x++) {
			getline(file, line, ',');
			setValue(x, y, std::stof(line));
		}
		getline(file, line, '\n');
		setValue(3, y, std::stof(line));

		y++;
	}

	file.close();

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 4; x++) {
			LOG_INFO("Next Float %u,%u at %f", x, y, getValue(x, y));
		}
	}

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
