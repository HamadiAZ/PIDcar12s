void autoColorChooser()
{ // to update the sensors with the right line color depending on the Pathstring 
  if (pathSteps == 0)
  {
    if (isPathArrayCorrect == true)
      currentLineColor = path[pathSteps++]; // Serial.println(pathSteps);
    else
    {
      currentLineColor = 'B';
      Serial.print("Couldn't find a correct Color, Switched by default to BLACK");
    }
    Serial.print("PATH[0] LINE COLOR INITIALISED : ");
    Serial.println(currentLineColor);
    updatesensors(currentLineColor, direction, offD);
    for (int i = 0; i < SensorCount; i++)
    {
      lastIntDsensors[i] = IntDsensors[i];
    }
    Taction = millis();
  }
  else
  {
    updatesensors(currentLineColor, direction, offD); // Serial.println(" debugging 1 ");
  }
  // ========================================== affichage du path dans les led ============================================
  // next move : ( following the line until the robot find it )
  // right : red in the top right led , left inverse ..
  // forward : middle red led
  // change color : top right and top left red led
  // STOP : ALL RED
  // PathColorSettings contain colors AS number from :
  // https://camo.githubusercontent.com/2f40c83acc6756da11aed2a7109bade069a48e032f16db23e4fd282aca865c37/68747470733a2f2f7261772e6769746875622e636f6d2f466173744c45442f466173744c45442f67682d70616765732f696d616765732f4853562d7261696e626f772d776974682d646573632e6a7067
  // EXCEPT FOR RED DONT MAKE 0 : MAKE 1 !!
  // 0 = no color !!

  if ((path[pathSteps] == 'R') || (path[pathSteps] == 'r'))
    {
        PathColorSettings[NUM_LEDS - 1] = 255;
        for (int i = 0; i < NUM_LEDS - 1; i++)
        {
            PathColorSettings[i] = 0;
        }
    }
    else if ((path[pathSteps] == 'L') || (path[pathSteps] == 'l'))
    {
        PathColorSettings[0] = 255;
        for (int i = 1; i < NUM_LEDS; i++)
        {
            PathColorSettings[i] = 0;
        }
    }
    else if (path[pathSteps] == 'F'||path[pathSteps] == 'M'||path[pathSteps] == 'f')
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            PathColorSettings[i] = 0;
        }
        PathColorSettings[2] = 255;
        // 5 led : 2 wastanya
        // PathColorSettings[3]=255; // 8 led : 3 ET 4 MIDDLE
        // PathColorSettings[4]=255; // 8 led : 3 ET 4 MIDDLE
    }
    // else if((path[pathSteps]=='W')||(path[pathSteps]=='B'))
    else if ((mode == 'W') || (mode == 'B')) // TEST THIS
    {
        PathColorSettings[0] = 255;
        PathColorSettings[NUM_LEDS - 1] = 255;
        for (int i = 1; i < NUM_LEDS - 1; i++)
        {
            PathColorSettings[i] = 0;
        }
    }
    else if (path[pathSteps]=='V') // 
    {
        for (int i = 1; i < NUM_LEDS - 1; i++)
        {
            PathColorSettings[i] = 0;
        }
        PathColorSettings[0] = 255;
        PathColorSettings[NUM_LEDS - 1] = 255;
        if (path[pathSteps+1]=='L') PathColorSettings[1] = 255;
        if (path[pathSteps+1]=='R') PathColorSettings[NUM_LEDS-2] = 255;
        
        
    }
    else if (path[pathSteps] == 's')
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            PathColorSettings[i] = 255;
        }
    }
       else if (path[pathSteps]=='C') // 
    {
        for (int i = 1; i < NUM_LEDS - 1; i++)
        {
            PathColorSettings[i] = 0;
        }
        PathColorSettings[0] = 255;        
        //PathColorSettings[1] = 255;
        PathColorSettings[NUM_LEDS-1] = 255;             
        //PathColorSettings[NUM_LEDS-2] = 255;
    }
  // ========================================== fin affichage dans les led ====================================================
}


