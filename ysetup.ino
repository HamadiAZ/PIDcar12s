void setup()
{
  initializeValues(); // MUST BE CALLED FIRST in setup!!
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
  stope();
  qtr.emittersOff();
  qtr.setTypeAnalog(); // or setTypeAnalog()
  qtr.setSensorPins(analog_pins, SensorCount);
  //lcd.begin(16, 2);
  //lcd.clear();
  //// *********************************************************
  //Serial.begin(115200); //  //// DONT FORGOT TO DISABLE THIS BEFORE STARTING THE ROBOT *********************************************************
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();

  initialCheck();
  initialCalcTimes();
  calibratesensors();
  waitForStartButton();
  // BLOCKMOVEMENT = true;
  // stope();
  
  initialAngle = getAngle();
  forward(130, 130);
  delay(100);
}
