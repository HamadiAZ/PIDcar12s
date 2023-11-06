
void conditionsDO()
{
  if (conditionsCounter == 0)
  {

  }

  else if (conditionsCounter == 1)
  {

  }
  else if (conditionsCounter == 2)
  {
  
  }
  else if (conditionsCounter == 3)
  {
   
  }
  else if (conditionsCounter == 4)
  {
    back(160, 180);
    delay(80);
    stope();
   
  }
  else if (conditionsCounter == 5)
  {
    int oldDistance = distanceL;
    getAngle();
    double lastAngle = GyroAngle;
    initialAngle = GyroAngle;
    // initialAngle=initialAngle - 360;
    back();
    delay(50);
    stope();
    delay(500);
    double entryTime = millis();
    while (true)
    {
      forward(100, 110);
      updatesensors(currentLineColor);
      if (((distanceF < 17) && (distanceL < 17)) || ((millis() - entryTime) > 2000))
        break;
    }
    turn(-50);
    stope();
    while (1)
    {
      oldDistance = distanceL;
      getAngle();
      lastAngle = GyroAngle;
      wallfollow(18, 'L');
      if (((millis() - entryTime) > 4000) && (lastAngle - initialAngle > 70) && (distanceL > 50))
      {
        right();
        delayGyro(50);
        stope();
        delayGyro(300);
        forward(100, 100);
        delayGyro(400);
        back();
        delayGyro(50);
        stope();
        turn(initialAngle + 110);
        delayGyro(200);
        entryTime = millis();
        while (1)
        {
          forward(100, 100);
          updatesensors(currentLineColor);
          if ((distanceL > 60 && millis() - entryTime > 50) || millis() - entryTime > 320)
            break;
        }
        forward(100, 100);
        delayGyro(120);
        stope();
        turn(initialAngle + 180);
        entryTime = millis();
        while (true)
        {
          forward(100, 100);
          updatesensors(currentLineColor);
          if (distanceF < 17 || millis() - entryTime > 900)
            break;
        }
        back();
        delay(50);
        stope();
        delay(100000);
      }
    }
  }
  else
    Serial.println("Error! NOMBER OF C IN PATHSTRING IS MORE THAN THE CONDITIONS IN conditionsDO FUNCTION");
}
