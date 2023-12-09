#include "main.h"



////////////////////

//backRightMotor - port 18
//frontRightMotor - port 10
//backLeftMotor - port 12
//frontLeftMotor - port 1

//ratchetMotor - port 13
//intakeMotor - port 9
//flywheelMotor - port 16
//armMotor - port 17

//////////////////
	

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor lF(18);
pros::Motor lB(19);
pros::Motor rF(16); 
pros::Motor rB(17); 

//other motors
pros::Motor rat(8);
pros::Motor intake(9);
pros::Motor fly(10);
pros::Motor arm(20);


pros::MotorGroup left({lF, lB});
pros::MotorGroup right({rF, rB});



lemlib::Drivetrain drivetrain(
	&left, //leftside motorgroup
	&right, //right side motorgroup
	13.25, //wheel track
	lemlib::Omniwheel::NEW_4, //wheel diameters
	200, //drivetrain rpm
	2 //chase power
);


lemlib::ControllerSettings linear(
	10, //P
	30, //D
	1,
	100,
	3,
	500,
	20
);

lemlib::ControllerSettings angular(
	5, //P
	10, //D
	1,
	100,
	3,
	500,
	20
);

lemlib::OdomSensors sensors(
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr //IMU
);

lemlib::Chassis chassis(drivetrain, linear, angular, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

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

/*
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
void autonomous() {	
	
   chassis.moveTo(-100, 100, 180, 1000, true); 
   
   

   
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
void opcontrol() {
	while (true) {
		int forward = -controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int yaw = -controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		if(controller.get_digital(E_CONTROLLER_DIGITAL_X)){ 
				fly.move_voltage(-12000);
		} else {
			fly.brake();
		}
		
		//intake
		if(controller.get_digital(E_CONTROLLER_DIGITAL_R1)){ 
				intake.move_voltage(12000);	
		} 
		else if(controller.get_digital(E_CONTROLLER_DIGITAL_R2)){ 
				intake.move_voltage(-12000);
		} else {
			intake.brake();
		}

		//arm
		if(controller.get_digital(E_CONTROLLER_DIGITAL_L1)){ 
				arm.move_voltage(12000);	
		} 
		else if(controller.get_digital(E_CONTROLLER_DIGITAL_L2)){ 
				arm.move_voltage(-12000);
		} else {
			arm.brake();
		}

		//ratchet
		if(controller.get_digital(E_CONTROLLER_DIGITAL_UP)){ 
				rat.move_voltage(1000);	
		} 
		else if(controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)){ 
				rat.move_voltage(-1000);
		} else {
			rat.brake();
		}
		
		chassis.arcade(yaw, forward);

		pros::delay(20);
	}
}
