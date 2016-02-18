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

class CameraReader : public PIDSource{
private:
	int len, mysocket;
	struct sockaddr_in dest;
	long counter = 0;
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	priority_mutex *mutex;

	static CameraReader *reader;
	bool reading = false;
	float lastX, lastY;
	pthread_t thread;
	CameraReader();
	~CameraReader();
	static void *update(void *);
public:
	static CameraReader *getCameraReader();
	void stopReading();
	void startReading();
	void startUp();
	void shutDown();
	float getLastX();
	float getLastY();
	double PIDGet();
};

#endif
