/** External Import(s) **/
// NoOp

/** Define Macro(s) **/
/* Configuration Value(s) */
#define LOOP_WAIT 0
/* Default Value(s) */
#define DEFAULT_BUZZER_TONE 85

/** Custom Import(s) **/
#include "hardware_config.h"
#include "button.h"
#include "potentiometer.h"
#include "output.h"
#include "math.h"
#include "led.h"

/** Global Variable(s) **/
// NoOp


void setup() {
  /* Output Setup */
  outputSetup(USE_OLED, USE_SERIAL);
  if (USE_LED) { setupLed(LED_PIN); }
  if (USE_BUZZER) { pinMode(BUZZER_PIN, OUTPUT); }

  /* Input Setup */
  if (USE_POTENTIOMETER) { potentiometerSetup(); }
  if (USE_BUTTON) { pinMode(BUTTON_PIN, INPUT); }

  /* Sensor Setup */
  if (USE_PRESSURE_SENSOR) { Pressure.begin(); }
}

void loop() {
  /* Potentiometer */
  float potVal = LOW;
  if (USE_POTENTIOMETER) {
    potVal = potentiometerFloat();
    outputAdd("Pot:        ", String(potVal));
  }
  /* Button Status */
  int buttonState = LOW;
  if (USE_BUTTON) {
    buttonState = getButtonState();
    if (buttonState == HIGH) {
      outputAdd("Button:       ", "ON");
    } else {
      outputAdd("Button:      ", "OFF");
    }
  }
  /* Set LED Status */
  if (USE_LED) {
    if (updateLedState(buttonState, potVal) == HIGH) {
      outputAdd("LED:          ", String("ON"));
    } else {
      outputAdd("LED:         ", String("OFF"));
    }
  }
  /* Pressure Sensor */
  if (USE_PRESSURE_SENSOR) {
    outputAdd("Temp:       ", String(CelsiusToFahrenheit(Pressure.readTemperature())), " F");
    outputAdd("Pres:   ", String(Pressure.readPressure()), " Pa");
    outputAdd("Alt:     ", String(MetersToFeet(Pressure.readAltitude())), " ft");
  }
  /* Buzzer */
  if (USE_BUZZER) {
    if (buttonState == HIGH || potVal == HIGH) {
      int buzzer_tone = DEFAULT_BUZZER_TONE;
      if (potVal != LOW) {
        buzzer_tone = potVal * 100;
      }
      tone(BUZZER_PIN, buzzer_tone);
      // TODO: fix jank.
      if (buzzer_tone == 100) {
        outputAdd("Buzzer:      ", String(buzzer_tone));
      } else if (buzzer_tone > 9) {
        outputAdd("Buzzer:       ", String(buzzer_tone));
      } else {
        outputAdd("Buzzer:        ", String(buzzer_tone));
      }
    } else {
      noTone(BUZZER_PIN);
      outputAdd("Buzzer:      ", "OFF");
    }
  }

  outputPublish();
  
  delay(LOOP_WAIT);
}
