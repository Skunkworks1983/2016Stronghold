/*
 * GetBall.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: S-4020395
 */

#include <Commands/Driving/GetBall.h>
#include <Services/CameraReader.h>
#include <Subsystems/Shooter.h>
#include <cstdbool>

GetBall::GetBall(float speedTranslate) :
		speedTranslate(speedTranslate) {

}
void GetBall::Initialize() {

}
void GetBall::Execute() {

}
bool GetBall::IsFinished() {
	return shooter->getBreakBeam()
			|| CameraReader::getCameraReader()->isBallInShooter();
}
void GetBall::End() {

}
void GetBall::Interrupted() {

}

