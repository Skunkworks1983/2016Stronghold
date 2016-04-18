#include <sys/socket.h>
#include <HAL/cpp/priority_mutex.h>
#include <Robot.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <cstdbool>
#include <cmath>
#include <iostream>

static const int imageWidth = 640;
static const int imageHeight = 480;

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
		return getLastLeftX() == INVALID;
	case MIDGOAL:
		return getLastMidX() == INVALID;
	case RIGHTGOAL:
		return getLastRightX() == INVALID;
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
	lastLeftX = 0;
	lastLeftY = 0;
	lastMidX = 0;
	lastMidY = 0;
	lastRightX = 0;
	lastRightY = 0;

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
			camera_reader->lastLeftX = 2
					* ((float) msg.posX1 / (float) imageWidth) - 1;
			camera_reader->lastLeftY =
					((float) msg.posY1 / (float) imageHeight);
		}
		if (msg.posX2 != INVALID) {

			camera_reader->lastMidX = 2
					* ((float) msg.posY2 / (float) imageWidth) - 1;
			camera_reader->lastMidY = ((float) msg.posY2 / (float) imageHeight);
		}
		if (msg.posX3 != INVALID) {
			camera_reader->lastRightX = 2
					* ((float) msg.posY3 / (float) imageWidth) - 1;
			camera_reader->lastRightY =
					((float) msg.posY3 / (float) imageHeight);
		}
		camera_reader->mutex->unlock();
	}
#endif
	pthread_detach(pthread_self());
	pthread_exit(NULL);

	return NULL;
}

float CameraReader::getLastLeftX() {
	mutex->lock();
	float tempLast = lastLeftX;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getLastLeftY() {
	mutex->lock();
	float tempLast = lastLeftY;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getLastMidX() {
	mutex->lock();
	float tempLast = lastMidX;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getLastMidY() {
	mutex->lock();
	float tempLast = lastMidY;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getLastRightX() {
	mutex->lock();
	float tempLast = lastRightX;
	mutex->unlock();
	return tempLast;
}

float CameraReader::getLastRightY() {
	mutex->lock();
	float tempLast = lastRightY;
	mutex->unlock();
	return tempLast;
}

bool CameraReader::isBallInShooter() {
	return ballInShooter;
}

double CameraReader::PIDGet() {
	switch (currentMode) {
	case LEFTGOAL:
		return getLastLeftX();
	case MIDGOAL:
		return getLastMidX();
	case RIGHTGOAL:
		return getLastRightX();
	}
	return 0.0;
}

double CameraReader::getXAngle() {
	if (getLastLeftX() != INVALID) {
		double angle = getLastLeftX() * (53.5 / 2);	//raspberry pi cam horizontal FOV
		return angle;
	} else {
		return INVALID;
	}
}

double CameraReader::getCorrectedXAngle(double distance) {
	if (getLastLeftX() != INVALID) {
		double pixelX = (((atan(7 / distance) * M_PI) / 180.0) / 53.5)
				+ getLastLeftX();
		double angle = pixelX * (53.5 / 2);	//raspberry pi cam horizontal FOV

		return angle;
	} else {
		return INVALID;
	}
}

double CameraReader::getCorrectedXAngle(){
	double dist = 81 / tan(M_PI * (getYAngle() / 180.0));

	return getCorrectedXAngle(dist);
}

double CameraReader::getYAngle() {
	if (getLastLeftY() != INVALID) {
		const double angle = (((double) (1 - getLastLeftY())) * 41.41) + 28.46;
		return angle;
	} else {
		return INVALID;
	}
}
