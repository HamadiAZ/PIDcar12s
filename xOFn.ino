// this tab is about OTHER GENERAL USE FUNCTIONS


void waitForStartButton()
{
  int initialReadBtn = digitalRead(button);
  while (initialReadBtn == digitalRead(button))
  {
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
