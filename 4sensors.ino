
int getAngle()
{
  mpu.update();
  GyroAngle = mpu.getAngleZ() + GyroOffset;
  return GyroAngle;
}
void updatesensors(char S = currentLineColor, WhichLineToFollow dir = direction, OfflineDirection off = offD)
{                                 // updatesensors( BLACK B mode or WHite W mode)
  distanceL = ultrasonicL.read(); // Serial.print("distance left : "); Serial.println(distanceL);Serial.println("*************");
  distanceR = ultrasonicR.read(); // Serial.print("distance right : "); Serial.println(distanceR);Serial.println("*******************************************");
  distanceF = ultrasonicF.read();
  getAngle();
  for (int i = 0; i < SensorCount; i++)
  {
    lastIntDsensors[i] = IntDsensors[i];
  }
  //   readLineWhite(uint16_t *sensorValues, QTRReadMode mode = QTRReadMode::On, WhichLineToFollow direction = WhichLineToFollow::AUTO LEFT RIGHT, bool AutoTopLeftOrRight = true)
  // readLineBlack(uint16_t *sensorValues, QTRReadMode mode = QTRReadMode::On, WhichLineToFollow direction = WhichLineToFollow::AUTO, bool AutoTopLeftOrRight = true)
  // WhichLineToFollow : RIGHT LEFT AUTO
  if (S == 'W')
  {
    position = qtr.readLineWhite(sensors, QTRReadMode::On, dir, off);
    currentLineColor = 'W';
  }
  else
  {
    // qtr.readLineBlack(sensors, QTRReadMode::On,  WhichLineToFollow::AUTO // RIGHT // LEFT, AutoTopLeftOrRight=true);
    position = qtr.readLineBlack(sensors, QTRReadMode::On, dir, off);
    currentLineColor = 'B';
  }
  //   Serial.print("cuurent color ");Serial.print (currentLineColor); Serial.print("// Dsensors :");
  // LED PRINTING ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if ((millis() - ledactiontime) > 30 && updateLedsInSensorsFn) // update leds if not myledwhiteon() ( after 50ms delay)
  {
    // LED PRINTING
    for (int i = 0; i < NUM_LEDS; i++)
    {
      //  int PathColorSettings[] = {255, 0, 0, 0, 0, 0, 0, 255};
      // ********* params
      // BEST int widthOfActiveLeds = 2200; // 1000 ~ 1led
      int widthOfActiveLeds = 2000; // 1000 ~ 1led
      int lineFollowingColor = 95;  //  https://camo.githubusercontent.com/2f40c83acc6756da11aed2a7109bade069a48e032f16db23e4fd282aca865c37/68747470733a2f2f7261772e6769746875622e636f6d2f466173744c45442f466173744c45442f67682d70616765732f696d616765732f4853562d7261696e626f772d776974682d646573632e6a7067
      int maxBrightness = 200;
      int waitingColor = 65;
      // ***************
      int ledIndex = i * 1000;
      int localPosition = map(position, 0, (SensorCount * 1000 - 1000), 0, NUM_LEDS * 1000 - 1000);
      int delta = ledIndex - localPosition;
      int deltaLedPosition = abs(delta);

      int betaBrightness = constrain(deltaLedPosition, 0, widthOfActiveLeds / 2);
      int lineBrightness = map(betaBrightness, 0, widthOfActiveLeds / 2, 255, 0);
      int brightness = constrain(PathColorSettings[i] + lineBrightness, 0, maxBrightness);
      int ledColor = 0;

      if (brightness > 0)
      {

        if (isPathTimesArrayCorrect == true)
        {
          double timeNow = millis();
          int delayBetweenEachAction = 4000;
          if (pathSteps != 0 && isPathTimesArrayCorrect == true)
            delayBetweenEachAction = pathTimes[pathSteps];
          // Serial.println(pathSteps);
          int deltaTime = timeNow - Taction;
          if (deltaTime < delayBetweenEachAction - 20 && RUNROBOT == true)
          {
            // leds[i] = CHSV(100, 255, 190);
            // still blocked
            int lineColor = map(deltaTime, 0, delayBetweenEachAction, waitingColor, lineFollowingColor);
            int pathColor = map(deltaTime, 0, delayBetweenEachAction, waitingColor, PathColorSettings[i]);
            int betaColor = (pathColor + lineColor);
            ledColor = constrain(betaColor, 0, 255);
            // Serial.print(ledColor);Serial.print("  ");
          }
          else if (deltaTime < delayBetweenEachAction && RUNROBOT == true)
          {
            ledColor = 250;
            brightness = 255;
            for (int i = 0; i < NUM_LEDS; i++)
            {
              leds[i] = CHSV(ledColor, 255, brightness);
            }
            break;
          }
          else
            ledColor = constrain(PathColorSettings[i] + lineFollowingColor, 0, 255);
        }
        else
          ledColor = constrain(PathColorSettings[i] + lineFollowingColor, 0, 255);
      }
      // ledColor = constrain(PathColorSettings[i] + lineFollowingColor, 0, 255);
      // Serial.print(" // color : ");
      // Serial.print(ledColor);
      leds[i] = CHSV(ledColor, 255, brightness);
      // Serial.println("******************************************");
    }
    Serial.println("  ");
  }
  FastLED.show();
  // creating Dsensors : W and B readings
  // Serial.print("Dsensors :");
  for (int i = 0; i < SensorCount; i++)
  {
    if (sensors[i] > (qtr.calibrationOn.maximum[i] + qtr.calibrationOn.minimum[i]) / 2)
      Dsensors[i] = 'B';
    else
      Dsensors[i] = 'W';
    Serial.print(Dsensors[i]);
    Serial.print("  ");
  }
  //  Serial.print("  ");

  // creating intDsensors : 0 and 1 readings 1=line que ce soit white or black line
  if (S == 'W')
  {
    for (int i = 0; i < SensorCount; i++)
    {
      if (Dsensors[i] == 'W')
        IntDsensors[i] = 1;
      else
        IntDsensors[i] = 0;
    }
  }
  else
  {
    for (int i = 0; i < SensorCount; i++)
    {
      if (Dsensors[i] == 'W')
        IntDsensors[i] = 0;
      else
        IntDsensors[i] = 1;
    }
  }
  // printing values
  Serial.print("VALUES Dsensors : ");
  for (int i = 0; i < SensorCount; i++)
  {
    Serial.print(IntDsensors[i]);
  }
  // Serial.print (" LAST: ");
  //  for(int i=0;i<SensorCount;i++){
  // Serial.print((int)lastIntDsensors[i]); }

  // saving changing times
  for (int i = 0; i < SensorCount; i++)
  {
    if (IntDsensors[i] != lastIntDsensors[i])
      lastIntDsensorstimes[i] = millis();
  }

  // printing times if u want to check
  // Serial.print("  TIMES CHANGES DIFFERENCE : ");
  // for(int i=0;i<SensorCount;i++){Serial.print(millis()-lastIntDsensorstimes[i]);Serial.print("  ");  }     // print the time differences for each sensor

  Serial.print(" position : ");
  Serial.println(position);
  Serial.println(' ');
}