void applySpeed(int speed)
{
  if (speed == 2)
    secondSpeed();
  else if (speed == 3)
    thirdSpeed();
  else if (speed == 4)
    fourthSpeed();
  else
    firstSpeed();
}
void chooseSpeed(bool sentFromTimeRestriction = false)
{
  if (enableSpeedManager == false)
  {
    applySpeed(defaultManualSpeed);
    return;
  }
  // else => enableSpeedManager == true
  if (sentFromTimeRestriction == true)
    applySpeed(SpeedManager_HighSpeed);
  else
    applySpeed(SpeedManager_LowSpeed);

}
void ELSE()
{
  chooseSpeed(false);
  pidfollow(false); // 0 to disable internal readsensors fn of PID cuz we already updated in Run_Robot
}

void initialCheck()
{

  int timesArraySize = sizeof(pathTimes) / sizeof(pathTimes[0]);
  if (timesArraySize != strlen(path))
  {
    // signal error

    isPathTimesArrayCorrect = false;
    isPathArrayCorrect = false;
    myledwhiteon();
    delay(3000);
  }
  if (path[0] != 'B' && path[0] != 'W')
  {
    Serial.print("here");
    isPathTimesArrayCorrect = false;
    isPathArrayCorrect = false;
    myledwhiteon();
    delay(3000);
  }

  boolean isWandBModesAreCorrectInPath = true;
  char prevChar = '\0';
  for (int i = 0; i < strlen(path); i++)
  {
    if (path[i] == 'W' || path[i] == 'B')
    {
      char currentChar = path[i];
      if (currentChar == prevChar)
      {
        isWandBModesAreCorrectInPath = false; // Two consecutive 'W' or 'B' characters found
      }
      prevChar = currentChar;
    }
  }
  if (isWandBModesAreCorrectInPath == false)
  {
    Serial.print("Cant have two Consecutives B or Two W in path, this is false example : BFRLBs, you must add a W in between the Two B");
    isPathArrayCorrect = false;
    myledwhiteon();
    delay(3000);
  }
}
void initializeValues()
{
  // THE FIRST FUNCTION THAT MUST BE CALLED IN SETUP !
  // MODIFIABLE
  conditionsCounter = 0;
  mode = 'S';
  Taction = 0;
  updateLedsInSensorsFn = true;
  OfflineDirection offD = OfflineDirection::AUTO;
  WhichLineToFollow direction = WhichLineToFollow::AUTO;
  pathSteps = 0;
  boolean isPathTimesArrayCorrect = true;
  boolean isPathArrayCorrect = true;
  BLOCKMOVEMENT = false;
  RUNROBOT = false;
  SetPoint = 5500;
  enableSpeedManager = false;
  defaultManualSpeed = 1;
  SpeedManager_LowSpeed = 1;
  SpeedManager_HighSpeed = 3;

  // DONT TOUCH
  for (int i = 0; i < SensorCount; i++)
  {
    PathColorSettings[i] = 0;
    lastIntDsensors[i] = 0;
  }
}
void initialCalcTimes()
{
  float cmToMsFactor1stSpeed = 16.4; //  first speed hassen 140
  float cmToMsFactor4thSpeed = 9.8;  //  fourth speed hassen still unknown!!
  float cmToMsFactor2ndSpeed = map(2, 1, 4, cmToMsFactor4thSpeed, cmToMsFactor1stSpeed);
  float cmToMsFactor3rdSpeed = map(3, 1, 4, cmToMsFactor4thSpeed, cmToMsFactor1stSpeed);
  float speedFactors[4] = {cmToMsFactor1stSpeed, cmToMsFactor2ndSpeed, cmToMsFactor3rdSpeed, cmToMsFactor4thSpeed};
  int ArraySize = sizeof(pathDistances) / sizeof(pathDistances[0]);
  int currentSpeed = 1;
  int startIndex = 1;

  for (int i = startIndex; i < ArraySize; i++)
  {
    if (path[i] == '4' || path[i] == '3' || path[i] == '2' || path[i] == '1')
      currentSpeed = path[i] - '0';

    pathTimes[i] = pathDistances[i] * speedFactors[currentSpeed - 1];
  }
}
