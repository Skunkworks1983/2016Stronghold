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

#define DRIVEBASE_RIGHTENCODER_PORT 0
#define DRIVEBASE_LEFTENCODER_PORT 4

#define COLLECTOR_TURNUP 1
#define COLLECTOR_TURNDOWN 0

//Buttons

#define OI_BUTTON_BREACH_PORT 2

#endif
