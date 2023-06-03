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
}

void initialCalcTimes()
{
  float cmToMsFactor1stSpeed = 16.4; //  first speed hassen 140
  float cmToMsFactor5thSpeed = 9.8;  //  fifth  speed hassen still unknown!!
  int ArraySize = sizeof(pathDistances) / sizeof(pathDistances[0]);
  int currentSpeed = 1;
  if (path[1] == '5' || path[1] == 5) currentSpeed = 5;
  for (int i = 2; i < ArraySize; i++)
  {
    if (currentSpeed == 5) pathTimes[i] = pathDistances[i] * cmToMsFactor5thSpeed;
    else pathTimes[i] = pathDistances[i] * cmToMsFactor1stSpeed;

    if (path[i] == '5' || path[i] == 5) currentSpeed = 5;
    else if (path[i] == '1' || path[i] == 1) currentSpeed = 1;
  }
}
void waitForStartButton() {
  int initialReadBtn = digitalRead(button);
  while (initialReadBtn == digitalRead(button)) {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(100, 255, 255);
    }
    FastLED.show();
    delay(50);
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(100, 0, 0);
    }
    FastLED.show();
    delay(50);
    digitalRead(button);
  }

}

void test() {
  Taction = millis();
  updateLedsInSensorsFn = false;
  unsigned long  ledsTimeLimited = 0;
  while (1) {
    updatesensors(currentLineColor);
    wallfollow(20);
    if (distanceR > 100 && (millis() - Taction > 2200) && enetcomLedCounter > 0) {
      while (1) {
        forward(100, 140);
        updatesensors(currentLineColor);
        // myledwhiteon();
        if (CountLines() == 1) {
          //myledwhiteon();
          break;
        }
      }
      break;
    }
    else if (IntDsensors[6] == 1 || IntDsensors[7] == 1) {
      if (enetcomLedCounter == 0) {
        ledsTimeLimited = millis();
      }
      if (millis() - ledsTimeLimited < 300) {
        enetcomLedCounter++;
        leds[enetcomLedCounter - 1] = CHSV(250, 255, 250);
        FastLED.show();
        while (1) {
          wallfollow(20);
          ledsTimeLimited = millis();
          updatesensors(currentLineColor);
          if ((CountLines() == 0) || (distanceR > 90 && (millis() - Taction > 700))) break;
        }
      }
    }
    else wallfollow(20);
  }
}
