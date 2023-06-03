void wallfollow(int offset = 16, char wall = 'L', boolean autoTurn = true) // offset : distance to the wall
{
  int derivative = 0;
  int Tp = 80;
  int Kp2 = 3.5;//6
  int Kd2 = 5;
  // Kp2 = 6; CCV //Kd2 = 30; BBEST
  // Kp2 = 8; CCV //Kd2 = 30;
  int error = 0, lasterror, Turn, powerR, powerL;
  int r, l;
  distanceF = ultrasonicF.read();
  distanceL = ultrasonicL.read(); // Serial.print("distance left : "); Serial.println(distanceL);Serial.println("*************");
  distanceR = ultrasonicR.read(); // Serial.print("distance right : "); Serial.println(distanceR);Serial.println("*******************************************");
  // distanceL=10;
  int enteringLoopTime;
  if (distanceR <= 2) // KI YOD5LL F 7IT IMIN MEL 50° JSUQA 30°// CBN
  {
    enteringLoopTime = millis();
    while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
    {
      distanceR = ultrasonicR.read();
      Serial.print("distance right : ");
      Serial.println(distanceR);
      Serial.println("*******************************************");
      delay(10);
      back(120, 250);
      if (distanceR >= 8 || millis() - enteringLoopTime > 1000)
      {
        break;
      };
    }
    delay(10);
    right(80, 80); // bech y7abes eddoran bel inertie
    delay(40);     // bech y7abes eddoran bel inertie
    forward(200, 200);      // bech y7abes
    delay(200);
  }
  else if (distanceL <= 1) // KI YOD5L F 7IT lisar // CBN
  {

    delay(10);
    back(170, 70);
    delay(250);
    left(80, 80); // bech y7abes eddoran bel inertie
    delay(40);    // bech y7abes eddoran bel inertie
    stope();      // bech y7abes
  }
  else if ((distanceF < 3) && (wall == 'R'))
  {
    enteringLoopTime = millis();
    while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
    {
      distanceF = ultrasonicF.read();
      Serial.println(distanceF);
      delay(10);
      back(50, 190);
      if (distanceF >= 10 || millis() - enteringLoopTime > 1000)
      {
        forward(200, 80);
        delay(200);
        break;
      };
    }
  }
  else if ((distanceF < 3) && (wall == 'L'))
  {
    enteringLoopTime = millis();
    while (1) // idour imin jusqa YARJA3 PARALLEL LEL 7IT lisar
    {
      distanceF = ultrasonicF.read();
      Serial.println(distanceF);
      delay(10);
      back(190, 50);
      if (distanceF >= 10 || millis() - enteringLoopTime > 1000)
      {
        forward(80, 200);
        delay(200);
        break;
      };
    }
  }
  else
  { // PID FOLLOW
    int localKp2;
    if (wall == 'R')
    { // right wall follow
      error = distanceR - offset;
      if (abs(error) > 80)  {
        localKp2 = 0.01;
        Kd2 = 15;
      }
      //            else if (abs(error) > 30)
      //               { localKp2 = 1;Kd2 = 5;}
      else
      {
        if (error > 0) {
          //b3id
          localKp2 = 10;
          Kd2 = 1;
        } else {//GRIB
          localKp2 = 12;
          Kd2 = 0.1;
        }
      }
    }  else{ // left wall follow
      error = offset - distanceL;
       localKp2 = 5;
        Kd2 = 15;
//      if (abs(error) > 80)  {
//        localKp2 = 0.01;
//        Kd2 = 15;
//      }
//      else
//      {
        if (error < 0) {
          //b3id
          localKp2 = 5;
          //Kd2 = 1;
        } else {//GRIB
          localKp2 = 3;
         // Kd2 = 0.1;
        }
//      }
    }





    //            if ((abs(error) < offset * 1.2) && (distanceF < 20) && (distanceL > 50) && (autoTurn == true))
    //            {
    //                enteringLoopTime = millis();
    //                while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
    //                {
    //                    distanceF = ultrasonicF.read();
    //                    Serial.print("distance right : ");
    //                    Serial.println(distanceR);
    //                    Serial.println("*******************************************");
    //                    delay(10);
    //                    left(150, 70);
    //                    if (distanceF >= 80 || millis() - enteringLoopTime > 1000)
    //                    {
    //                        break;
    //                    };
    //                }
    //                delay(30);
    //                right(80, 80); // bech y7abes eddoran bel inertie
    //                delay(40);     // bech y7abes eddoran bel inertie
    //                stope();       // bech y7abes
    //            }
    derivative = error - lasterror;
    Turn = localKp2 * error + Kd2 * derivative;
    r = Tp - Turn;
    l = Tp + Turn;
    r = constrain(r, 0, 100);
    l = constrain(l, 0, 100);
    // r = map(r, -160, 160, 40, 130);  // 40 OUTMIN ET 110 OUT MAX
    // l = map(l, -2*Tp, 2*Tp, 0 , 170); //BESTTTT + KP 12 0 0
    // l = map(l, -255, 255, 0 , 140);
    lasterror = error;

    //       else
    //        { // left wall follow
    //            Serial.println("IM HERE");
    //            error = distanceL - offset;
    //            int localKd2;
    //            if (abs(error) > 40)
    //                localKd2 = 300;
    //            else
    //                localKd2 = Kd2;
    //            if ((abs(error) < offset * 1) && (distanceF < 25) && (distanceR > 50) && autoTurn == true)
    //            {
    //                enteringLoopTime = millis();
    //                while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
    //                {
    //                    distanceF = ultrasonicF.read();
    //                    Serial.print("distance right : ");
    //                    Serial.println(distanceR);
    //                    Serial.println("*******************************************");
    //                    delay(10);
    //                    right(70, 150);
    //                    if (distanceF >= 80 || millis() - enteringLoopTime > 1000)
    //                    {
    //                        break;
    //                    };
    //                }
    //                delay(30);
    //                left(80, 80); // bech y7abes eddoran bel inertie
    //                delay(40);    // bech y7abes eddoran bel inertie
    //                stope();      // bech y7abes
    //            }
    //            derivative = error - lasterror;
    //            Turn = Kp2 * error + Kd2 * derivative;
    //            r = Tp + Turn;
    //            l = Tp - Turn;
    //            l = constrain(l, 0, 255);
    //            r = constrain(r, 0, 190);
    //            // r = map(r, -160, 160, 40, 130);  // 40 OUTMIN ET 110 OUT MAX
    //            // l = map(l, -2*Tp, 2*Tp, 0 , 170); //BESTTTT + KP 12 0 0
    //            // l = map(l, -255, 255, 0 , 140);
    //            lasterror = error;
    //        }

    forward(r, l);
    Serial.print("wall PID SPEEDS R,L ");
    Serial.print(r);
    Serial.print(" , ");
    Serial.println(l);
    // lel integrale
  }
}

