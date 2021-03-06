#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    rls,            sensorReflection)
#pragma config(Sensor, in2,    lls,            sensorReflection)
#pragma config(Sensor, dgtl9,  Button,         sensorTouch)
#pragma config(Sensor, dgtl10, sonar,          sensorSONAR_raw)
#pragma config(Sensor, I2C_1,  Motor1,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  Motor2,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  Motor3,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  Motor4,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           Motor1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           Motor2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Motor3,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Motor4,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           bucket,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rclaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           lclaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           nub,           tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)


//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////







void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;


	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop



	// User control code here, inside the loop


while (true)
	{
		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joystick values to update your motors, etc.
		// .....................................................................................
		int LX = vexRT[Ch1];
		int LY = vexRT[Ch2];
		int Rotate = vexRT[Ch4] * -1;
		/*
		Motor1 - BR
		Motor2 - BL
		Motor3 - FL
		Motor4 - FR
		*/
		motor[Motor1] = LY + LX + Rotate;
		motor[Motor2] = -(LY) + LX + Rotate;
		motor[Motor3] = -(LY) + -(LX) + Rotate;
		motor[Motor4] = LY + -(LX) + Rotate;
		if(vexRT[Btn6U] == 1){
			motor[nub] = 500;
		}
		else if(vexRT[Btn5U] == 1){
			motor[nub] = -500;
		}
		else if(vexRT[Btn6D] == 1){
			motor[nub] = 60;
		}
		else if(vexRT[Btn5D] == 1){
			motor[nub] = -60;
		}
		else{
			motor[nub] = 0;
		}

		if(vexRT[Btn7U] == 1){
			motor[lclaw] = 40;
			motor[rclaw] = -40;
		}
		else if(vexRT[Btn7D] == 1){
			motor[lclaw] = -20;
			motor[rclaw] = 20;
		}
		else{
			motor[lclaw] = motor[rclaw] = 0;
		}
		if(vexRT[Btn8D] == 1){
			motor[bucket] = -70;
		}
		else if(vexRT[Btn8U] == 1){
			motor[bucket] = 90;
		}
		else{
			motor[bucket] = 0;
		}
	}
}
