/*
 * ControllerHandler.h
 *
 *  Created on: Mar 31, 2016
 *      Author: S-4020395
 */

#ifndef SRC_CONTROLLERS_CONTROLLERHANDLER_H_
#define SRC_CONTROLLERS_CONTROLLERHANDLER_H_

#include <Controllers/SkunkController.h>
#include <map>

class PIDOutput;
class PIDSource;
class SkunkController;

class ControllerHandler{
private:
	ControllerHandler();
	ControllerHandler(const ControllerHandler &);
	~ControllerHandler();

	std::map<unsigned, SkunkController*> controllers;
public:
	static ControllerHandler *getInstance();
	SkunkController *createController(unsigned index, double vGain, double aGain,
		double xGain, PIDOutput *output, PIDSource *source);
	SkunkController *getController(unsigned index);
};

#endif /* SRC_CONTROLLERS_CONTROLLERHANDLER_H_ */
