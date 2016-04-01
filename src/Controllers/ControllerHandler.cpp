/*
 * ControllerHandler.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: S-4020395
 */

#include <Controllers/ControllerHandler.h>
#include <PIDOutput.h>
#include <PIDSource.h>

ControllerHandler::ControllerHandler() {

}

ControllerHandler *ControllerHandler::getInstance() {
	static ControllerHandler *handler = new ControllerHandler();
	return handler;
}

SkunkController *ControllerHandler::createController(unsigned index,
		double vGain, double aGain, double xGain, PIDOutput *output,
		PIDSource *source) {
	SkunkController *controller = new SkunkController(vGain, aGain,
			xGain, output, source);

	controllers[index] = controller;

	return controller;
}

SkunkController *ControllerHandler::getController(unsigned index){
	if(controllers.count(index) != 0){
		return controllers[index];
	}
	return NULL;
}

