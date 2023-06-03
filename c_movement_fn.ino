
void stope()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward(int r = 120, int l = 120)
{
  lastLeftSpeed = l;
  lastRightSpeed = r;
  if (BLOCKMOVEMENT == true)
  {
    return stope();
  }

  analogWrite(ENA, l);
  analogWrite(ENB, r);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Serial.print("forward");
}
void right(int r = 120, int l = 120)
{ // THE SPEED OF FORWARD OF RIGHT THEN LEFT WHEEL
  lastLeftSpeed = l;
  lastRightSpeed = -r;
  if (BLOCKMOVEMENT == true)
  {
    stope();
  }
  else
  {
    analogWrite(ENA, l);
    analogWrite(ENB, r);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    // Serial.print("right");
  }
}

void left(int r = 120, int l = 120)
{ // THE SPEED OF FORWARD OF RIGHT THEN LEFT WHEEL
  lastLeftSpeed = -l;
  lastRightSpeed = r;
  if (BLOCKMOVEMENT == true)
  {
    stope();
  }
  else
  {
    analogWrite(ENA, l);
    analogWrite(ENB, r);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    // Serial.print(" left ");
  }
}

void back(int R = 110, int L = 110)
{ // BACK SPEED OF RIGHT THEN LEFT WHEEL
  lastLeftSpeed = -L;
  lastRightSpeed = -R;
  if (BLOCKMOVEMENT == true)
  {
    stope();
  }
  else
  {
    analogWrite(ENA, L);
    analogWrite(ENB, R);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    //Serial.print(" back ");
  }
}
void moveRobot(int rightMotorSpeed = 150, int leftMotorSpeed = 150) {
  if (rightMotorSpeed < 0 && leftMotorSpeed < 0)
  {
    back(abs(rightMotorSpeed), abs(leftMotorSpeed));
  }
  else if (rightMotorSpeed < 0 && leftMotorSpeed > 0)
  {
    right(abs(rightMotorSpeed), abs(leftMotorSpeed));
  }
  else if (rightMotorSpeed > 0 && leftMotorSpeed < 0)
  {
    left(rightMotorSpeed, abs(leftMotorSpeed));
  }
  else
  {
    forward(rightMotorSpeed, leftMotorSpeed);
  };
}
void STOPE() {
  signed int sl = 1;
  signed int sr = 1;
  if (lastLeftSpeed < 0) sl = -1;
  if (lastRightSpeed < 0) sr = -1;
  if (abs(lastRightSpeed) > abs(lastLeftSpeed)) {
    int mappedSubsitution = map(5, 0, lastRightSpeed, 0, lastLeftSpeed);
    for (int i = 0; i <= 51; i++) {
      if (abs(lastRightSpeed) >= 5) {
        lastRightSpeed = (abs(lastRightSpeed) - 5) * sr;
      }
      else lastRightSpeed = 0;

      if (abs(lastLeftSpeed) >= mappedSubsitution) {
        lastLeftSpeed = (abs(lastLeftSpeed) - mappedSubsitution) * sl;
      }
      else lastLeftSpeed = 0;
      moveRobot(lastRightSpeed, lastLeftSpeed);
    }
  } else {
    int mappedSubsitution = map(5, 0, lastLeftSpeed, 0, lastRightSpeed);
    for (int i = 0; i <= 51; i++) {
      if (abs(lastLeftSpeed) >= 5) {
        lastLeftSpeed = (abs(lastLeftSpeed) - 5) * sr;
      }
      else lastLeftSpeed = 0;

      if (abs(lastRightSpeed) > mappedSubsitution) {
        lastRightSpeed = (abs(lastRightSpeed) - mappedSubsitution) * sl;
      }
      else lastRightSpeed = 0;
      moveRobot(lastRightSpeed, lastLeftSpeed);
    }
  }
  back(100, 100);
  delay(20);
  stope();


}

// mche bdet langle 45° gauche elli hya 10045
// ngolah ane 90055 => but 90

void turn(int but = 90) {
  getAngle();
  long startangle = GyroAngle;
  if (but > 1500) {
    Serial.print(" but : ");
    but = but - startangle;
    Serial.print(but); Serial.print("  |  ");
  }
  if (abs(but) < 11) {
    getAngle();
    startangle=GyroAngle;
    //    if (but < 0) {
    //      right();
    //      delay(100);
    //    } else {
    //      left();
    //      delay(100);
    //    }
    //stope();
    //return ;
  }
  if (but > 0) {
    unsigned long entyTime = millis();
    int realBut = but ;
    while (true)
    {
      getAngle();
      if (GyroAngle - startangle >= (realBut / 3))
        left(60, 60);
      else
        left(140, 140);
      if ((GyroAngle - startangle >= realBut) || (millis() - entyTime > 3000)) {
        right(200, 200);
        delay(40);
        stope();
        break;
      }
    }
  } else {
    unsigned long entyTime = millis();
    int realBut = but + 10;
    while (true)
    {

      //updatesensors();
      getAngle();
      if (GyroAngle - startangle <= (realBut / 3))
        right(60, 60);
      else
        right(140, 140);
      if ((GyroAngle - startangle <= realBut) || (millis() - entyTime > 2000)) {
        left(200, 200);
        delay(40);
        stope();
        break;
      }
    }
  }

}
