#include <HAL/cpp/priority_mutex.h>

struct sockaddr_in;

#ifndef CAMERAREADER_H
#define CAMERA_READER_H

#include <sys/socket.h>
#include <Services/Message.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstring>
#include <pthread.h>

#define PORTNUM 17800
#define MAXRCVLEN 2300
#define INVALID 4200

class CameraReader{
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
};

#endif
