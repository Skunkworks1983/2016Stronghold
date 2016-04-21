/*
 * PIDWrapper.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#include <PIDController.h>
#include <PIDOutput.h>
#include <RobotMap.h>
#include <Services/PIDWrapper.h>

PIDWrapper::PIDWrapper(float p, float i, float d, float f, PIDSource *source,
		PIDOutput *output) :
		output(output), source(source) {
	ptr = new PIDController(p, i, d, f, source, output);
	setpoint = 0;

	LOG_DEBUG("Created PIDWrapper with %f, %f, %f", p, i, d);
}

void PIDWrapper::Enable() {
	ptr->Enable();
	LOG_DEBUG("PIDWrapper Enabled");
}

void PIDWrapper::setAbsoluteTolerance(double value){
	ptr->SetAbsoluteTolerance(value);
	LOG_DEBUG("PIDWrapper absoluteTolerance %f", value);
}

void PIDWrapper::Disable() {
	ptr->Disable();
	LOG_DEBUG("PIDWrapper Disabled");
}

void PIDWrapper::SetSetpoint(float setpoint) {
	ptr->SetSetpoint(setpoint);
	LOG_DEBUG("PIDWrapper SetSetpoint");
}

void PIDWrapper::SetPID(float p, float i, float d, float f) {
	LOG_INFO("PIDWrapper Setting PID values to %f, %f, %f, %f", p, i, d, f);
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
	output->PIDWrite(0);
//	double p = ptr->GetP();
//	double i = ptr->GetI();
//	double d = ptr->GetD();
//	double f = ptr->GetF();
//	delete ptr;
//	ptr = new PIDController(p, i, d, f, source, output);
}

bool PIDWrapper::OnTarget(){
	return ptr->OnTarget();
}

float PIDWrapper::getError(){
	return ptr->GetError();
}

