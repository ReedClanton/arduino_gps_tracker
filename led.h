/** External Import(s) **/
// NoOp

/** Define Macro(s) **/
// NoOp

/** Custom Import(s) **/
// NoOp

/** Global Variable(s) **/
unsigned char led_pin = LED_PIN;


void setupLed(unsigned char pin = LED_PIN) {
  led_pin = pin;
  pinMode(led_pin, OUTPUT);
}

short updateLedState(int val_check_1 = LOW, int val_check_2 = LOW, int val_check_3 = LOW, int val_check_4 = LOW) {
  if (val_check_1 == HIGH || val_check_2 == HIGH || val_check_3 == HIGH || val_check_4 == HIGH) {
    digitalWrite(led_pin, HIGH);
    return HIGH;
  } else {
    digitalWrite(led_pin, LOW);
    return LOW;
  }
}
