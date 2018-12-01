#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  autonomous1,    sensorDigitalIn)
#pragma config(Sensor, dgtl2,  autonomous2,    sensorDigitalIn)
#pragma config(Sensor, dgtl6,  autonomous6,    sensorDigitalIn)
#pragma config(Sensor, dgtl7,  autonomous7,    sensorDigitalIn)
#pragma config(Sensor, dgtl8,  autonomous8,    sensorDigitalIn)
#pragma config(Sensor, dgtl11, autonomous11,   sensorDigitalIn)
#pragma config(Sensor, dgtl12, autonomous12,   sensorDigitalIn)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           middleleft,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           backright,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           backleft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backarm,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port5,           forks,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           frontleft,     tmotorVex393_MC29, PIDControl, encoderPort, I2C_5)
#pragma config(Motor,  port7,           frontright,    tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port8,           leftarm,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port9,           rightarm,      tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port10,          middleright,   tmotorVex393_HBridge, openLoop, reversed)
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

static const float ticksPerArmInch = 1366.0/27.0;

static const float ticksPerForkInch = 94.0;

static const float ticksPerBackInch = 9.9;

void move(float dist, int speed, bool hold)
{
	resetMotorEncoder(frontright);
	resetMotorEncoder(frontleft);

	setMotorTarget(frontright, dist*ticksPerInch, speed, hold);
	setMotorTarget(frontleft, dist*ticksPerInch, speed, hold);

	while (!getMotorTargetCompleted(frontright) && !getMotorTargetCompleted(frontleft))
		wait1Msec(10);
}

void spin(float deg, int speed, bool hold)
{
	resetMotorEncoder(frontright);
	resetMotorEncoder(frontleft);

	setMotorTarget(frontright, deg*ticksPerDeg, speed, hold);
	setMotorTarget(frontleft, -deg*ticksPerDeg, speed, hold);

	while (!getMotorTargetCompleted(frontright) && !getMotorTargetCompleted(frontleft))
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

void armback(float dist, int speed, bool hold)
{
	resetMotorEncoder(backarm);

	setMotorTarget(backarm, dist*ticksPerBackInch, speed, hold);

	while (!getMotorTargetCompleted(backarm))
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

	slaveMotor(backright, frontright);
	slaveMotor(backleft, frontleft);
	slaveMotor(middleright, frontright);
	slaveMotor(middleleft, frontleft);
	//slaveMotor(leftarm, rightarm);
	//make the back and middle motors copy what the front motors do because they don't have encoders

	motor[frontleft] = 0;
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

//25 distance(50 speed) is all the way up for the arm
//-5 distance(50 speed)is all the way down for the forks
//positive dist is left for spin
//fork is the function

void red_far(void)
{
	arm(10, 127, false);
	move(6, 127, false);		//red_far (platform)
	spin(95, 127, false);
	move(28, 127, false);
	armback(10, 127, true);
	spin(-86, 127, false);
	move(65, 127, false);
}

void blue_far(void)
{
	move(6, 127, false);		//blue_far (platform)
	spin(-90, 127, false);
	move(24, 127, false);
	arm(5, 127, false);
	spin(90, 127, false);
	move(60, 127, false);
}

void red_close(void)
{
	move(-49, 127, false);		//red_close (flag + platform)
	arm(5, 127, false);
	move(8, 127, false);
	armback(9, 127, true);
	move(66, 127, false);
	spin(90, 127, false);
	move(64, 127, false);
}

void blue_close(void)
{
	move(-49, 127, false);		//blue_close (flag + platform)
	arm(5, 127, false);
	move(8, 127, false);
	armback(9, 127, true);
	move(66, 127, false);
	spin(-90, 127, false);
	move(64, 127, false);
}

void flag(void)
{
	move(-47, 127, false);
}

void cap(void)
{
	move(44, 127, false);
	spin(-90, 127, false);
}

void skills(void)
{
	move(-47, 127, false);
	move(24, 127, false);
	spin(-90, 127, false);
	move(12, 127, false);
	armback(50, 127, false);
	move(24, 127, false);
	spin(90, 127, false);
	move(-24, 127, false);
	move(24, 127, false);
	spin(90, 127, false);
	move(-48, 127, false);
	armback(50, 127, false);
	move(-24, 127, false);
	spin(90, 127, false);
	move(-24, 127, false);
	move(24, 127, false);
	spin(-90, 127, false);
	move(120, 127, false);
	spin(90, 127, false);
	move(48, 127, false);
	spin(90, 127, false);
	arm(8, 127, false);
	armback(10, 127, false);
	move(72, 127, false);
}

task autonomous()
{
	if(!SensorValue(autonomous1))
	{
		red_close();
	}

	else if(!SensorValue(autonomous2))
	{
		red_far();
	}

	else if(!SensorValue(autonomous6))
	{
		flag();
	}

	else if(!SensorValue(autonomous7))
	{
		skills();
	}

	else if(!SensorValue(autonomous8))
	{
		cap();
	}

	else if(!SensorValue(autonomous11))
	{
		blue_close();
	}

	else if(!SensorValue(autonomous12))
	{
		blue_far();
	}
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
	//variable to stop drive train drift

	bool halfspeed = false;
	//tempright = vexRT[Ch2]
	//templeft = vexRT[Ch3];

	//PID fixup
	nMotorPIDSpeedCtrl[frontleft] = RegIdle;
	nMotorPIDSpeedCtrl[frontright] = RegIdle;
	nMotorPIDSpeedCtrl[forks] = RegIdle;
	nMotorPIDSpeedCtrl[rightarm] = RegIdle;
	nMotorPIDSpeedCtrl[leftarm] = RegIdle;
	nMotorPIDSpeedCtrl[backarm] = RegIdle;

	while (true)
	{
		if(vexRT[Btn6D] == 1)
		{
			halfspeed = true;
		}
		else if(vexRT[Btn6U] == 1)
		{
			halfspeed = false;
		}

		temp = vexRT[Ch2];		//Back right motor (back and middle right motors are slaved to front right motor)
		if((temp < -10) || (temp > 10) && halfspeed == true)
		{
			motor[frontright]  = temp / 2;
		}
		else if((temp < -10) || (temp > 10) && halfspeed == false)
		{
			motor[frontright] = temp;
		}
		else
		{
			motor[frontright] = 0;
		}

		temp = vexRT[Ch3];		//Back left motor (front and middle left motors are slaved to back left motor)
		if((temp < -10) || (temp > 10) && halfspeed == true)
		{
			motor[frontleft]  = temp / 2;
		}
		else if((temp < -10) || (temp > 10) && halfspeed == false)
		{
			motor[frontleft] = temp;
		}
		else
		{
			motor[frontleft] = 0;
		}


		if(vexRT[Btn6UXmtr2] == 1)		//Arm
		{
			motor[rightarm] = 100;
			motor[leftarm] = 100;
		}
		else if(vexRT[Btn6DXmtr2] == 1)
		{
			motor[rightarm] = -100;
			motor[leftarm] = -100;
		}
		else
		{
			motor[rightarm] = 10;
			motor[leftarm] = 10;
		}


		if(vexRT[Btn5UXmtr2] == 1)		//Forks
		{
			motor[forks] = 80;
		}
		else if(vexRT[Btn5DXmtr2] == 1)
		{
			motor[forks] = -80;
		}
		else
		{
			motor[forks] = 5;		//
		}

		motor[backarm] = vexRT[Ch2Xmtr2];		//backarm

		delay(10);
	}
}
