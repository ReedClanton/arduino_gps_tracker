/** External Code Import(s) **/
// NoOp

/** Define Macro(s) **/
// NoOp

/** Custom Import(s) **/
#include "hardware_config.h"
#include "Led.h"
#include "MyBuzzer.h"
#include "Output.h"
#include "Potentiometer.h"
#include "math.h"

/** Global Variable(s) **/
Led myLed;
MyBuzzer myBuzzer;
Output* myOutput;
Potentiometer* myPot;


void setup() {
  /* Output Setup */
  myOutput = new Output();
  if (USE_LED) {
    myLed = Led(LED_PIN);
  }
  if (USE_BUZZER) {
    myBuzzer = MyBuzzer();
  }

  /* Input Setup */
  myPot = new Potentiometer();
  if (USE_BUTTON) {
    pinMode(BUTTON_PIN, INPUT);
  }

  /* Sensor Setup */
  if (USE_PRESSURE_SENSOR) {
    Pressure.begin();
  }
}

void loop() {
  /* Potentiometer */
  myOutput->addOutput("Pot:        ", String(myPot->val()));
  int potVal = myPot->val(0, 100);
  if (potVal < 100) {
    myOutput->addOutput("Pot:          ", String(potVal));
  } else {
    myOutput->addOutput("Pot:         ", String(potVal));
  }
  /* Button Status */
  int buttonState = LOW;
  if (USE_BUTTON) {
    buttonState = digitalRead(BUTTON_PIN);
  }
  /* Set LED Status */
  if (USE_LED) {
    if (buttonState == HIGH || myPot->val() == HIGH) {
      myLed.on();
    } else {
      myLed.off();
    }
  }
  /* Pressure Sensor */
  if (USE_PRESSURE_SENSOR) {
    // Temperature.
    myOutput->addOutput("Temp:       ", String(CelsiusToFahrenheit(Pressure.readTemperature())), " F");
    // Pressure.
    myOutput->addOutput("Pres:   ", String(Pressure.readPressure()), " Pa");
    // Altitude.
    myOutput->addOutput("Alt:     ", String(MetersToFeet(Pressure.readAltitude())), " ft");
  }
  /* Buzzer */
  if (USE_BUZZER) {
    if (buttonState == HIGH || myPot->val() == HIGH) {
      if (myPot->val() != LOW) {
        myBuzzer.setTone(myPot->val(0, 100));
      }
      myBuzzer.on();
    } else {
      myBuzzer.off();
    }
  }

  myOutput->publish();
  
  delay(LOOP_WAIT);
}
