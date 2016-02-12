#ifndef ROBOTMAP_H
#define ROBOTMAP_H
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;
// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;
#define LIGHT_SENSOR_PORT 1




#define LINE_FOLLOW_P 1
#define LINE_FOLLOW_I 0
#define LINE_FOLLOW_D 0


#define OI_JOYSTICK_LEFT_PORT 0
#define OI_JOYSTICK_RIGHT_PORT 1
#define OI_OPERATOR_PORT 2


#define COLLECTOR_ROTATOR_MOTOR_1_PORT 0
#define COLLECTOR_ROTATOR_MOTOR_2_PORT 1
#define COLLECTOR_ROLLER_MOTOR_1_PORT 2
#define COLLECTOR_ROLLER_MOTOR_2_PORT 3

//MotorManager(ewe) Constants
#define MAX_MANAGED_MOTORS 20

#define DRIVEBASE_LEFTMOTOR_1_PORT 3
#define DRIVEBASE_LEFTMOTOR_2_PORT 4
#define DRIVEBASE_LEFTMOTOR_3_PORT 5

#define DRIVEBASE_RIGHTMOTOR_1_PORT 0
#define DRIVEBASE_RIGHTMOTOR_2_PORT 1
#define DRIVEBASE_RIGHTMOTOR_3_PORT 2

#define CLIMBER_PULLY_MOTOR_1_PORT 6
#define CLIMBER_PULLY_MOTOR_2_PORT 7
#define CLIMBER_PULLY_MOTOR_3_PORT 8
#define CLIMBER_PULLY_MOTOR_4_PORT 9

#define CLIMBER_ARM_MOTOR_PORT 10

#define MULTI_TOOL_MOTRO_1_PORT 11
#define MULTI_TOOL_MOTRO_2_PORT 12

#define COLLECTOR_MOTOR_PORT 13

#define SHOOTER_MOTOR_1_PORT 14
#define SHOOTER_MOTOR_2_PORT 15

#define DRIVEBASE_RIGHTENCODER_PORT 0
#define DRIVEBASE_LEFTENCODER_PORT 4

//Breach Buttons
#define OI_PORTCULLIS_BREACH_PORT 0
#define OI_BUTTON_BREACH_PORT 2
#define OI_CHEVAL_BREACH_PORT 1
#define OI_GENERAL_BREACH_PORT 3
#define POWER_DISTRIBUTION_PANEL_PORT 0

#define POWER_LEVEL_1 11
#define POWER_LEVEL_2 10
#define POWER_LEVEL_3 9

#define POWER_BROWNOUT_VOLTAGE 7
#define POWER_DRIVEBASE_VOLTAGE_WIDTH 0.5
#define POWER_VOLTAGE_WIDTH 1.5

#define COLLECTOR_TURNUP 1
#define COLLECTOR_TURNDOWN 0

//Buttons

//Collecting buttons
#define OI_COLLECT_BALL_PORT 4
#define OI_COLLECTOR_UP_PORT 5

//aiming buttons
#define OI_AIM_AT_GOAL_PORT 6

//shooting buttons
#define OI_SHOOT_LOW_PORT 7
#define OI_SHOOT_HIGH_PORT 8
#define OI_SPIN_UP_SHOOTER_PORT 9

//climbing buttons
#define OI_ROTATE_ARM_PORT 10
#define OI_ENGAGE_WINCH_PORT 11

//auto constants
#define CHEV_SPEED 0.5
#define CHEV_SHORTDIST 3
#define CHEV_DIST 5

#define LOGFILE_NAME "/U/robotLog"

#define CHEVAL_ENCODER_ROTATIONS 0
#define MOAT_ENCODER_ROTATIONS 0
#define ROCKWALL_ENCODER_ROTATIONS 0
#define RAMPART_ENCODER_ROTATIONS 0
#define ROUGHTERRAIN_ENCODER_ROTATIONS 0
#define PORTCULLIS_ENCODER_ROTATIONS 0
#define SALLYPORT_ENCODER_ROTATIONS 0
#define LOWBAR_ENCODER_ROTATIONS 0

#endif
