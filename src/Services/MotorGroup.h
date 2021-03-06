/*
 * MotorGroup.h
 *
 *  Created on: Mar 9, 2016
 *      Author: S-4020395
 */

#ifndef SRC_SERVICES_MOTORGROUP_H_
#define SRC_SERVICES_MOTORGROUP_H_

#include <PIDOutput.h>
#include <Services/Motor.h>
#include <vector>

class MotorGroup: public PIDOutput {
protected:
	std::vector<Motor*> motorList;
private:
	int c;
	float lastCurrent;
	unsigned brownoutCount;
public:
	std::vector<Motor*> & getMotorList();
	MotorGroup(std::vector<Motor*> motorgroup);
	virtual ~MotorGroup();
	void PIDWrite(float output);
	int getPID(Motor motor);
};

class ShooterRotatorGroup: public MotorGroup {
private:
	float realOutput = 0;
public:
	ShooterRotatorGroup(std::vector<Motor*> motorgroup);
	void PIDWrite(float output);
};

class DrivebaseMotorGroup: public MotorGroup {
private:
	unsigned log_count = 0;
public:
	DrivebaseMotorGroup(std::vector<Motor*> motorgroup);
	void PIDWrite(float output);

	static float lastOutput;
};

#endif /* SRC_SERVICES_MOTORGROUP_H_ */
