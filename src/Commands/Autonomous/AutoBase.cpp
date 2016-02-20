#include <Commands/Autonomous/AutoBase.h>
#include <cstdbool>

AutoBase::AutoBase() {
	AutoBase("AutoBase-Blank");
}

AutoBase::AutoBase(char *style) :
		CommandGroup(style) {
}

AutoBase::~AutoBase() {
}

AutoBase *AutoBase::createSelectedAuto(eObstacle obstacle, eStartPos startPos,
		eGoalPos goalPos) {
	AutoBase *auto_base = new AutoBase("SelectedAuto");
	switch (obstacle) {
	case Obstacle_lowBar:
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

	case Obstacle_ramppart:
		auto_base->AddSequential(AutoBase::doRamP());
		break;

	case Obstacle_rockwall:
		auto_base->AddSequential(AutoBase::doRockW());
		break;

	case Obstacle_portcullis:
		auto_base->AddSequential(AutoBase::doPortC());
		break;
	}

	//TODO: move to desired goal

	switch (goalPos) {
	case high:
		break;
	case low:
		break;
	}
	return auto_base;
}

AutoBase *AutoBase::getSelectedAuto() {
	eObstacle obstacle;
	eStartPos startPos;
	eGoalPos goalPos;

	readDIPSwitches(&obstacle, &startPos, &goalPos);
	return createSelectedAuto(obstacle, startPos, goalPos);
}

void AutoBase::readDIPSwitches(eObstacle *obstacle, eStartPos *sp, eGoalPos *goal) {
	std::vector<DigitalInput *> digitalInputs; // initialize digital input
	for (int i = DIP_START; i < DIP_END; ++i) {
		digitalInputs.push_back(new DigitalInput(i));
	}

	//calculate position
	*sp = (eStartPos)0; // start Position
	int adder = 1;
	for (int i = DIP_CHANNEL_POSITION_START; i < DIP_CHANNEL_POSITION_END;
			++i) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*sp = (eStartPos)((*sp) | adder);
		}
		adder = adder << 1;
	}
	//calculate obstacle
	*obstacle = (eObstacle)0;
	adder = 1;
	for (int i = DIP_CHANNEL_OBSTACLE_START; i < DIP_CHANNEL_OBSTACLE_END;
			i++) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*obstacle = (eObstacle)( (*obstacle) | adder);
		}
		adder = adder << 1;
	}
	//calculate goal
	*goal = (eGoalPos)0; // start Position
	adder = 1;
	for (int i = DIP_CHANNEL_GOAL_START; i < DIP_CHANNEL_GOAL_END; i++) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*goal = (eGoalPos)((*goal) | adder);
		}
		adder = adder << 1;
	}
	for (int i = DIP_START; i < DIP_END; ++i) {
		delete digitalInputs[i];
	}
}

