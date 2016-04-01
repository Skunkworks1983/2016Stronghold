/*
 * SkunkController.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: S-4020395
 */

#include <Controllers/SkunkController.h>
#include <HAL/cpp/priority_mutex.h>
#include <iostream>

SkunkController::SkunkController(double vGain, double aGain,
		double xGain, PIDOutput *output, PIDSource *source) :
		vGain(vGain), aGain(aGain), xGain(xGain), output(output), source(source) {

}

SkunkController::~SkunkController() {
	delete mutex;
	pthread_exit(NULL);
}

void SkunkController::calculate() {

}

void SkunkController::setup() {
	int rc = 0;
//	rc = pthread_create(&thread, NULL, update, (void*) this);
	if (rc) {
		std::cout << "Error:unable to create thread," << rc << std::endl;
	}
}