uint8_t localCountLines(uint8_t cumulativeLineCounter = 0, int index = 0, int prevValue = 0)
{
  if (index == SensorCount)
    return cumulativeLineCounter;
  else if (IntDsensors[index] == 1 && prevValue == 0)
    localCountLines(cumulativeLineCounter + 1, index + 1, IntDsensors[index]);
  else
    localCountLines(cumulativeLineCounter, index + 1, IntDsensors[index]);
}

uint8_t CountLines()
{ // ONLY FOR 5 SENSORS !
  int sum = 0;
  if (!qtr.CheckonLine())
    return 0;
  return localCountLines(0, 0, 0);
}
void calibratesensors()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
  for (int i = 0; i < (int)NUM_LEDS / 2; i++)
  {
    leds[i] = CHSV(160, 255, 255);
    leds[NUM_LEDS - i - 1] = CHSV(160, 255, 150);
    FastLED.show();
    delay(150);
  }
  leds[2] = CHSV(160, 255, 150);
  FastLED.show();
  delay(400);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
  }
  int hue = 1;
  for (uint8_t i = 0; i < NUM_LEDS; i++)
  {
    for (uint8_t j = 0; j < 20; j++) // modify the loop counter limit to make the calibration shorter or longer
    {
      qtr.calibrate();
    }
    leds[i] = CHSV(100, 255, 190);
    FastLED.show();
  }

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println(" ***********************************************************");
}
void calibratE()
{

  // Serial.println("starting calibration");
  for (uint8_t i = 0; i < 150; i++)
  {
    qtr.calibrate();
    delay(10);
  }

  // Serial.println("calibration DONE");
  //  print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    // Serial.print(' ');
  }
  Serial.println(" ***********************************************************");
}
