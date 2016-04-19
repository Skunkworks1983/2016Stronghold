#include <Commands/Driving/GoToBatter.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

#define TURN_BOUND_LEFT -60
#define TURN_BOUND_RIGHT 60

#define GO_STRAIGHT_TOLERANCE 6

#define TURN_SPEED .7
#define TURN_PERCENTAGE -.75
#define MOVE_TOWARD_SPEED .3
#define MOVE_TOWARD_PERCENT .5

GoToBatter::GoToBatter() :
		startPos(startPos) {
	Requires(drivebase);
	reader = CameraReader::getCameraReader();
}

// Called just before this Command runs the first time
void GoToBatter::Initialize() {
	SensorManager::getSensorManager()->ZeroYaw();
	startPos = AutoBase::getStartPos();

	switch(startPos){
	case lowBar:
		break;
	case two:
		break;
	case three:
		break;
	case four:
		break;
	case five:
		break;
	}
	state = Startup;
	adjacentInitialLeft = 0;
	adjacentInitialRight = 0;
	distance_adjacent = 0;
	LOG_INFO("Go to batter command has initialized");
}

// Called repeatedly when this Command is scheduled to run
void GoToBatter::Execute() {
	const double gyro_angle = SensorManager::getSensorManager()->getYaw();
	const double camera_angle = reader->getXAngle();

	//magic numbers galore
	const double angleY = reader->getYAngle();
	const double distance_away = 81 / tan(M_PI * (angleY / 180.0));

	const double corrected_camera_angle = reader->getCorrectedXAngle(distance_away);

	const double left_encoder = (SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() * DRIVEBASE_FOOT_PER_TICK)
			* 12;
	const double right_encoder = (SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() * DRIVEBASE_FOOT_PER_TICK)
			* 12;

	LOG_INFO(
			"gyro %f cam_angleX %f camAngleY %f distance %f leftEncDiff %f rightEncDiff %f distance_adjacent %f correctedAngle %f",
			gyro_angle, camera_angle, angleY, distance_away, fabs(left_encoder - adjacentInitialLeft),
			fabs(right_encoder - adjacentInitialRight), distance_adjacent, corrected_camera_angle);

	switch (state) {
	case Startup:
		LOG_INFO("GoToBatter State = Startup")
		;

		if (reader->getLastLeftX() != INVALID) {
			state = JustNowFound;
		} else {
			state = JustNowLost;
		}
		break;
	case JustNowFound:
		LOG_INFO("GoToBatter State = JustNowFound");

		distance_adjacent = distance_away
				* sin(M_PI * ((corrected_camera_angle + gyro_angle) / 180.0));

		if (fabs(distance_adjacent) > GO_STRAIGHT_TOLERANCE) {

			state = TurningToAdjacent;
			adjacentInitialYaw = gyro_angle;
			LOG_INFO("Setting adjacentInitialYaw to %f", gyro_angle);
		} else {
			LOG_INFO(
					"Angle %f is less than tolerance %d so going to move straight",
					corrected_camera_angle, GO_STRAIGHT_TOLERANCE)
			state = MovingToward;
		}
		break;
	case MovingAdjacent:
		LOG_INFO("GoToBatter State = MovingAdjacent")
		;

		if (fabs(left_encoder - adjacentInitialLeft) > fabs(distance_adjacent)
				|| fabs(right_encoder - adjacentInitialRight)
						> fabs(distance_adjacent)) {
			drivebase->setLeftSpeed(0.0);
			drivebase->setRightSpeed(0.0);
			state = TurningAwayFromAdjacent;
		} else {
			drivebase->setLeftSpeed(-.3);
			drivebase->setRightSpeed(-.3);
		}
		break;
	case TurningToAdjacent:
		LOG_INFO("GoToBatter State = TurningToAdjacent")
		;

		if (corrected_camera_angle < 0) {
			drivebase->setLeftSpeed(-TURN_SPEED);
			drivebase->setRightSpeed(TURN_SPEED);
		} else {
			drivebase->setLeftSpeed(TURN_SPEED);
			drivebase->setRightSpeed(-TURN_SPEED);
		}
		if (fabs(gyro_angle) > 90) {
			drivebase->setLeftSpeed(0);
			drivebase->setRightSpeed(0);
			state = MovingAdjacent;
			adjacentInitialLeft = left_encoder;
			adjacentInitialRight = right_encoder;

			LOG_INFO("InitialLeft %f InitialRight %f set", adjacentInitialLeft,
					adjacentInitialRight);
		}
		break;
	case TurningAwayFromAdjacent:
		LOG_INFO("GoToBatter State = TurningAwayFromAdjacent")
		;

		if (corrected_camera_angle < 0) {
			drivebase->setLeftSpeed(-TURN_SPEED);
			drivebase->setRightSpeed(TURN_SPEED);
		} else {
			drivebase->setLeftSpeed(TURN_SPEED);
			drivebase->setRightSpeed(-TURN_SPEED);
		}
		if (fabs(adjacentInitialYaw - gyro_angle) > 90) {
			drivebase->setLeftSpeed(0);
			drivebase->setRightSpeed(0);
			state = MovingToward;
		}
		break;
	case JustNowLost:
		LOG_INFO("GoToBatter State = JustNowLost")
		;

		state = SearchingLeft;
		break;
	case SearchingLeft:
		LOG_INFO("GoToBatter State = SearchingLeft")
		;

		if (reader->getLastLeftX() != INVALID) {
			LOG_INFO("Target Found at %f", reader->getLastLeftX());
			state = JustNowFound;
			break;
		} else {
			if (gyro_angle < TURN_BOUND_LEFT) {
				state = SearchingRight;
			}
			drivebase->setLeftSpeed(-TURN_SPEED);
			drivebase->setRightSpeed(TURN_SPEED);
		}
		break;
	case SearchingRight:
		LOG_INFO("GoToBatter State = SearchingRight")
		;

		if (reader->getLastLeftX() != INVALID) {
			LOG_INFO("Target Found at %f", reader->getLastLeftX());
			state = JustNowFound;
			break;
		} else {
			if (gyro_angle > TURN_BOUND_RIGHT) {
				state = JustNowLost;
			}
			drivebase->setLeftSpeed(TURN_SPEED);
			drivebase->setRightSpeed(-TURN_SPEED);
		}
		break;
	case MovingToward:
		LOG_INFO("GoToBatter State = MovingToward")
		;

		if (corrected_camera_angle > 0) {
			drivebase->setRightSpeed(-MOVE_TOWARD_SPEED);
			drivebase->setLeftSpeed(-MOVE_TOWARD_SPEED * MOVE_TOWARD_PERCENT);
		} else {
			drivebase->setRightSpeed(-MOVE_TOWARD_SPEED * MOVE_TOWARD_PERCENT);
			drivebase->setLeftSpeed(-MOVE_TOWARD_SPEED);
		}
		break;
	default:
		LOG_WARNING("GoToBatter is in default state!!")
		;

		state = JustNowLost;
		break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GoToBatter::IsFinished() {
	return state == AtBatter;
}

// Called once after isFinished returns true
void GoToBatter::End() {
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
	SensorManager::getSensorManager()->ZeroYaw();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GoToBatter::Interrupted() {
	End();
}
