#include <sys/socket.h>
#include <Services/CameraReader.h>
#include <SmartDashboard/SmartDashboard.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <HAL/cpp/priority_mutex.h>

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
}

CameraReader::~CameraReader() {
	delete mutex;
	pthread_exit(NULL);
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

	bind(camera_reader->mysocket, (sockaddr *) &(camera_reader->dest),
			sizeof(camera_reader->dest));

	while (true) {
		Message msg;

		camera_reader->len = recv(camera_reader->mysocket, (char *) &msg,
				sizeof(msg), 0);
		camera_reader->mutex->lock();
		if (msg.posX1 != INVALID) {
			camera_reader->lastLeftX = 2 * (msg.posX1 / imageWidth) - 1;
			camera_reader->lastLeftY = 2 * (msg.posY1 / imageHeight) - 1;
			camera_reader->lastMidX = 2 * (msg.posY2 / imageWidth) - 1;
			camera_reader->lastMidY = 2 * (msg.posY2 / imageHeight) - 1;
			camera_reader->lastRightX = 2 * (msg.posY3 / imageWidth) - 1;
			camera_reader->lastRightY = 2 * (msg.posY3 / imageHeight) - 1;
		}
		camera_reader->mutex->unlock();
	}
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

