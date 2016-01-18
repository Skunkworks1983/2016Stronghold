#ifndef SKUNK_ENCODER_H
#define SKUNK_ENCODER_H

#include "WPILib.h"
#include <CounterBase.h>
#include <LiveWindow/LiveWindowSendable.h>
#include <PIDSource.h>
#include <SensorBase.h>

class SkunkEncoder: public SensorBase,
		public CounterBase,
		public PIDSource,
		public LiveWindowSendable {
	SkunkEncoder(int dataPort, int signPort);
	~SkunkEncoder();
	int GetPosition();
	void update();
private:
	int current_position;
	DigitalInput *dataSource, *signSource;
};

#endif

