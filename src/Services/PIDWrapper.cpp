/*
 * PIDWrapper.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#include <PIDController.h>
#include <PIDSource.h>
#include <Services/Logger.h>
#include <Services/PIDWrapper.h>
#include <cstdio>
#include <RobotMap.h>

PIDWrapper::PIDWrapper(float p, float i, float d, float f, PIDSource *source,
		PIDOutput *output) {
	ptr = new PIDController(p, i, d, f, source, output);

	LOG_DEBUG("Created PIDWrapper with %f, %f, %f", p, i, d);
}

void PIDWrapper::Enable() {
	ptr->Enable();
	LOG_DEBUG("PIDWrapper Enabled");
}

void PIDWrapper::Disable() {
	ptr->Disable();
	LOG_DEBUG("PIDWrapper Enabled");
}

void PIDWrapper::SetSetpoint(float setpoint) {
	ptr->SetSetpoint(setpoint);
	LOG_DEBUG("PIDWrapper SetSetpoint");
}

void PIDWrapper::SetPID(float p, float i, float d, float f) {
	char str[1024];
	sprintf(str, "PIDWrapper Setting PID values to %f, %f, %f, %f", p, i, d, f);
	Logger::getLogger()->log(str, Debug);
	ptr->SetPID(p, i, d, f);
}

void PIDWrapper::SetInputRange(float minimumInput, float maximumInput) {
	ptr->SetInputRange(minimumInput, maximumInput);
}

void PIDWrapper::SetOutputRange(float minimumOutput, float maximumOutput) {
	ptr->SetOutputRange(minimumOutput, maximumOutput);
}

void PIDWrapper::SetContinuous(bool isContinuous) {
	ptr->SetContinuous(isContinuous);
}

void PIDWrapper::SetPIDSourceType(PIDSourceType pidSource) {
	ptr->SetPIDSourceType(pidSource);
}

bool PIDWrapper::IsEnabled() {
	return ptr->IsEnabled();
}

void PIDWrapper::Reset() {
	ptr->Reset();
}

