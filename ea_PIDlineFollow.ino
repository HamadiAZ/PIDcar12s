
const PROGMEM float TURNFACTOR = 1;      // multiplier=1 GADCH YON9ES VITESS FEL DORA
//const PROGMEM float Kp = 0.07;             // black line
//const PROGMEM float Ki = 0.04; float Kp = 0.020   ;        // 255: 0.1     110: 0.2
const PROGMEM float Ki = 0.0;             // 255: 0.05    110: 0.05
 float Kd = 2.9;             // 255: 0.003   110: 0.004
float Kp= 0.016;   
 
  uint8_t rightMaxSpeed = 140; // 255  50
 uint8_t leftMaxSpeed = 140;  //
void thirdSpeed(){
  rightMaxSpeed = 230; // 255  50
  leftMaxSpeed = 230;
  Kp = 0.038  ;        // 0.038
  Kd = 4;   
}
void firstSpeed(){
  rightMaxSpeed = 140; // 255  50
  leftMaxSpeed = 140;
  Kp = 0.03  ;        // 0.038
  Kd = 2.9;        
}             // 255: 0.05    110: 0.05
//const PROGMEM float Kd = 0.21;             // 255: 0.003   110: 0.004



void pidfollow(int C = 1)
{
  // SetPoint = (numberOfSensors-1)*500

  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = micros();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  int med_Speed_R;
  int med_Speed_L;
  if (C != 0)
    updatesensors('B',direction,offD);
  int p = position - SetPoint;
  int error = p;
  int i = i + prev_i;
  int d = (error - (prev_error))/elapsedTime;
  float pid = (Kp * p) + (Ki * i) + (Kd * d);
  prev_i = i;
  prev_error = error;

  med_Speed_L = leftMaxSpeed - TURNFACTOR * abs(pid);
  med_Speed_R = rightMaxSpeed - TURNFACTOR * abs(pid);
  int leftMotorSpeed = med_Speed_L + pid;
  int rightMotorSpeed = med_Speed_R - pid;

  leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);
  float multiplier = 1; // hetha lel 3jal leli idoro lteli , 0 y3ni matdor 7ata 3ejla lteli
  // 1 y3ni fi right turn ,  vitesses des pid 3ejla avant w 3ejla arriere

  // bech ibaddel les vitess negatives into positive speeds that forward right and left fn can undestand
  if (rightMotorSpeed < 0 && leftMotorSpeed < 0)
  {
    back(abs(rightMotorSpeed), abs(leftMotorSpeed));
  }
  else if (rightMotorSpeed < 0 && leftMotorSpeed > 0)
  {
    right(abs(multiplier * rightMotorSpeed), abs(leftMotorSpeed));
  }
  else if (rightMotorSpeed > 0 && leftMotorSpeed < 0)
  {
    left(rightMotorSpeed, multiplier * abs(leftMotorSpeed));
  }
  else
  {
    forward(rightMotorSpeed, leftMotorSpeed);
  };
//  Serial.print("LINE PID SPEEDS R,L ");
//  Serial.print(rightMotorSpeed);
//  Serial.print(" , ");
//  Serial.print(leftMotorSpeed);
  // forward(rightMotorSpeed,leftMotorSpeed);
  // delayMicroseconds(140);
}
