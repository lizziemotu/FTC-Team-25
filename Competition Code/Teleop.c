#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeeker,       sensorI2CCustom)
#pragma config(Sensor, S3,     HTMC,           sensorI2CCustom)
#pragma config(Sensor, S4,     lightSensor,    sensorLightInactive)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveRight,    tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     driveLeft,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     grabberArm,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_2,     driveSide,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    gravityShelf,         tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    IRServo,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    Ramp,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "../library/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../library/sensors/drivers/hitechnic-compass.h"
#include "../library/sensors/drivers/lego-light.h"
#include "Lib/Lib12-13.c"


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  servo[gravityShelf] = SHELFDOWN;
  servo[IRServo] = IRDOWN;
	servo[Ramp] = RAMP_START;
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void forwarddrivetrain ()//The function containing the code to run the forward drivetrain teleop
{
	if(abs(joystick.joy1_y1) > 50)//If the absolute value of the right joystick is greater than 50 then:
 	{
        nMotorPIDSpeedCtrl[driveLeft]   = mtrSpeedReg;
 		motor[driveLeft] = joystick.joy1_y1;//run the right motor at the level of power that the input from the joystick indicates.
 	}
 	else
 	{
 		motor[driveLeft] = 0;//If the absolute value of the right joystick is less than 50, then stop the right motor.
    }

   if(abs(joystick.joy1_y2) > 50)//If the absolute value of the right joystick's x-axis is greater than 50 then:
   {
        nMotorPIDSpeedCtrl[driveRight]   = mtrSpeedReg;
 		motor[driveRight] = joystick.joy1_y2;//run the left motor at the level of power that the input from the joystick indicates.
   }
   else
   {
 		motor[driveRight] = 0;//If the absolute value of the right joystick's x-axis is less than 50, then stop the left motor.
   }
}

void sidewaysdrivetrain ()//The function containing the code to run the sideways drivetrain telop
{
   if (joy1Btn(8))//If button 8 is pressed
   {
        nMotorPIDSpeedCtrl[driveSide]   = mtrSpeedReg;
 		motor[driveSide] = -100;// drive the right motor at 100
   }
   else if (joy1Btn(7))
   {
        nMotorPIDSpeedCtrl[driveSide]   = mtrSpeedReg;
 		motor[driveSide] = 100;// drive the left motor at -100
   }
   else
   {
     motor[driveSide] = 0;
   }
}

void movegravityShelf ()
{
	int val;

    if (joy2Btn(5))
    {
		servo[gravityShelf] = SHELFUP;
    }

	if (joy2Btn(7))
	{
		servo[gravityShelf] = SHELFDOWN;
	}

	if (joy2Btn(2))
	{
		val = ServoValue[gravityShelf];
		val -= SHELFINCREMENT;
		servo[gravityShelf] = val;
	}

	if (joy2Btn(4))
	{
		val = ServoValue[gravityShelf];
		val += SHELFINCREMENT;
		servo[gravityShelf] = val;
	}
}

void IRarm()
{
	if(joy2Btn(6))
	{
		servo[IRServo] = IRUP;
	}
	else if(joy2Btn(8))
	{
	    servo[IRServo] = IRRING;
	}
}

void arm ()
{
		if (joy2Btn(1))
		{
			motor[grabberArm] = 50;
		}
		else if(joy2Btn(3))
		{
			motor[grabberArm] = -50;
		}
		else
		{
			motor[grabberArm] = 0;
		}
}
void ramp ()
{
    //ramp code
}


task main()
{
  initializeRobot();//call the initializeRobot function

  waitForStart();   // wait for start of tele-op phase

  while (true)//infinite loop. Put all code in here to keep it running for the whole match
  {
    getJoystickSettings(joystick);//Get joystick input

  	forwarddrivetrain();//call the forwarddrivetrain function
  	sidewaysdrivetrain();//call the sidewaysdrivetrain function
  	movegravityShelf();
  	IRarm();
  	arm();
  }
}