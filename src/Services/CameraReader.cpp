#include <sys/socket.h>
#include <Services/CameraReader.h>
#include <SmartDashboard/SmartDashboard.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <HAL/cpp/priority_mutex.h>

CameraReader::CameraReader() {
	thread = (pthread_t)NULL;
	lastX = 0;
	lastY = 0;
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

void CameraReader::startUp() {
	int rc = pthread_create(&thread, NULL, update, (void*) this);
	if (rc) {
		std::cout << "Error:unable to create thread," << rc << std::endl;
	}
}

void CameraReader::startReading() {
	reading = true;
	lastX = 0;
	lastY = 0;
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
		if (msg.posX != INVALID) {
			camera_reader->lastX = 2 * (msg.posX / 640.0) - 1;
			camera_reader->lastY = 2 * (msg.posY / 480.0) - 1;
		}
		camera_reader->mutex->unlock();
	}
}

float CameraReader::getLastX() {
	mutex->lock();
	float tempLastX = lastX;
	mutex->unlock();
	return tempLastX;
}

float CameraReader::getLastY() {
	mutex->lock();
	float tempLastX = lastX;
	mutex->unlock();
	return tempLastX;
}

double CameraReader::PIDGet(){
	return getLastX();
}


