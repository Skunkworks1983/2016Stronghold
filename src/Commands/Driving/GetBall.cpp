/*
 * GetBall.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: S-4020395
 */

#include <Commands/Driving/GetBall.h>
#include <Services/CameraReader.h>
#include <Subsystems/Collector.h>
#include <cstdbool>

GetBall::GetBall(float speedTranslate) :
		speedTranslate(speedTranslate) {

}
void GetBall::Initialize() {

}
void GetBall::Execute() {

}
bool GetBall::IsFinished() {
	return collector->getBreakBeam()
			|| CameraReader::getCameraReader()->isBallInCollector();
}
void GetBall::End() {

}
void GetBall::Interrupted() {

}

