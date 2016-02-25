#include <Commands/Driving/TurnLeftEncoder.h>
#include <Services/Logger.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <RobotMap.h>
#include <cstdio>

TurnLeftEncoder::TurnLeftEncoder(double degrees) :
		degrees(degrees) {
	Requires(drivebase);
}

TurnLeftEncoder::~TurnLeftEncoder() {
}

void TurnLeftEncoder::Initialize() {
	initial = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet();
	double speed = .5;
	drivebase->setLeftSpeed(-speed);
	drivebase->setRightSpeed(speed);
}

void TurnLeftEncoder::Execute() {

}

bool TurnLeftEncoder::IsFinished() {
	double end = 3000;
	return fabs(
			(fabs(SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet())
					+ fabs(SensorManager::getSensorManager()->getSensor(
					SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet())) / 2
					- initial) > end * (degrees / 360.0);
}

void TurnLeftEncoder::End() {
	char str[1024];
	sprintf(str, "TurnDegreeEncoder ENDED!");
	writeToLogFile(LOGFILE_NAME, str);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

void TurnLeftEncoder::Interrupted() {
	End();
}
