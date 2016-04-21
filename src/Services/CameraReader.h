#ifndef CAMERA_READER_H
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
	bool ballInShooter = false;

	float xData[3];
	float yData[3];
	unsigned widthData[3];

	float targetAngleOffset[3] = {-60, 0, 60 };
	float targetXOffset[3] = {-12, 0, 12 };
	float targetYOffset[3] = {-6, 0, -6 };


	float goal1X = INVALID;
	float goal1Y = INVALID;
	unsigned goal1Width = INVALID;

	float goal2X = INVALID;
	float goal2Y = INVALID;
	unsigned goal2Width = INVALID;

	float goal3X = INVALID;
	float goal3Y = INVALID;
	unsigned goal3Width = INVALID;

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

	float getGoal1X();
	float getGoal1Y();
	unsigned getGoal1Width();

	float getGoal2X();
	float getGoal2Y();
	unsigned getGoal2Width();

	float getGoal3X();
	float getGoal3Y();
	unsigned getGoal3Width();

	bool tele = false;

	bool isLastInvalid();

	bool isBallInShooter();

	double getCorrectedXAngle(double distance);
	double getCorrectedXAngle(unsigned index);

	double getStraightDistance(double yValue);

	double getXAngle(unsigned index);
	double getYAngle(unsigned index);
	double getExpectedWidth(unsigned index);

	double PIDGet();
};

#endif
