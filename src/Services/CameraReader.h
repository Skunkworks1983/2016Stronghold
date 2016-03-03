#ifndef CAMERAREADER_H
#define CAMERA_READER_H

#include <PIDSource.h>
#include <sys/socket.h>
#include <Services/Message.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstring>
#include <pthread.h>

class priority_mutex;
struct sockaddr_in;

#define PORTNUM 17800
#define MAXRCVLEN 2300
#define INVALID 4200

enum CameraMode {
	LEFTGOAL, MIDGOAL, RIGHTGOAL
};

class CameraReader: public PIDSource {
private:
	int len, mysocket;
	struct sockaddr_in dest;
	long counter = 0;
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	priority_mutex *mutex;

	static CameraReader *reader;
	bool reading = false;
	float lastLeftX = 0;
	float lastLeftY = 0;
	float lastMidX = 0;
	float lastMidY = 0;
	float lastRightX = 0;
	float lastRightY = 0;
	pthread_t thread;
	CameraMode currentMode = LEFTGOAL;

	CameraReader();
	~CameraReader();
	static void *update(void *);
public:
	static CameraReader *getCameraReader();
	void setCameraMode(CameraMode mode);
	void stopReading();
	void startReading();
	void startUp();
	void shutDown();
	float getLastLeftX();
	float getLastLeftY();
	float getLastMidX();
	float getLastMidY();
	float getLastRightX();
	float getLastRightY();

	bool isLastInvalid();

	double PIDGet();
};

#endif
