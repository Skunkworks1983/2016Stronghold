#ifndef SRC_PORTCULLISAUTO_H_
#define SRC_PORTCULLISAUTO_H_

#include <Subsystems/Drivebase.h>
#include <Commandbase.h>
#include <Subsystems/Collector.h>
#include <Subsystems/SensorManager.h>

#define EPSILON .0005f

class PortcullisAuto: public CommandBase{
private:
	float speed;
	float distance;
	float turn; //how much you want them to turn
	float dt; //distant traveled
	float turning; //how much it turn
	bool firststop;
public:
	PortcullisAuto(float speed, float distance, float turn);
	void Initialize();
	~PortcullisAuto();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_PORTCULLISAUTO_H_ */
