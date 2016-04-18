#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#define ROBOT_NAME "VanillaThunder"
#define PRACTICEBOT 1

#include "TuningValues.h"

#define USE_DRIVEBASE 1
#define USE_CLIMBER 1
#define USE_SHOOTER 1
#define USE_ARM 1

#define USE_LOGGING 1

#define USE_GYRO 1
#define USE_CAMERA 1

#define USE_GAMEPAD 0

#define POWER_DISTRIBUTION_PANEL_PORT 0

#define DIP_CHANNEL_POSITION_START 1
#define DIP_CHANNEL_POSITIONS 3
#define DIP_CHANNEL_POSITION_END 	DIP_CHANNEL_POSITION_START 	+ DIP_CHANNEL_POSITIONS
#define DIP_CHANNEL_OBSTACLE_START 	DIP_CHANNEL_POSITION_END
#define DIP_CHANNEL_OBSTACLES 3
#define DIP_CHANNEL_OBSTACLE_END 	DIP_CHANNEL_OBSTACLE_START 	+ DIP_CHANNEL_OBSTACLES
#define DIP_CHANNEL_GOAL_START 		DIP_CHANNEL_OBSTACLE_END
#define DIP_CHANNEL_GOALS 1
#define DIP_CHANNEL_GOAL_END 		DIP_CHANNEL_GOAL_START 		+ DIP_CHANNEL_GOALS

#define DIP_START DIP_CHANNEL_POSITION_START
#define DIP_END   DIP_CHANNEL_GOAL_END

/**
 * Power
 */

#define CIM_MAX_CURRENT 133
#define MINI_CIM_MAX_CURRENT 86
#define RS775_MAX_CURRENT 30

#define OVER_MAX_TIME 1000000
#define MAX_STOP_TIME 1000000

/**
 * OI
 */

#define OI_JOYSTICK_LEFT_PORT 0
#define OI_JOYSTICK_RIGHT_PORT 1
#define OI_JOYSTICK_OPERATOR_PORT 2

#define OI_JOYSTICK_GAMEPAD_PORT 0

/**
 * DriveBase
 */

#define DRIVEBASE_LEFTMOTOR_1_PORT 0
#define DRIVEBASE_LEFTMOTOR_2_PORT 1
#define DRIVEBASE_LEFTMOTOR_3_PORT 2

#define DRIVEBASE_RIGHTMOTOR_1_PORT 13
#define DRIVEBASE_RIGHTMOTOR_2_PORT 14
#define DRIVEBASE_RIGHTMOTOR_3_PORT 15

#define DRIVEBASE_RIGHT_ENCODER_PORT 13 //CAN switched it to 2, orig is 1
#if PRACTICEBOT
#define DRIVEBASE_LEFT_ENCODER_PORT 2
#else
#define DRIVEBASE_LEFT_ENCODER_PORT 1
#endif

/**
 * Shooter Rotation
 */

#define COLLECTOR_ROTATOR_MOTOR_LEFT_PORT 3
#define COLLECTOR_ROTATOR_MOTOR_RIGHT_PORT 12

#define COLLECTOR_ROLLER_MOTOR_1_PORT 11
#define COLLECTOR_ROLLER_ENCODER_PORT 11

#define COLLECTOR_KICKER_MOTOR_PORT 4

#define COLLECTOR_ROTATOR_TOLERANCE 15
#define COLLECTOR_BREAK_BEAM_PORT 0

#define COLLECTOR_ROTATION_TICKS_PER_DEGREE (3565/135)

/**
 * Climber
 */

#define CLIMBER_WINCH_MOTOR_1_PORT 4
#define CLIMBER_WINCH_MOTOR_2_PORT 5
#define CLIMBER_WINCH_MOTOR_3_PORT 6
#define CLIMBER_WINCH_MOTOR_4_PORT 7

#define CLIMBER_WINCH_ENCODER_PORT 5

#define CLIMBER_ARM_MOTOR_PORT 8
#define CLIMBER_ARM_ENCODER_PORT CLIMBER_ARM_MOTOR_PORT
#define CLIMBER_ARM_DEGREES_TO_ENCODER_TICKS 1.5f

#define CLIMBER_SERVO_PORT 0

/**
 * Shooter
 */

#define SHOOTER_MOTOR_LEFT_PORT 9
#define SHOOTER_MOTOR_RIGHT_PORT 10

#define SHOOTER_MOTOR_LEFT_ENCODER_PORT 9
//right side if you are robot with collector down
#define SHOOTER_MOTOR_RIGHT_ENCODER_PORT 10

#define SHOOTER_ENCODER_TICKS_PER_REV 4096

/**
 * OI Ports
 */

/**
 * Breach Buttons
 */

#define OI_PORTCULLIS_BREACH_PORT 0
#define OI_BUTTON_BREACH_PORT 2
#define OI_CHEVAL_BREACH_PORT 1
#define OI_GENERAL_BREACH_PORT 3

/**
 * Collecting Buttons
 */

#define OI_COLLECT_BALL_PORT 4
#define OI_COLLECTOR_UP_PORT 5

/*
 * Aiming Buttons
 */

#define OI_AIM_AT_GOAL_PORT 6

/**
 * Shooting Buttons
 */

#define OI_SHOOT_LOW_PORT 7
#define OI_SHOOT_HIGH_PORT 8
#define OI_SPIN_UP_SHOOTER_PORT 9

/**
 * Climbing Buttons
 */

#define OI_ROTATE_ARM_PORT 10
#define OI_ENGAGE_WINCH_PORT 11

//auto constants

#define LOGFILE_NAME "/U/robotLog"
#define LOGFILE_PIDS "/U/pids"

#define CHEVAL_ENCODER_TICKS 0
#define MOAT_ENCODER_TICKS 0
#define ROCKWALL_ENCODER_TICKS 0
#define RAMPART_ENCODER_TICKS 0
#define ROUGHTERRAIN_ENCODER_TICKS 0
#define PORTCULLIS_ENCODER_TICKS 0
#define SALLYPORT_ENCODER_TICKS 0
#define LOWBAR_ENCODER_TICKS 0

#define CHEVAL_SPEED 1
#define MOAT_SPEED 1
#define ROCKWALL_SPEED 1
#define RAMPART_SPEED 1
#define ROUGHTERRAIN_SPEED 1
#define PORTCULLIS_SPEED 1
#define SALLYPORT_SPEED 1
#define LOWBAR_SPEED 1

#define TICKS_REVOLUTION 360
#define DRIVEBASE_FOOT_PER_TICK 0.0025

#define DEBUG false

#include <Services/Logger.h>

#define LOG_DEBUG(...) {\
			char buf[1024];\
			sprintf(buf, __VA_ARGS__);\
			Logger::getLogger()->log(buf, Debug);}

#define LOG_INFO(...) {\
			char buf[1024];\
			sprintf(buf, __VA_ARGS__);\
			Logger::getLogger()->log(buf, Info);}

#define LOG_WARNING(...) {\
			char buf[1024];\
			sprintf(buf, __VA_ARGS__);\
			Logger::getLogger()->log(buf, Warning);}

#define LOG_ERROR(...) {\
			char buf[1024];\
			sprintf(buf, __VA_ARGS__);\
			Logger::getLogger()->log(buf, Error);}

#define LOG_RECORD(...) {\
			char buf[1024];\
			sprintf(buf, __VA_ARGS__);\
			Logger::getLogger()->log(buf, Record);}

#endif
