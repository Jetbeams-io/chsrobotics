#pragma config(Sensor, dgtl1,  E0,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  E1,             sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  E2,             sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  E3,             sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  Button,         sensorTouch)
#pragma config(Motor,  port2,           Motor1,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           Motor2,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           Motor3,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           Motor4,        tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
typedef struct {
	int speed;
	int dir;
	int half;
	bool grad;
} MotorValues;

void controller() {
	if(vexRT[Ch2] > 9 || vexRT[Ch1] > 9){
		int dir = atan2(vexRT[Ch2], vexRT[Ch1]);
		dir = radiansToDegrees(dir);
		MotorValues motors[4];
		for (int i = 0; i < 4; i++) {
			MotorValues new;
			motors[i] = new;
		}

		//calculate direction of motors
		if (dir >= 0 && dir < 180) {
			motors[0].dir = 1;
		}
		else {
			motors[0].dir = -1;
		}
		if (dir >= 90 && dir < 270) {
			motors[1].dir = 1;
		}
		else {
			motors[1].dir = -1;
		}
		if (dir >= 180 && dir < 360) {
			motors[2].dir = 1;
		}
		else {
			motors[2].dir = -1;
		}
		if ((dir >= 0 && dir < 90) || (dir >= 270 && dir < 360)) {
			motors[3].dir = 1;
		}
		else {
			motors[3].dir = -1;
		}

		//test if gradating
		bool case1 = ((dir >= 0 && dir < 45) || (dir >= 90 && dir < 135) || (dir >= 180 && dir < 225) || (dir >= 270 && dir < 315));
		bool case2 = ((dir >= 45 && dir < 90) || (dir >= 135 && dir < 180) || (dir >= 225 && dir < 270) || (dir >= 315 && dir < 360));

		if ((dir >= 0 && dir < 90) || (dir >= 180 && dir < 270)) {
			motors[0].grad = case1;
			motors[1].grad = case2;
			motors[2].grad = case1;
			motors[3].grad = case2;
			motors[0].half = 1;
			motors[1].half = 2;
			motors[2].half = 1;
			motors[3].half = 2;
		}

		if ((dir >= 90 && dir < 180) || (dir >= 270 && dir < 360)) {
			motors[0].grad = case2;
			motors[1].grad = case1;
			motors[2].grad = case2;
			motors[3].grad = case1;
			motors[0].half = 2;
			motors[1].half = 1;
			motors[2].half = 2;
			motors[3].half = 1;
		}

		//calculate speed
		int num = 0;
		for (int i = 0; i < 4; i++) {
			num++;
			if (motors[i].grad) {
				int dir45 = dir % 45;
				if (dir45 == 0) { dir45 = 45; }
				if (motors[i].half == 1) {
					motors[i].speed = floor(dir45 / 45 * 127) * motors[i].dir;
				}
				else {
					motors[i].speed = floor(45 / dir45 * 127) * motors[i].dir;
				}
			}
			else {
				motors[i].speed = 127 * motors[i].dir;
			}
		}
		motor[Motor1] = motors[0].speed;
		motor[Motor2] = motors[1].speed;
		motor[Motor3] = motors[2].speed;
		motor[Motor4] = motors[3].speed;
	}
	else{
		motor[Motor1] = 0;
		motor[Motor2] = 0;
		motor[Motor3] = 0;
		motor[Motor4] = 0;
	}
}

#define length(a) (sizeof(a)/sizeof(a[0]))
void min(iterable){
	currentMin = iterable[0]
	for(int i = 0; i < length(iterable); i++){
		if(iterable[i] < currentMin){
			currentMin = iterable[i];
		}
	}
	return currentMin
}*/

void CUNI(){
	int LX = vexRT[Ch1];
	int LY = vexRT[Ch2];
	int Rotate = vexRT[Ch4];
	motor[Motor1] = LY + LX + Rotate;
	motor[Motor2] = -(LY) + LX + Rotate;
	motor[Motor3] = -(LY) + -(LX) + Rotate;
	motor[Motor4] = LY + -(LX) + Rotate;
}

bool calibrate;
void ECUNI(){
	SensorValue[E0] = SensorValue[E1] = SensorValue[E2] = SensorValue[E3] = 0;
	if(Button == 1){

		calibrate = false;
		for(int i = 0; i < 10; i++){
			wait1Msec(500);
			if(Button == 0){
				return;
			}
			if(i == 9){
				calibrate = true;
			}
		}
	}
	if(calibrate == true){
		SensorValue[E0] = 0;
		SensorValue[E1] = 0;
		SensorValue[E2] = 0;
		SensorValue[E3] = 0;

		motor[Motor1] = 127;
		motor[Motor2] = 127;
		motor[Motor3] = 127;
		motor[Motor4] = 127;
		wait1Msec(3000);
		motor[Motor1] = 0;
		motor[Motor2] = 0;
		motor[Motor3] = 0;
		motor[Motor4] = 0;
	}
	int min = 9999999999999999;
	int cenc = NULL;
	int sensorValues[] = {SensorValue[E0], SensorValue[E1], SensorValue[E2], SensorValue[E3]};

	for(int i = 0; i < 4; i++){
		if(sensorValues[i] < min){
			min = sensorValues[i];
			cenc = i;

		}
	}
}

task main(){
	while(true){
		CUNI();
		ECUNI();
	}
}