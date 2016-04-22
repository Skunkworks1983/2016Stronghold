#include <sys/socket.h>
#include <HAL/cpp/priority_mutex.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/SensorManager.h>
#include <cmath>
#include <cstdbool>
#include <iostream>

static const int imageWidth = 640;
static const int imageHeight = 480;

#define FOV_DEG_X 53.5
#define FOV_DEG_Y 41.41

#define CAM_ANGLE_DEG 40.0 - (FOV_DEG_Y / 2.0)
#define CAM_HEIGHT_INCHES 11.0

#define TOWER_HEIGHT 92.0
#define TARGET_WIDTH_INCHES 20.0

#define DEG(x) (x * 180.0) / M_PI
#define RAD(x) (x * M_PI) / 180.0

CameraReader::CameraReader() {
	thread = (pthread_t) NULL;
	len = -1;
	mysocket = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&dest, 0, sizeof(dest)); /* zero the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl(0); /* Listen on all interfaces */
	dest.sin_port = htons(PORTNUM); /* set destination port number */
	mutex = new priority_mutex();

	tele = false;

	//startUp();
}

CameraReader::~CameraReader() {
	delete mutex;
}

CameraReader *CameraReader::getCameraReader() {
	static CameraReader *reader = new CameraReader();
	return reader;
}

bool CameraReader::isLastInvalid() {
	switch (currentMode) {
	case LEFTGOAL:
		return getGoal1X() == INVALID;
	case MIDGOAL:
		return getGoal2X() == INVALID;
	case RIGHTGOAL:
		return getGoal3X() == INVALID;
	}
	return true;
}

void CameraReader::setCameraMode(CameraMode mode) {
	currentMode = mode;
}

void CameraReader::startUp() {
	int rc = pthread_create(&thread, NULL, update, (void*) this);
	if (rc) {
		std::cout << "Error:unable to create thread," << rc << std::endl;
	}
}

void CameraReader::startReading() {
	reading = true;
	goal1X = 0;
	goal1Y = 0;
	goal1Width = 0;

	goal2X = 0;
	goal2Y = 0;
	goal2Width = 0;

	goal3X = 0;
	goal3Y = 0;
	goal3Width = 0;
}

unsigned CameraReader::getGoal1Width() {
	mutex->lock();
	float tempLast = goal1Width;
	mutex->unlock();
	return tempLast;
}

unsigned CameraReader::getGoal2Width() {
	mutex->lock();
	float tempLast = goal2Width;
	mutex->unlock();
	return tempLast;
}

unsigned CameraReader::getGoal3Width() {
	mutex->lock();
	float tempLast = goal3Width;
	mutex->unlock();
	return tempLast;
}

void CameraReader::stopReading() {
	reading = false;
}

void *CameraReader::update(void *d) {
	CameraReader *camera_reader = (CameraReader*) d;
#if USE_CAMERA
	bind(camera_reader->mysocket, (sockaddr *) &(camera_reader->dest),
			sizeof(camera_reader->dest));
	while (true) {
		Message msg;

		if (camera_reader->tele) {
			//break;	//TODO: remove this
		}

		int len = recv(camera_reader->mysocket, (char *) &msg, sizeof(msg), 0);

		camera_reader->mutex->lock();

		if (msg.posX1 != INVALID) {
			camera_reader->goal1X = 2 * ((float) msg.posX1 / (float) imageWidth)
					- 1;
			camera_reader->goal1Y = ((float) msg.posY1 / (float) imageHeight);
			camera_reader->goal1Width = msg.width1;
		} else {
			camera_reader->goal1X = INVALID;
			camera_reader->goal1Y = INVALID;
			camera_reader->goal1Width = INVALID;
		}
		if (msg.posX2 != INVALID) {

			camera_reader->goal2X = 2 * ((float) msg.posY2 / (float) imageWidth)
					- 1;
			camera_reader->goal2Y = ((float) msg.posY2 / (float) imageHeight);
			camera_reader->goal2Width = msg.width2;
		} else {
			camera_reader->goal2X = INVALID;
			camera_reader->goal2Y = INVALID;
			camera_reader->goal2Width = INVALID;
		}
		if (msg.posX3 != INVALID) {
			camera_reader->goal3X = 2 * ((float) msg.posY3 / (float) imageWidth)
					- 1;
			camera_reader->goal3Y = ((float) msg.posY3 / (float) imageHeight);
			camera_reader->goal3Width = msg.width3;
		} else {
			camera_reader->goal3X = INVALID;
			camera_reader->goal3Y = INVALID;
			camera_reader->goal3Width = INVALID;
		}

		camera_reader->mutex->unlock();
	}
#endif
	pthread_detach(pthread_self());
	pthread_exit(NULL);

	return NULL;
}

float CameraReader::getGoal1X() {
	mutex->lock();
	float tempLast = goal1X;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getGoal1Y() {
	mutex->lock();
	float tempLast = goal1Y;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getGoal2X() {
	mutex->lock();
	float tempLast = goal2X;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getGoal2Y() {
	mutex->lock();
	float tempLast = goal2Y;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getGoal3X() {
	mutex->lock();
	float tempLast = goal3X;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getGoal3Y() {
	mutex->lock();
	float tempLast = goal3Y;
	mutex->unlock();
	return tempLast;
}

bool CameraReader::isBallInShooter() {
	return ballInShooter;
}

double CameraReader::PIDGet() {
	switch (currentMode) {
	case LEFTGOAL:
		return getGoal1X();
	case MIDGOAL:
		return getGoal2X();
	case RIGHTGOAL:
		return getGoal3X();
	}
	return 0.0;
}

double CameraReader::getXAngle(unsigned index) {
	if (getGoal1X() != INVALID) {
		double angle = getGoal1X() * (53.5 / 2); //raspberry pi cam horizontal FOV
		return angle;
	} else {
		return INVALID;
	}
}

double CameraReader::getCorrectedXAngle(double distance) {
	if (getGoal1X() != INVALID) {
		double pixelX = (((atan(7 / distance) * M_PI) / 180.0) / 53.5)
				+ getGoal1X();
		double angle = pixelX * (53.5 / 2);	//raspberry pi cam horizontal FOV

		return angle;
	} else {
		return INVALID;
	}
}

double CameraReader::getCorrectedXAngle(unsigned index) {
	double dist = 81 / tan(M_PI * (getYAngle(index) / 180.0));

	return getCorrectedXAngle(dist);
}

double CameraReader::getYAngle(unsigned index) {
	if (getGoal1Y() != INVALID) {
		const double angle = (((double) (1 - getGoal1Y())) * 41.41) + 28.46;
		return angle;
	} else {
		return INVALID;
	}
}

double CameraReader::getStraightDistance(double yValue) {
	const double angle = yValue * FOV_DEG_Y + CAM_ANGLE_DEG;
	return TOWER_HEIGHT - CAM_HEIGHT_INCHES / sin(M_PI * (angle / 180.0));
}

double CameraReader::getExpectedWidth(unsigned index) {
	const double x = xData[index];
	const double y = yData[index];

	const double dist = getStraightDistance(y);

	const double angleToTarget = getCorrectedXAngle(index)
					+ SensorManager::getSensorManager()->getYaw();

	const double angularWidth = 2*DEG(atan(.5 * TARGET_WIDTH_INCHES / dist));
	const double pixelWidth = (angularWidth / FOV_DEG_X) * imageWidth;

	return pixelWidth * fabs(cos(RAD(angleToTarget + 0)));

	return 0;
}
