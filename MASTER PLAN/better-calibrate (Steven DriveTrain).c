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

void newstevendrivetrain(){ //This code does not account for weak motors
    SensorValue[0] = 0;
    SensorValue[1] = 0;
    SensorValue[2] = 0;
    SensorValue[3] = 0;
    int LX = vexRT[Ch1];
    int LY = vexRT[Ch2];
    int Rotate = vexRT[Ch4] * -1;
    /*
     Motor1 - BR
     Motor2 - BL
     Motor3 - FL
     Motor4 - FR
     */
//    motor[Motor1] = LY + LX + Rotate;
//    motor[Motor2] = -(LY) + LX + Rotate;
//    motor[Motor3] = -(LY) + -(LX) + Rotate;
//    motor[Motor4] = LY + -(LX) + Rotate;
    
    
    
    //627.2 is the number of ticks for a normal geared revolution
    float firstMotor = 627.2 * ((LX/127) + (LY/127))
    float secoundMotor = 627.2 * (((-LX)/127) + ((-LY)/127))
    float thirdMotor = 627.2 * (((-LX)/127) + (((-LY)/127))
    float fourthMotor = 627.2 * (((-LX)/127) + ((LY)/127))
    
    do{
        if(SensorValue[0] < firstmotor){
            motor[Motor1] = LY + LX;
        }
        else{
            motor[Motor1] = 0;
        }
        if(SensorValue[1] < secoundMotor){
            motor[Motor2] = -(LY) + LX;
        }
        else{
            motor[Motor2] = 0;
        }
        if(SensorValue[2] < thirdMotor){
            motor[Motor3] = -(LY) + -(LX);
        }
        if(SensorValue[3] < fourthMotor){
            motor[Motor4] = LY + -(LX);
        }
        else{
            motor[Motor4] = 0;
        } while((SensorValue[0] < firstMotor) && (SensorValue[1] < secoundMotor) && (SensorValue[2] < thirdMotor) && (SensorValue[3] < fourthMotor));
    }
    
    
    
    
    
}





void stevendrivetrain(){


	SensorValue[0] = 0;
	SensorValue[1] = 0;
	SensorValue[2] = 0;
	SensorValue[3] = 0;
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
	int firstMotor = abs(SensorValue[0]);
	int secoundMotor = abs(SensorValue[1]);
	int thridMotor = abs(SensorValue[2]);
	int fourthMotor = abs(SensorValue[3]);



	
	if(firstMotor < thirdMotor){
		motor[3] = (-(LY) + -(LX) + Rotate)/3;
	}
	else if(thirdMotor < firstMotor){
		motor[1] = (LY + LX + Rotate)/3;
	}

	if(secoundMotor < fourthMotor){
		motor[3] = (-(LY) + LX + Rotate)/3;
	}
	else if(fourthMotor < secoundMotor){
		motor[1] = (LY + -(LX) + Rotate)/3;
	}
		
	
	

}
