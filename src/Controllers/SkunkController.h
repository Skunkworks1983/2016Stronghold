/*
 * SkunkSpacedController.h
 *
 *  Created on: Mar 31, 2016
 *      Author: S-4020395
 */

#ifndef SRC_CONTROLLERS_SKUNKCONTROLLER_H_
#define SRC_CONTROLLERS_SKUNKCONTROLLER_H_

#include <pthread.h>
#include <stddef.h>

class PIDOutput;
class PIDSource;
class priority_mutex;

class SkunkController {
private:
	double vGain = 0;
	double aGain = 0;
	double xGain = 0;
	PIDOutput *output = NULL;
	PIDSource *source = NULL;

	priority_mutex *mutex;
	pthread_t thread;
	static void *update(void *);

	void calculate();
	void setup();
public:
	SkunkController(double vGain, double aGain, double xGain,
			PIDOutput *output, PIDSource *source);
	~SkunkController();
};

#endif /* SRC_CONTROLLERS_SKUNKCONTROLLER_H_ */
