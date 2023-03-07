/** Define Macro(s) **/
// Tracks default potentiometer pin.
#define DEFAULT_POTENTIOMETER_PIN A0

/** Global Variable(s) **/
// Tracks pin that's used (in case default isn't used).
unsigned char potentiometer_pin = DEFAULT_POTENTIOMETER_PIN;


void potentiometerSetup(unsigned char pin = DEFAULT_POTENTIOMETER_PIN) {
  potentiometer_pin = pin;
  pinMode(potentiometer_pin, INPUT);
}

float potentiometerFloat(float start_range = 0, float end_range = 1) {
  return start_range + ((end_range - start_range) / 1023) * analogRead(potentiometer_pin);
}

int potentiometerInt(int start_range = 0, int end_range = 100) {
  return start_range + ((end_range - start_range) / 1023) * analogRead(potentiometer_pin);
}
