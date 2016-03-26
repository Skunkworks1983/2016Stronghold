/*
 * PIDWrapper.h
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */
#pragma once

#include <PIDSource.h>
#include <stddef.h>
#include <cstdbool>

class PIDController;
class PIDOutput;

class PIDWrapper {
private:
	PIDController *ptr = NULL;
	PIDOutput *output = NULL;
	PIDSource *source = NULL;
	float setpoint;
public:
	PIDWrapper(float p, float i, float d, float f, PIDSource *source, PIDOutput *output);
	void Enable();
	void Disable();
	void SetSetpoint(float setpoint);
	void SetPID(float p, float i, float d, float f = 0);
	void SetInputRange(float minimumInput, float maximumInput);
	void SetOutputRange(float minimumOutput, float maximumOutput);
	void SetContinuous(bool isContinuous);
	void SetPIDSourceType(PIDSourceType pidSource);
	bool IsEnabled();
	void Reset();
};



