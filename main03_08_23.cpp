#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Fuck PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define MOTOR_MAX_SPEED 100 // The motor has the 36 Gearset

void autonomous() {

	pros::Motor left_wheels (LEFT_WHEELS_PORT);
  	pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor

  	right_wheels.move_relative(1000, MOTOR_MAX_SPEED);
  	left_wheels.move_relative(1000, MOTOR_MAX_SPEED);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

// #define LEFT_WHEELS_PORT 1
// #define RIGHT_WHEELS_PORT 10

// std::int32_t pros::Controller::get_analog ÷÷( pros::controller_analog_e_t channel )
// prostd::int32_t motor_move ( const std::int8_t voltage )

/*
void opcontrol() {
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true);
  pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;
    left_wheels.move(left);
    right_wheels.move(right);

    pros::delay(2);
  }
}
*/
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10

void opcontrol() {
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
    right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));

    pros::delay(2);
  }
}


/*
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define ARM_PORT 8
#define CLAW_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'
#define ARM_LIMIT_SWITCH_PORT 'h'

void opcontrol() {
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true);
  pros::Motor arm (ARM_PORT, MOTOR_GEARSET_36); // The arm motor has the 100rpm (red) gearset
  pros::Motor claw (CLAW_PORT, MOTOR_GEARSET_36);

  pros::ADIDigitalIn left_bumper (LEFT_BUMPER_PORT);
  pros::ADIDigitalIn right_bumper (RIGHT_BUMPER_PORT);
  pros::ADIDigitalIn arm_limit (ARM_LIMIT_SWITCH_PORT);

  pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;

    if (left_bumper.get_value() || right_bumper.get_value()) {
      // One of the bump switches is currently pressed
      if (left < 0) {
        left = 0;
      }
      if (right < 0) {
        right = 0;
      }
    }
    left_wheels.move(left);
    right_wheels.move(right);

    if (master.get_digital(DIGITAL_R1)) {
      arm.move_velocity(100); // This is 100 because it's a 100rpm motor
    }
    else if (master.get_digital(DIGITAL_R2) && !arm_limit.get_value()) {
      arm.move_velocity(-100);
    }
    else {
      arm.move_velocity(0);
    }

    if (master.get_digital(DIGITAL_L1)) {
      claw.move_velocity(100);
    }
    else if (master.get_digital(DIGITAL_L2)) {
      claw.move_velocity(-100);
    }
    else {
      claw.move_velocity(0);
    }

    pros::delay(2);
  }
}

*/