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

task main()
{
	wait1Msec(5000);
	int motors[] = {motor[Motor1], motor[Motor2], motor[Motor3], motor[Motor4]};
	int encoders[] = {SensorValue[Motor1], SensorValue[Motor2], SensorValue[Motor3], SensorValue[Motor4]};
	motor[Motor1] = motor[Motor2] = motor[Motor3] = motor[Motor4] = 127;
	wait1Msec(500);
	SensorValue[Motor1] = SensorValue[Motor2] = SensorValue[Motor3] = SensorValue[Motor4] = 0;
	clearTimer(T1);
	wait1Msec(1000);
	int currentMin = encoders[0];
	for(int i = 0; i < 4; i++) {
		if(encoders[i] < currentMin) {
			currentMin = encoders[i];
		}
	}
	float slowSpeed = currentMin / (time1(T1) * 1000);
	for(int i = 0; i < 4; i++) {
		wait1Msec(500);
		SensorValue[Motor1] = SensorValue[Motor2] = SensorValue[Motor3] = SensorValue[Motor4] = 0;
		clearTimer(T1);
		wait1Msec(1000);
		int speed = 127;
		float motorSpeed = encoders[i] / (time1(T1) * 1000);
		while(motorSpeed > slowSpeed - 5 && motorSpeed < slowSpeed + 5) {
			speed--;
			motors[i] = speed;
			wait1Msec(100);
			SensorValue[Motor1] = SensorValue[Motor2] = SensorValue[Motor3] = SensorValue[Motor4] = 0;
			clearTimer(T1);
			wait1Msec(900);
			motorSpeed = encoders[i] / (time1(T1) * 1000);
		}
		string tensPlace[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
		string onesPlace[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
		int ones = motorSpeed % 10;
		int tens = motorSpeed / 10;
		writeDebugStream(tensPlace[tens]);
		writeDebugStreamLine(onesPlace[ones]);
	}
}
