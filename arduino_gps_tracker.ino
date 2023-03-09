/** External Code Import(s) **/
// NoOp

/** Define Macro(s) **/
// NoOp

/** Custom Import(s) **/
#include "hardware_config.h"
#include "Led.h"
#include "MyBuzzer.h"
#include "Output.h"
#include "button.h"
#include "potentiometer.h"
#include "output.h"
#include "math.h"

/** Global Variable(s) **/
Led myLed;
MyBuzzer myBuzzer;
//Output myOutput;


void setup() {
  /* Output Setup */
  outputSetup(USE_OLED, USE_SERIAL);
  //myOutput = Output(USE_OLED, USE_SERIAL);
  if (USE_LED) {
    myLed = Led(LED_PIN);
  }
  if (USE_BUZZER) {
    myBuzzer = MyBuzzer();
  }

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
    //myOutput.addOutput("Pot:        ", String(potVal));
    outputAdd("Pot:        ", String(potVal));
  }
  /* Button Status */
  int buttonState = LOW;
  if (USE_BUTTON) {
    buttonState = getButtonState();
  }
  /* Set LED Status */
  if (USE_LED) {
    if (buttonState == HIGH || potVal == HIGH) {
      myLed.on();
    } else {
      myLed.off();
    }
  }
  /* Pressure Sensor */
  if (USE_PRESSURE_SENSOR) {
    // Temperature.
    //myOutput.addOutput("Temp:       ", String(CelsiusToFahrenheit(Pressure.readTemperature())), " F");
    outputAdd("Temp:       ", String(CelsiusToFahrenheit(Pressure.readTemperature())), " F");
    // Pressure.
    //myOutput.addOutput("Pres:   ", String(Pressure.readPressure()), " Pa");
    outputAdd("Pres:   ", String(Pressure.readPressure()), " Pa");
    // Altitude.
    //myOutput.addOutput("Alt:     ", String(MetersToFeet(Pressure.readAltitude())), " ft");
    outputAdd("Alt:     ", String(MetersToFeet(Pressure.readAltitude())), " ft");
  }
  /* Buzzer */
  if (USE_BUZZER) {
    if (buttonState == HIGH || potVal == HIGH) {
      if (potVal != LOW) {
        myBuzzer.setTone(potVal * 100);
      }
      myBuzzer.on();
    } else {
      myBuzzer.off();
    }
  }

  //myOutput.publish();
  outputPublish();
  
  delay(LOOP_WAIT);
}
