#include <Commands/Driving/GoToBatter.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/MotorManager.h>
#include <Services/PIDWrapper.h>
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

#define SEARCH_SPEED .55
#define SEARCH_PERCENT -.75

#define MOVE_TOWARD_SPEED .35
#define MOVE_TOWARD_PERCENT .5

GoToBatter::GoToBatter() {
	Requires(drivebase);
	reader = CameraReader::getCameraReader();
	manager = MotorManager::getMotorManager();
	sensor = SensorManager::getSensorManager();

	pid = manager->getPID(PID_ID_DRIVEBASE_ROT);
}

// Called just before this Command runs the first time
void GoToBatter::Initialize() {
//	sensor->ZeroYaw();
	startPos = AutoBase::getStartPos();

	switch (startPos) {
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

	first = true;
}

// Called repeatedly when this Command is scheduled to run
void GoToBatter::Execute() {
	const double gyro_angle = sensor->getYaw();
	const double camera_angle = reader->getXAngle(0);

	//magic numbers galore
	const double angleY = reader->getYAngle(0);
	const double distance_away = 81 / tan(M_PI * (angleY / 180.0));

	const double corrected_camera_angle = reader->getCorrectedXAngle(
			distance_away);

	const double gyro_to_camera = SensorManager::wrapCheck(
			corrected_camera_angle + gyro_angle);

	const double left_encoder = (sensor->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() * DRIVEBASE_FOOT_PER_TICK)
			* 12;
	const double right_encoder = (sensor->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() * DRIVEBASE_FOOT_PER_TICK)
			* 12;

	LOG_INFO(
			"gyro %f cam_angleX %f camAngleY %f distance %f leftEncDiff %f rightEncDiff %f distance_adjacent %f correctedAngle %f",
			gyro_angle, camera_angle, angleY, distance_away,
			fabs(left_encoder - adjacentInitialLeft),
			fabs(right_encoder - adjacentInitialRight), distance_adjacent,
			corrected_camera_angle);

	switch (state) {
	case Startup:
		LOG_INFO("GoToBatter State = Startup")
		;

		if (reader->getGoal1X() != INVALID) {
			state = JustNowFound;
		} else {
			state = JustNowLost;
		}
		break;
	case JustNowFound:
		LOG_INFO("GoToBatter State = JustNowFound")
		;

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

		if (first) {
			drivebase->setLeftSpeed(-.3);
			drivebase->setRightSpeed(-.3);
			first = false;
		}

		if (fabs(left_encoder - adjacentInitialLeft) > fabs(distance_adjacent)
				|| fabs(right_encoder - adjacentInitialRight)
						> fabs(distance_adjacent)) {
			drivebase->setLeftSpeed(0.0);
			drivebase->setRightSpeed(0.0);
			first = true;
			state = TurningAwayFromAdjacent;
		}
		break;
	case TurningToAdjacent:
		LOG_INFO("GoToBatter State = TurningToAdjacent")
		;

		if (first) {
			pid->Reset();
			if (gyro_to_camera > 0) {
				pid->SetSetpoint(90);
				pid->Enable();
			} else {
				pid->SetSetpoint(-90);
				pid->Enable();
			}
			first = false;
		}
		if (fabs(pid->getError()) < 2.0) {
			pid->Disable();
			drivebase->setLeftSpeed(0);
			drivebase->setRightSpeed(0);
			first = true;
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

		if (first) {
			pid->Reset();
			pid->SetSetpoint(0);
			pid->Enable();
			first = false;
		}
		if (fabs(pid->getError()) < 2.0) {
			pid->Disable();
			drivebase->setLeftSpeed(0);
			drivebase->setRightSpeed(0);
			first = true;
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

		if (first) {
			pid->Reset();
			pid->SetSetpoint(TURN_BOUND_LEFT);
			pid->Enable();
			first = false;
		}

		if (reader->getGoal1X() != INVALID) {
			LOG_INFO("Target Found at %f", reader->getGoal1X());
			first = true;
			state = JustNowFound;
			break;
		} else {
			if (fabs(pid->getError()) < 2.0) {
				first = true;
				state = SearchingRight;
			}
		}
		break;
	case SearchingRight:
		LOG_INFO("GoToBatter State = SearchingRight")
		;

		if (first) {
			pid->Reset();
			pid->SetSetpoint(TURN_BOUND_RIGHT);
			pid->Enable();
		}

		if (reader->getGoal1X() != INVALID) {
			LOG_INFO("Target Found at %f", reader->getGoal1X());
			first = true;
			state = JustNowFound;
			break;
		} else {
			if (fabs(pid->getError()) < 2.0) {
				first = true;
				state = JustNowLost;
			}

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

void GoToBatter::changeState(BatterState state) {
	first = true;
	this->state = state;
}

// Make this return true when this Command no longer needs to run execute()
bool GoToBatter::IsFinished() {
	return state == AtBatter;
}

// Called once after isFinished returns true
void GoToBatter::End() {
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GoToBatter::Interrupted() {
	End();
}
