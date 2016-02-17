#pragma once

class Shooter: public Subsystem{

private:
	SensorManager * sensorManager;
	MotorManager *motorManager;

	//this is the best code ever - Tucker Bowlin 2016
public:
	Shooter();
	void activateShooter(bool active);
	void setShooterSpeed(float speed);
	float getSpeed();


};
