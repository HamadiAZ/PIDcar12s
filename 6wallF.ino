float Kp2 = 3.5;//6
float Kd2 = 5;
void wallfollow(int offset = 10, char wall = 'L', boolean autoTurn = true) // offset : distance to the wall
{
  int derivative = 0;
  int Tp = 90;
  int error = 0, lasterror, Turn, powerR, powerL;
  int r, l;
  distanceF = ultrasonicF.read();
  distanceL = ultrasonicL.read(); // Serial.print("distance left : "); Serial.println(distanceL);Serial.println("*************");
  distanceR = ultrasonicR.read(); // Serial.print("distance right : "); Serial.println(distanceR);Serial.println("*******************************************");
  int enteringLoopTime;
  if (distanceR <= 2) 
  {
    enteringLoopTime = millis();
    while (1) 
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
    right(80, 80); // counter inertia
    delay(40);     // counter inertia
    forward(200, 200);      
    delay(200);
  }
  else if (distanceL <= 2) // KI YOD5L F 7IT lisar // CBN
  {

    delay(10);
    back(170, 70);
    delay(250);
    left(80, 80); // counter inertia
    delay(40);    // counter inertia
    stope();      
  }
  else if ((distanceF < 2) && (wall == 'R'))
  {
    enteringLoopTime = millis();
    while (1) // turn left until the robot is parallel to the right wall
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
  else if ((distanceF < 2) && (wall == 'L'))
  {
    enteringLoopTime = millis();
    while (1) // turn right until the robot is parallel to the left wall
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
    }  else { // left wall follow
      error = offset - distanceL;
      localKp2 = Kp2;
      //      if (abs(error) > 80)  {
      //        localKp2 = 0.01;
      //        Kd2 = 15;
      //      }
      //      else
      //      {
      //        if (error < 0) {
      //          //b3id
      //          localKp2 = 6;
      //          Kd2 = 1;
      //        } else {//GRIB
      //          localKp2 = 12;
      //          Kd2 = 0.1;
      //        }
      //      }
    }
    derivative = error - lasterror;
    Turn = localKp2 * error + Kd2 * derivative;
    r = Tp - Turn;
    l = Tp + Turn;
    r = constrain(r, 0, 200);
    l = constrain(l, 0, 200);
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
    //                while (1) // 
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
    //                left(80, 80); //
    //                delay(40);    // 
    //                stope();      // 
    //            }
    //            derivative = error - lasterror;
    //            Turn = Kp2 * error + Kd2 * derivative;
    //            r = Tp + Turn;
    //            l = Tp - Turn;
    //            l = constrain(l, 0, 255);
    //            r = constrain(r, 0, 190);
    //            // r = map(r, -160, 160, 40, 130);  // 
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
