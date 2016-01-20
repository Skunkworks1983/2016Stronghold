#ifndef SKUNK_ENCODER_H
#define SKUNK_ENCODER_H

#include "WPILib.h"
#include <CounterBase.h>
#include <LiveWindow/LiveWindowSendable.h>
#include <PIDSource.h>
#include <SensorBase.h>

struct Data {
	int *counter;
	priority_mutex *m_mutex;
	DigitalInput * m_DataSource;
	DigitalInput * m_SignSource;
};

class SkunkEncoder: public PIDSource {
public:
	SkunkEncoder(int dataPort, int signPort, std::string name = "DEFAULT");
	virtual ~SkunkEncoder();
	int GetPosition();
	void Reset();
	double PIDGet();
	void post();
private:
	int current_position;
	DigitalInput *dataSource, *signSource;
	priority_mutex *mutex;
	Data *data;
	std::string name;
};

#endif

