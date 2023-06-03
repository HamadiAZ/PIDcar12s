void case_11111()
{ // compare (readings , string elli feha les X lezm tkoun 2eme parameter)
  if (path[pathSteps] == 'F')
  {
    ////Serial.println("FORWARD : PATH F : ");
    myledwhiteon();
    pathSteps++;
    forward(200, 200);
    delay(120);
    Taction = millis();
  } else if (path[pathSteps] == 'W') {
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
    //    right(100, 180);
    //    delay(150);
    //    while (1)
    //    {
    //      right(100, 180); // ////Serial.println("right");
    //      updatesensors(currentLineColor);
    //      if ((compare(IntDsensors, "00xxxxxx11x0") || compare(IntDsensors, "xx0xxxx11000")) && CountLines() <= 1)
    //        break;
    //    }
    //    left(100, 120);
    //    delay(50);
    //    stope();
    Taction = millis();
  }
  else if (path[pathSteps] == 'L')
  {
    ////Serial.println("90° LEFT : PATH L : ");
    pathSteps++;
    myledwhiteon();
    left(180, 140);
    delay(150);
    while (1)
    {
      left(120, 100); // ////Serial.println("left");
      updatesensors(currentLineColor);
      if ((IntDsensors[6] == 1) && (IntDsensors[0] == 0))
        break;
    }
    Taction = millis();
  }
  else if (path[pathSteps] == 'l')
  {
    pathSteps++;
    myledwhiteon();
    left(100, 80);
    delay(250);
    while (1)
    {
      left(60, 60); // ////Serial.println("right");
      updatesensors(currentLineColor);
      if (((IntDsensors[0] == 0) && (IntDsensors[11] == 0) && (IntDsensors[1] == 1)) || ((IntDsensors[1] == 0) && (IntDsensors[10] == 0) && (IntDsensors[2] == 1)) || ((CountLines() == 1) && (position < 4000) && (position > 1000) ))
        break;
    }
    Taction = millis();
  }
  //    else if (path[pathSteps] == 'r')
  //    {
  //        ////Serial.print("right 90 safya with pid");
  //        doublet = millis();
  //        myledwhiteon();
  //        while ((millis() - t) < 500)
  //        {
  //            updatesensors(currentLineColor);
  //            ELSE();
  //        }
  //        pathSteps++;
  //        Taction = millis();
  //    }
  else if (path[pathSteps] == 's')
  {
    ////Serial.println("DEAD STOP , PATHSTRING : s DONE");
    myledwhiteon();
    back(100, 100);
    delay(70);
    stope();
    delay(50000);

  }
  else
  { // ERREUR DANS PATHSTRING GO FOR PID SAFER
    // Y3NI LGUEE DOURA OR INTERSECTION W MALGUECH 7AJA S7I7A FEL PATHSTRING EXEMPLE 00X11 W YALGA LEFT L
    // pathSteps++;
    ELSE();
    ////Serial.println("SENT TO PID FROM 11111 CONDITION");
    // goto jump; // INAGGEZ L ADD PATH , if needed remove the comment above
  }
  // jump:;
}

void case_110x1_1x011(int tempsInterval)
{ // CHANGEMENT DE mode : point of changing found so stop using the mode variable
  // Taction=millis();
  if (path[pathSteps] == 'B') {

    Taction = millis();
    Prevc = 'B';
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'B';
    mode == 'N'; // normal mode ,cad : NO SEARCHING for linecolor switching ,  now Normal line following
  } else if (path[pathSteps] == 'W') {

    Taction = millis();
    Prevc = 'W';
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'W';
    mode == 'N'; // normal mode ,cad : NO SEARCHING for linecolor switching ,  now Normal line following
  } else
  {
    ELSE();
    ////Serial.print("SENT TO PID FROM 1x0x1 CONDITION");
  }
}

void case_2_lines()
{
  if (path[pathSteps] == 'V')
  {
    pathSteps++; // BECH INAGGEZ EL "V" w ychof V YDOUR M3AHA  L wale R
    if ((path[pathSteps] == 'L') )
    {
      ////Serial.print("left 45° angle V");
      myledwhiteon();
      left(150, 100);
      delay(250);
      while (true)
      {
        updatesensors(currentLineColor);
        left(120, 80 );
        //if ((IntDsensors[0] == 0) && (IntDsensors[1] == 0) && (IntDsensors[5] == 1) && (IntDsensors[7] == 0)) break;
        if (CountLines() == 1) {
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
        //if ((IntDsensors[0] == 0) && (IntDsensors[1] == 0) && (IntDsensors[5] == 1) && (IntDsensors[7] == 0)) break;
        if (CountLines() == 1) break;
      }
      Taction = millis();
      pathSteps++;
    }
    else
    {
      ELSE();
      ////Serial.print("SENT TO PID FROM CountLines()==2 CONDITION");
    }
  } else if (path[pathSteps] == 'B') {

    Taction = millis();
    Prevc = 'B';
    pathSteps++;
    myledwhiteon();
    currentLineColor = 'B';
    mode == 'N'; // normal mode ,cad : NO SEARCHING for linecolor switching ,  now Normal line following
  } else if (path[pathSteps] == 'W') {

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
  else if (path[pathSteps] == 'L')
  {
    ////Serial.println("90° LEFT : PATH L : ");
    pathSteps++;
    myledwhiteon();
    delay(50);
    while (1)
    {

      left(200, 100); // ////Serial.println("left");
      updatesensors(currentLineColor);
      if (IntDsensors[0] == 1)
        break;
    }
    Taction = millis();
  }
  //  else if (path[pathSteps] == 'l')
  //  {
  //    ////Serial.print("left 90 safya with pid");
  //    double t = millis();
  //    myledwhiteon();
  //    while ((millis() - t) < 2000)
  //    {
  //      updatesensors(currentLineColor);
  //      ELSE();
  //    }
  //    pathSteps++;
  //    Taction = millis();
  //  }
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
    forward();
    delay(100);
    Taction = millis();
  }
  else if (path[pathSteps] == 'r')
  {
    Taction = millis();
    pathSteps++;
  }    else if (path[pathSteps] == 'M')
  {
    myledwhiteon();
    forward(200, 200);
    Taction = millis();
    delay(100);
    pathSteps++;
    otherconditionsCounter = 0;
  }
  else
  { // ERREUR DANS PATHSTRING GO FOR PID SAFER
    // pathSteps++; ZA3MA KEN Y8LAT AMA 5IR N5ALLOH IZID PATH WALE LE ???
    ELSE();
    //////Serial.println("SENT TO PID FROM 00x11 CONDITION");
  }
}
