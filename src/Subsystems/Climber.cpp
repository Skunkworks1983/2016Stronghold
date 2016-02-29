#include <CANSpeedController.h>
#include <CANTalon.h>
#include <PIDController.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Servo.h>
#include <Subsystems/Climber.h>
#include <TuningValues.h>

Climber::Climber() :
		Subsystem("Climber") {
	servo = new Servo(CLIMBER_SERVO_PORT);

	/*armMotor = new CANTalon(CLIMBER_ARM_MOTOR_PORT);
	armMotor->Reset();
	armMotor->SetEncPosition(0);
	armMotor->SetPIDSourceType(PIDSourceType::kDisplacement);
	armMotor->SetControlMode(CANTalon::ControlMode::kPosition);
	armMotor->SetPID(CLIMBER_ARM_P, CLIMBER_ARM_I,
	CLIMBER_ARM_D);*/
}

Climber::~Climber() {

}

void Climber::InitDefaultCommand() {

}

void Climber::setServoAngle(float angle) {
	servo->SetAngle(angle);
}

float Climber::getServoAngle() {
	return servo->GetAngle();
}

void Climber::setServoSpeed(float speed) {
	servo->Set(speed);
	//servo->SetSpeed(speed);
}

void Climber::setWinchSpeed(float winchSpeed) {
	MotorManager* motorManager = MotorManager::getMotorManager();
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_1_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_2_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_3_PORT, winchSpeed);
	motorManager->setSpeed(CLIMBER_WINCH_MOTOR_4_PORT, winchSpeed);
}

void Climber::setSetpoint(float position) {
	armMotor->SetSetpoint(position);
	//armMotor->Set(position);
	armMotor->EnableControl();
}

void Climber::disablePID() {
	armMotor->Disable();
}