//int wallTimePrev = 0;
//int WallTime = 0;
//void wallfollow(int offset = 20, char wall = 'L', boolean autoTurn = true) // offset : distance to the wall
//{
//  int derivative = 0;
//  int Tp = 80;
//  float Kp2 = 3.5;//6
//  float Kd2 = 5;
//  // Kp2 = 6; CCV //Kd2 = 30; BBEST
//  // Kp2 = 8; CCV //Kd2 = 30;
//  int error = 0, lasterror, Turn, powerR, powerL;
//  int r, l;
//  distanceF = ultrasonicF.read();
//  distanceL = ultrasonicL.read(); // Serial.print("distance left : "); Serial.println(distanceL);Serial.println("*************");
//  distanceR = ultrasonicR.read(); // Serial.print("distance right : "); Serial.println(distanceR);Serial.println("*******************************************");
//  // distanceL=10;
//  int enteringLoopTime;
//  if (distanceR <= 2) // KI YOD5LL F 7IT IMIN MEL 50° JSUQA 30°// CBN
//  {
//    enteringLoopTime = millis();
//    while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
//    {
//      distanceR = ultrasonicR.read();
//      Serial.print("distance right : ");
//      Serial.println(distanceR);
//      Serial.println("*******************************************");
//      delay(10);
//      back(120, 250);
//      if (distanceR >= 8 || millis() - enteringLoopTime > 1000)
//      {
//        break;
//      };
//    }
//    delay(10);
//    right(80, 80); // bech y7abes eddoran bel inertie
//    delay(40);     // bech y7abes eddoran bel inertie
//    forward(200, 200);      // bech y7abes
//    delay(200);
//  }
//  else if (distanceL <= 1) // KI YOD5L F 7IT lisar // CBN
//  {
//
//    delay(10);
//    back(170, 70);
//    delay(250);
//    left(80, 80); // bech y7abes eddoran bel inertie
//    delay(40);    // bech y7abes eddoran bel inertie
//    stope();      // bech y7abes
//  }
//  else if ((distanceF < 3) && (wall == 'R'))
//  {
//    enteringLoopTime = millis();
//    while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
//    {
//      distanceF = ultrasonicF.read();
//      Serial.println(distanceF);
//      delay(10);
//      back(50, 190);
//      if (distanceF >= 10 || millis() - enteringLoopTime > 1000)
//      {
//        forward(200, 80);
//        delay(200);
//        break;
//      };
//    }
//  }
//  else if ((distanceF < 3) && (wall == 'L'))
//  {
//    enteringLoopTime = millis();
//    while (1) // idour imin jusqa YARJA3 PARALLEL LEL 7IT lisar
//    {
//      distanceF = ultrasonicF.read();
//      Serial.println(distanceF);
//      delay(10);
//      back(190, 50);
//      if (distanceF >= 10 || millis() - enteringLoopTime > 1000)
//      {
//        forward(80, 200);
//        delay(200);
//        break;
//      };
//    }
//  }
//  else
//  { // PID FOLLOW
//    int localKp2;
//    if (wall == 'R')
//    { // right wall follow
//      error = distanceR - offset;
//      if (abs(error) > 80)  {
//        localKp2 = 0.01;
//        Kd2 = 15;
//      }
//      //            else if (abs(error) > 30)
//      //               { localKp2 = 1;Kd2 = 5;}
//      else
//      {
//        if (error > 0) {
//          //b3id
//          localKp2 = 10;
//          Kd2 = 1;
//        } else {//GRIB
//          localKp2 = 12;
//          Kd2 = 0.1;
//        }
//      }
//    }  else { // left wall follow
//      //Serial.print(" left wall | distL="); Serial.print(distanceL); Serial.print(" | ");
//      error = offset - distanceL;
//      localKp2 = 5;
//      Kd2 = 15;
//      if (error < 0) {
//        //b3id
//        localKp2 = 3;//5
//        Kd2 = 0.5;//15
//      } else {//GRIB
//        localKp2 = 3.6;
//        Kd2 = 0.1;
//      }
//      //      }
//    }
//
//
//
//
//
//    //            if ((abs(error) < offset * 1.2) && (distanceF < 20) && (distanceL > 50) && (autoTurn == true))
//    //            {
//    //                enteringLoopTime = millis();
//    //                while (1) // idour ISAR jusqa YARJA3 PARALLEL LEL 7IT LIMIN
//    //                {
//    //                    distanceF = ultrasonicF.read();
//    //                    Serial.print("distance right : ");
//    //                    Serial.println(distanceR);
//    //                    Serial.println("*******************************************");
//    //                    delay(10);
//    //                    left(150, 70);
//    //                    if (distanceF >= 80 || millis() - enteringLoopTime > 1000)
//    //                    {
//    //                        break;
//    //                    };
//    //                }
//    //                delay(30);
//    //                right(80, 80); // bech y7abes eddoran bel inertie
//    //                delay(40);     // bech y7abes eddoran bel inertie
//    //                stope();       // bech y7abes
//    //            }
//    wallTimePrev = WallTime;                            // the previous time is stored before the actual time read
//    WallTime = micros();                            // actual time read
//    elapsedTime = (WallTime - wallTimePrev) / 1000;
//    derivative = (error - lasterror) / elapsedTime;
//    //enimLeftDistanceError=derivative;
//    Turn = localKp2 * error + Kd2 * derivative;
//    r = Tp - Turn;
//    l = Tp + Turn;
//    r = constrain(r, 0, 110);
//    l = constrain(l, 0, 150);
//    // r = map(r, -160, 160, 40, 130);  // 40 OUTMIN ET 110 OUT MAX
//    // l = map(l, -2*Tp, 2*Tp, 0 , 170); //BESTTTT + KP 12 0 0
//    // l = map(l, -255, 255, 0 , 140);
//
//    lasterror = error;
//
//    forward(r, l);
////    Serial.print("wall PID SPEEDS R,L ");
////    Serial.print(r);
////    Serial.print(" , ");
////    Serial.println(l);
//    delay(5);
//    // lel integrale
//  }
//}
