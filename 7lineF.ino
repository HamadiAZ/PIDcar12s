
float TURNFACTOR = 1; // multiplier=1 (speed reduction in turn ! multiplier of the error)

float Ki = 0.0;             // 255: 0.05    110: 0.05
float Kd = 4.7;             // 255: 0.003   110: 0.004
float Kp = 0.015;

uint8_t rightMaxSpeed = 140; //
uint8_t leftMaxSpeed = 140;  //

void firstSpeed()
{
  rightMaxSpeed = 140; 
  leftMaxSpeed = 140;
  Kp = 0.015;
  Kd = 3; 
  TURNFACTOR = 1;
} // 255: 0.05    110: 0.05
void secondSpeed()
{
  rightMaxSpeed = 140; 
  leftMaxSpeed = 140;
  Kp = 0.015; // 0.038
  Kd = 3;
  TURNFACTOR = 0.2;
}
void thirdSpeed()
{
  rightMaxSpeed = 190; 
  leftMaxSpeed = 190;
  Kp = 0.025; // 0.038
  Kd = 5;
   TURNFACTOR = 0.4;
}
void fourthSpeed()
{
  rightMaxSpeed = 230; 
  leftMaxSpeed = 230;
  Kp = 0.016; // 0.038
  Kd = 2.9;
}
void pidfollow(bool internalUpdateSensors = true)
{
  // SetPoint = (numberOfSensors-1)*500

  LineFwPrevTime = LineFwNewTime; // the previousLineFwNewTime is stored before the actualLineFwNewTime read
  LineFwNewTime = micros();       // actualLineFwNewTime read
  double elapsedTime = (LineFwNewTime - LineFwPrevTime) / 1000;
  int med_Speed_R;
  int med_Speed_L;
  if (internalUpdateSensors = true)
    updatesensors('B', direction, offD);
  int p = position - SetPoint;
  int error = p;
  int i = i + prev_i;
  int d = (error - (prev_error)) / elapsedTime;
  float pid = (Kp * p) + (Ki * i) + (Kd * d);
  prev_i = i;
  prev_error = error;

  med_Speed_L = leftMaxSpeed - TURNFACTOR * abs(pid);
  med_Speed_R = rightMaxSpeed - TURNFACTOR * abs(pid);
  int leftMotorSpeed = med_Speed_L + pid;
  int rightMotorSpeed = med_Speed_R - pid;

  leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);
  float multiplier = 1; // multiplier for the inverse speed wheel if needed, normally 1 which has no effect on pid calculations, but if more inverse speed is needed, this can do the job
  
  // translate the negative speeds into positive speeds that forward right and left fn can understand
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
