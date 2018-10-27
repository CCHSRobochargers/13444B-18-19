#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           backright,     tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port3,           backleft,      tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port5,           forks,         tmotorVex393_MC29, PIDControl, encoderPort, I2C_5)
#pragma config(Motor,  port6,           frontleft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           frontright,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftarm,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           rightarm,      tmotorVex393_MC29, PIDControl, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

static const float ticksPerInch = 1.01 * (627.2 / (4.1 * PI));
//adjust to compensate for wheel slip

static const float ticksPerDeg = 0.95 * (ticksPerInch * 17.5 * PI) / 360.0;

static const float ticksPerArmInch = 85.0;

static const float ticksPerForkInch = 94.0;

void move(float dist, int speed, bool hold)
{
	resetMotorEncoder(backright);
	resetMotorEncoder(backleft);

	setMotorTarget(backright, dist*ticksPerInch, speed, hold);
	setMotorTarget(backleft, dist*ticksPerInch, speed, hold);

	while (!getMotorTargetCompleted(backright) && !getMotorTargetCompleted(backleft))
		wait1Msec(10);
}

void spin(float deg, int speed, bool hold)
{
	resetMotorEncoder(backright);
	resetMotorEncoder(backleft);

	setMotorTarget(backright, deg*ticksPerDeg, speed, hold);
	setMotorTarget(backleft, -deg*ticksPerDeg, speed, hold);

	while (!getMotorTargetCompleted(backright) && !getMotorTargetCompleted(backleft))
		wait1Msec(10);
}

void arm(float dist, int speed, bool hold)
{
	resetMotorEncoder(rightarm);
	resetMotorEncoder(leftarm);

	setMotorTarget(rightarm, dist*ticksPerArmInch, speed, hold);
	setMotorTarget(leftarm, dist*ticksPerArmInch, speed, hold);

	while (!getMotorTargetCompleted(rightarm) && !getMotorTargetCompleted(leftarm))
		wait1Msec(10);
}

void fork(float dist, int speed, bool hold)
{
	resetMotorEncoder(forks);

	setMotorTarget(forks, dist*ticksPerForkInch, speed, hold);

	while (!getMotorTargetCompleted(forks))
		wait1Msec(10);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...

	slaveMotor(frontright, backright);
	slaveMotor(frontleft, backleft);
	//make the front motors copy what the back motors do because they don't have encoders

	motor[backleft] = 0;
	motor[backright] = 0;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//distance(50 speed) is all the way up for the arm
//10 distance(50 speed)is all the way up for the forks
//positive dist is left for spin
task autonomous()
{
	fork(-10, 50, false);  //red flag
	move(42, 127, false);
	fork(8, 50, true);
	/*
	fork(-10, 50, false);  //red flag
	move(12, 127, false);
	spin(90, 127, false);
	move(48, 127, false);

	fork(-10, 50, false);	//red platform
	spin(90, 127, false);
	move(24, 127, false);
	spin(-90, 127, false);
	move(48, 127, false);

	fork(-10, 50, false);  //blue flag
	move(48, 127, false);
	spin(-90, 127, false);
	move(48, 127, false);

	fork(-10, 50, false);  //blue platform
	spin(-90, 127, false);
	move(24, 127, false);
	spin(90, 127, false);
	move(48, 127, false);
	*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	int temp;
	//variable to

	//PID fixup
	nMotorPIDSpeedCtrl[backleft] = RegIdle;
	nMotorPIDSpeedCtrl[backright] = RegIdle;
	nMotorPIDSpeedCtrl[forks] = RegIdle;
	nMotorPIDSpeedCtrl[leftarm] = RegIdle;
	nMotorPIDSpeedCtrl[rightarm] = RegIdle;

	while (true)
	{
		//Right side of the robot is controlled by the right joystick
		temp = vexRT[Ch2];
		if((temp < -10) || (temp > 10))
		{
			motor[backright]  = temp;
		}
		else
		{
			motor[backright] = 0;
		}

		temp = vexRT[Ch3];
		if((temp < -10) || (temp > 10))
		{
			motor[backleft] = temp;
		}
		else
		{
			motor[backleft] = 0;
		}


		if(vexRT[Btn6U] == 1)  //if Btn 6U pressed arm up
		{
			motor[rightarm] = 40;
			motor[leftarm] = 40;
		}
		else if(vexRT[Btn6D] == 1)  // if Btn6D pressed arm down
		{
			motor[rightarm] = -40;
			motor[leftarm] = -40;
		}
		else
		{
			motor[rightarm] = 12;  //if not pressed don't move arm/try to keep it at the same hieght
			motor[leftarm] = 12;
		}

		if(vexRT[Btn5U] == 1)
		{
			motor[forks] = 40;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[forks] = -40;
		}
		else
		{
			motor[forks] = 0;
		}
		delay(10);
	}
}
