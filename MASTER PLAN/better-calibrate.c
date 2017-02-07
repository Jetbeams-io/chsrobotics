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

#define length(a) (sizeof(a)/sizeof(a[0]))
int min(int iterable) {
	int currentMin = iterable[0];
	for(int i = 0; i < length(iterable); i++) {
		if(iterable[i] < currentMin) {
			currentMin = iterable[i];
		}
	}
	return currentMin;
}

task main()
{
	wait1Msec(5000);
	int motors[] = {motor[Motor1], motor[Motor2], motor[Motor3], motor[Motor4]}
	int encoders[] = {sensorvalue[Motor1], sensorvalue[Motor2], sensorvalue[Motor3], sensorvalue[Motor4]}
	motor[Motor1] = motor[Motor2] = motor[Motor3] = motor[Motor4] = 127;
	wait1Msec(500);
	sensorvalue[Motor1] = sensorvalue[Motor2] = sensorvalue[Motor3] = sensorvalue[Motor4] = 0;
	clearTimer(T1);
	wait1Msec(1000);
	double slowSpeed = min(encoders) / (time1(T1) * 1000)
	for(int i = 0; i < 4; i++) {
		wait1Msec(500);
		sensorvalue[Motor1] = sensorvalue[Motor2] = sensorvalue[Motor3] = sensorvalue[Motor4] = 0;
		clearTimer(T1);
		wait1Msec(1000);
		int speed = 127;
		double motorSpeed = encoders[i] / (time1(T1) * 1000);
		while(motorSpeed > slowSpeed - 5 && motorSpeed < slowSpeed + 5) {
			speed--;
			motors[i] = speed;
			wait1Msec(100);
			sensorvalue[Motor1] = sensorvalue[Motor2] = sensorvalue[Motor3] = sensorvalue[Motor4] = 0;
			clearTimer(T1);
			wait1Msec(900);
			motorSpeed = encoders[i] / (time1(T1) * 1000);
		}
		writeDebugStream("Motor");
		writeDebugStream(i+1);
		writeDebugStream(": ");
		writeDebugStream(speed);
		writeDebugStream("\n");
	}
}
