/*
 * ShooterMotor.h
 *
 *  Created on: Mar 13, 2016
 *      Author: S-4020395
 */

#ifndef SRC_SUBSYSTEMS_SHOOTERMOTOR_H_
#define SRC_SUBSYSTEMS_SHOOTERMOTOR_H_

#include <PIDOutput.h>
#include <PIDSource.h>
#include <stddef.h>

#define USE_CAN_PID 0

class CANTalon;

class PIDController;

class ShooterMotor : public PIDOutput, public PIDSource{
public:
	enum ShooterSide{
		LEFT,RIGHT
	};
	ShooterMotor(ShooterSide side, double p, double i, double d);
	virtual ~ShooterMotor();

	void Disable();
	void Enable();
	void Reset();
	void SetSetpoint(float setpoint);
	void PIDWrite(float output);
	double PIDGet();
	void setPID(float p, float i, float d);
	double getSetpoint();
	double getError();
	bool isEnabled();
	float getOutputPercentage();
private:
	ShooterSide side;
	PIDController *controller = NULL;
	CANTalon *talon = NULL;
	float setpoint = 0.0;
	double oldOutput = 0.0;
	double lastSpeed = 0.0;
};

#endif /* SRC_SUBSYSTEMS_SHOOTERMOTOR_H_ */
