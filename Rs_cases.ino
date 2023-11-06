void case_11111()
{ // compare (readings , our but/desired state)
  if (path[pathSteps] == 'F')
  {
    ////Serial.println("FORWARD : PATH F : ");
    myledwhiteon();
    pathSteps++;
    forward(200, 200);
    delay(120);
    Taction = millis();
  }
  else if (path[pathSteps] == 'W')
  {
    currentLineColor = 'W';
    myledwhiteon();
    pathSteps++;
    Prevc = 'W';
    myledwhiteon();
    mode == 'N'; //
  }

  else if (path[pathSteps] == 'R')
  {
    ////Serial.println("90° RIGHT : PATH R : ");
    pathSteps++;
    myledwhiteon();
    turn(-100);
    Taction = millis();
  }
  else if (path[pathSteps] == 'L')
  {
    ////Serial.println("90° LEFT : PATH L : ");
    pathSteps++;
    myledwhiteon();
    turn(100);
    Taction = millis();
  }
  else if (path[pathSteps] == 's')
  {
    ////Serial.println("DEAD STOP , PATHSTRING : s DONE");
    myledwhiteon();
    back(160, 160);
    delay(90);
    stope();
    delay(500000);
  }
  else
  { // found the sensor case but not the right char in the pathstring => ignore it 
    ELSE();
  }
  // jump:;
}

void case_110x1_1x011()
{ 
  if (path[pathSteps] == 'B')
  {
    Taction = millis();
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'B';
  }
  else if (path[pathSteps] == 'W')
  {
    Taction = millis();
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'W';
  }
  else
  {
    ELSE();
    ////Serial.print("SENT TO PID FROM 1x0x1 CONDITION");
  }
}

void case_2_lines()
{
  if (path[pathSteps] == 'V')
  {
    pathSteps++; // jump the "V" and check if the next is R or L
    if ((path[pathSteps] == 'L'))
    {
      ////Serial.print("left 45° angle V");
      myledwhiteon();
      left(150, 100);
      delay(250);
      while (true)
      {
        updatesensors(currentLineColor);
        left(120, 80);
        // if ((IntDsensors[0] == 0) && (IntDsensors[1] == 0) && (IntDsensors[5] == 1) && (IntDsensors[7] == 0)) break;
        if (CountLines() == 1)
        {
          right();
          delay(50);
          stope();
          break;
        }
      }
      Taction = millis();
      pathSteps++;
    }
    else if ((path[pathSteps] == 'R') || (path[pathSteps] == 'r'))
    {
      ////Serial.print("left 45° angle V");
      myledwhiteon();
      right(50, 120);
      delay(370);
      while (true)
      {
        updatesensors(currentLineColor);
        right(30, 210);
        // if ((IntDsensors[0] == 0) && (IntDsensors[1] == 0) && (IntDsensors[5] == 1) && (IntDsensors[7] == 0)) break;
        if (CountLines() == 1)
          break;
      }
      Taction = millis();
      pathSteps++;
    }
    else
    {
      ELSE();
      ////Serial.print("SENT TO PID FROM CountLines()==2 CONDITION");
    }
  }
  else if (path[pathSteps] == 'B')
  {

    Taction = millis();
    Prevc = 'B';
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'B';
    mode == 'N'; // normal mode ,cad : NO SEARCHING for linecolor switching ,  now Normal line following
  }
  else if (path[pathSteps] == 'W')
  {

    Taction = millis();
    Prevc = 'W';
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'W';
    mode == 'N'; // normal mode ,cad : NO SEARCHING for linecolor switching ,  now Normal line following
  }
  else
  {
    ELSE();
    ////Serial.print("SENT TO PID FROM CountLines()==2 CONDITION");
  }
}

void case_111x0()
{ //  left or f

  if (path[pathSteps] == 'f')
  {
    ////Serial.println("FORWARD : PATH F : ");
    pathSteps++;
    myledwhiteon();
    forward(200, 200);
    delay(100);
    Taction = millis();
  }
  else if (path[pathSteps] == 'l')
  {
    myledwhiteon();
    turn(100);
    Taction = millis();
    pathSteps++;
  }
  else
  { // ERREUR DANS PATHSTRING GO FOR PID SAFER
    ELSE();
    //////Serial.print("SENT TO PID FROM 11x00 CONDITION");
  }
}

void case_0x111()
{ //  right or f //
  //////Serial.print("debugging ENTER LOOP  ");
  //////Serial.println(path[pathSteps]);
  if (path[pathSteps] == 'f')
  {
    Taction = millis();
    myledwhiteon();
    // ////Serial.println("FORWARD : PATH F : ");
    pathSteps++;
    forward(120, 120);
    delay(150);
    Taction = millis();
  }
  else if (path[pathSteps] == 'r')
  {
    myledwhiteon();
    turn(-100);
    Taction = millis();
    pathSteps++;
  }
  else
  { 
    ELSE();
 
  }
}
