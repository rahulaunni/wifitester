 /*drop detecton and encoder button detection*/
void checkButton() {
  const unsigned long LONG_DELTA = 400ul;               // hold seconds for a long press
  const unsigned long DEBOUNCE_DELTA = 10ul;        // debounce time
  static int lastButtonStatus = HIGH;                                   // HIGH indicates the button is NOT pressed
  int buttonStatus;                                                                    // button atate Pressed/LOW; Open/HIGH
  static unsigned long longTime = 0ul, shortTime = 0ul; // future times to determine is button has been poressed a short or long time
  boolean Released = true, Transition = false;                  // various button states
  boolean timeoutShort = false, timeoutLong = false;    // flags for the state of the presses

  buttonStatus = digitalRead(ENCODER_BTN);                // read the button state on the pin "BUTTON_PIN"
  timeoutShort = (millis() > shortTime);                          // calculate the current time states for the button presses
  timeoutLong = (millis() > longTime);

  if (buttonStatus != lastButtonStatus) {                          // reset the timeouts if the button state changed
    shortTime = millis() + DEBOUNCE_DELTA;
    longTime = millis() + LONG_DELTA;
  }

  Transition = (buttonStatus != lastButtonStatus);        // has the button changed state
  Released = (Transition && (buttonStatus == HIGH)); // for input pullup circuit

  lastButtonStatus = buttonStatus;                                     // save the button status

  if (timeoutLong && Released) { // long timeout has occurred and the button was just released

    BTN = 2; // long press
  }

 else if (timeoutShort && Released)                // short timeout has occurred (and not long timeout) and button was just released
  {

    BTN = 1; ///Short press
  }




}

int get_button()
{
  int button = BTN;
  BTN = 0;
  return button;

}
