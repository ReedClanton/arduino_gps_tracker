/** External Import(s) **/
// NoOp

/** Define Macro(s) **/
/* Assign Pin(s) */
#define BUTTON_PIN 4
#define BUZZER_PIN 5
#define DHTPIN 3
/* Set What Hardware is Used */
#define USE_POTENTIOMETER true
#define USE_OLED true
#define USE_SERIAL false
#define USE_PRESSURE_SENSOR true
#define USE_BUTTON true
#define USE_LED true
#define USE_BUZZER true
/* Configuration Value(s) */
#define LOOP_WAIT 0
/* Default Value(s) */
#define DEFAULT_BUZZER_TONE 85
#define SERVO_MIN_POSITION 0
#define SERVO_MAX_POSITION 179
#define DEFAULT_SERVO_POSITION 0

/** Custom Import(s) **/
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
  float pot_val = LOW;
  if (USE_POTENTIOMETER) {
    pot_val = potentiometerFloat();
    outputAdd("Pot:        ", String(pot_val));
  }
  /* Button Status */
  int button_state = LOW;
  if (USE_BUTTON) {
    button_state = buttonState();
    if (button_state == HIGH) {
      outputAdd("Button:       ", "ON");
    } else {
      outputAdd("Button:      ", "OFF");
    }
  }
  /* Set LED Status */
  if (USE_LED) {
    if (updateLedState(button_state, pot_val) == HIGH) {
      outputAdd("LED:          ", String("ON"));
    } else {
      outputAdd("LED:         ", String("OFF"));
    }
  }
  /* Pressure Sensor */
  if (USE_PRESSURE_SENSOR) {
    outputAdd("Temp:       ", String(CelsiusToFahrenheit(Pressure.readTemperature())), " F");
    outputAdd("Pres:   ", String(Pressure.readPressure()), " Pa");
    outputAdd("Alt:   ", String(Pressure.readAltitude()), " m");
  }
  /* Buzzer */
  if (USE_BUZZER) {
    if (button_state == HIGH || pot_val == HIGH) {
      int buzzer_tone = DEFAULT_BUZZER_TONE;
      if (pot_val != LOW) {
        buzzer_tone = pot_val * 100;
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

int buttonState() {
  return digitalRead(BUTTON_PIN);
}
