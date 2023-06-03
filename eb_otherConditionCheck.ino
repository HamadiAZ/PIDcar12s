
void conditions_manager()
{
  if (otherconditionsCheck())
  {
    myledwhiteon();
    otherconditionsDO();
    Taction = millis();
    otherconditionsCounter++;
    pathSteps++;
  }
  else
    ELSE();
}
boolean otherconditionsCheck()
{

  switch (otherconditionsCounter)
  {
    case 0:
      // Serial.println(" Condition 1 check ");
      return CountLines() >= 3;
      break;
    case 1:
      Serial.println(" Condition 3 check ");
      return CountLines() >= 2;
      break;
    case 2:
      Serial.println(" Condition 4 check ");
      return CountLines() == 0;
      break;
    case 3:
      Serial.println(" Condition 3 check ");
      return CountLines() >= 2;
      break;
    case 4:
      Serial.println(" Condition 5 check ");
      return true;
      break;
    case 5:
      Serial.println(" Condition 5 check ");
      return (distanceF < 50 && distanceL < 40);
      break;

    // ADD CASES IF U HAVE MORE
    default:
      Serial.println("Error! NOMBER OF C IN PATHSTRING IS MORE THAN THE CONDITIONS IN otherconditionsCheck FUNCTION");
      return true; // to continue following and does get stuck
  }
  return false; // if anything missing in the conditions bech lcode may7bsch
}
