

void conditions_manager()
{
  if (conditionsCheck())
  {
    myledwhiteon();
    conditionsDO();
    Taction = millis();
    conditionsCounter++;
    pathSteps++;
  }
  else
    ELSE();
}
boolean conditionsCheck()
{

  switch (conditionsCounter)
  {
  case 0:
    // Serial.println(" Condition 1 check ");
    return true;
    break;
  case 1:
    Serial.println(" Condition 3 check ");
    return true;
    break;
  case 2:
    Serial.println(" Condition 4 check ");
    return true;
    break;
  case 3:
    Serial.println(" Condition 3 check ");
    return true;
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
    Serial.println("Error! NOMBER OF C IN PATHSTRING IS MORE THAN THE CONDITIONS IN condition check FUNCTION");
    return true; // to continue following and does get stuck
  }
  return false; // if anything missing in the conditions, the code doesnt break
}
