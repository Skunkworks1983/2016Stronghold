#include <Commands/Autonomous/AutoBase.h>
#include <DigitalInput.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <cstdbool>
#include <cstdio>
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
	case Obstacle_lowBar:
		auto_base->AddSequential(AutoBase::doLowB());
		break;

	case Obstacle_cheval:
		//auto_base->AddSequential(AutoBase::doCheval());
		break;

	case Obstacle_moat:
		//auto_base->AddSequential(AutoBase::doMoat());
		break;

	case Obstacle_rough:
		auto_base->AddSequential(AutoBase::doRoughT());
		break;

	case Obstacle_ramppart:
		//auto_base->AddSequential(AutoBase::doRamP());
		break;

	case Obstacle_rockwall:
		//auto_base->AddSequential(AutoBase::doRockW());
		break;

	case Obstacle_portcullis:
		//auto_base->AddSequential(AutoBase::doPortC());
		break;
	}
	/*const float driveSpeed = .5;
	 //203.73 ticks per foot
	 switch (goalPos) {
	 case high:
	 switch (startPos) {
	 case spy: //drive forward
	 auto_base->AddSequential(new DriveForward(3.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-135));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-20));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 break;
	 case lowBar: // drive slightly left then line up for goal
	 auto_base->AddSequential(new DriveForward(3.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-135));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-20));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 ;
	 break;
	 case posZero: // drive left then line up for goal
	 auto_base->AddSequential(new TurnDegree(-20));
	 auto_base->AddSequential(new DriveForward(5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(3.49, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(15));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 break;
	 case posOne: // drive forward for high goal, left for low goal
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-90));
	 auto_base->AddSequential(new DriveForward(4, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(5));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 break;
	 case posTwo: // drive right then line up for goal
	 auto_base->AddSequential(new TurnDegree(-15));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(15));
	 auto_base->AddSequential(new DriveForward(3, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(5));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 break;
	 case posThree: // drive slightly right then line up for goal
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(1.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-90));
	 auto_base->AddSequential(new DriveForward(4.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-75));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 break;
	 }
	 case low:
	 switch (startPos) {
	 case spy: //drive forward
	 auto_base->AddSequential(new DriveForward(4, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-135));
	 auto_base->AddSequential(new DriveForward(0.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-20));
	 auto_base->AddSequential(new DriveForward(5, driveSpeed));
	 break;
	 case lowBar: // drive slightly left then line up for goal
	 auto_base->AddSequential(new DriveForward(5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(45));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(50));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 break;
	 case posZero: // drive left then line up for goal
	 auto_base->AddSequential(new TurnDegree(-20));
	 auto_base->AddSequential(new DriveForward(4, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(15));
	 auto_base->AddSequential(new DriveForward(4, driveSpeed));
	 break;
	 case posOne: // drive forward for high goal, left for low goal
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-90));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(5));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 break;
	 case posTwo: // drive right then line up for goal
	 auto_base->AddSequential(new TurnDegree(-15));
	 auto_base->AddSequential(new DriveForward(0.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(15));
	 auto_base->AddSequential(new DriveForward(1, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(5));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 break;
	 case posThree: // drive slightly right then line up for goal
	 auto_base->AddSequential(new TurnDegree(90));
	 auto_base->AddSequential(new DriveForward(1.5, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-90));
	 auto_base->AddSequential(new DriveForward(4.4, driveSpeed));
	 auto_base->AddSequential(new TurnDegree(-75));
	 auto_base->AddSequential(new DriveForward(2.5, driveSpeed));
	 break;
	 }
	 break;
	 }*/
	return auto_base;
}

AutoBase * AutoBase::getSelectedAuto() {
	eObstacle obstacle;
	eStartPos startPos;
	eGoalPos goalPos;

	//readDIPSwitches(&obstacle, &startPos, &goalPos);
	readDIPSwitchedObstacle(&obstacle);
	return createSelectedAuto(obstacle, startPos, goalPos);
}

void AutoBase::readDIPSwitchedObstacle(eObstacle *obstacle) {
	char str[1024];
	sprintf(str, "Read Switched Obstacle start");
	Logger::getLogger()->log(str, Info);
	std::vector<DigitalInput *> digitalInputs; // initialize digital input

	for (int i = 1; i < 4; i++) {
		digitalInputs.push_back(new DigitalInput(i));
	}

	//calculate obstacle
	*obstacle = (eObstacle) 0;
	int adder = 1;
	for (unsigned i = 0; i < digitalInputs.size(); i++) {
		bool isSet = digitalInputs[i]->Get();
		sprintf(str, "index %u bool %u", i, isSet);
		Logger::getLogger()->log(str, Info);
		if (isSet) {
			*obstacle = (eObstacle) ((*obstacle) | adder);
		}
		adder = adder << 1;
	}
	sprintf(str, "obstacle selected %d", (*obstacle));
	Logger::getLogger()->log(str, Info);
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
	//calculate goal
	*goal = (eGoalPos) 0; // start Position
	adder = 1;
	for (int i = DIP_CHANNEL_GOAL_START; i < DIP_CHANNEL_GOAL_END; i++) {
		bool isSet = digitalInputs[i]->Get();
		if (isSet) {
			*goal = (eGoalPos) ((*goal) | adder);
		}
		adder = adder << 1;
	}
	for (int i = DIP_START; i < DIP_END; ++i) {
		delete digitalInputs[i];
	}
}

