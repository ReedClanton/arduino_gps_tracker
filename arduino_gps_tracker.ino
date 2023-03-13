/** External Code Import(s) **/
#include <Ethernet.h>

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
bool error = false;


void setup() {
  /* Output Setup */
  myOutput = new Output();
  
  /* LED Setup */
  if (USE_LED) {
    myLed = Led(LED_PIN);
  }
  
  /* Buzzer Setup */
  if (USE_BUZZER) {
    myBuzzer = MyBuzzer();
  }
  
  /* Ethernet Setup */
  EthernetServer server(80);
  byte MAC[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress IP(192, 168, 12, 2);
  // Start the Ethernet connection.
  Ethernet.begin(MAC, IP);
  // Ethernet error checking.
  while (Ethernet.hardwareStatus() == EthernetNoHardware) {
    if (!error) {
      // Display error message.
      myOutput->addOutput("Ethernet shield");
      myOutput->addOutput("not found.");
      myOutput->publish();
      // Turn buzzer one.
      myBuzzer.on();
      // Tack error state.
      error = true;
    }
    // Flip state of LED.
    //if (myLed.state() == HIGH) {
    //  myLed.off();
    //} else {
    //  myLed.on();
    //}
  }
  // Error resolved.
  error = false;

  while (Ethernet.linkStatus() == LinkOFF) {
    if (!error) {
      // Display error message.
      myOutput->addOutput("Ethernet cable not connected.");
      myOutput->publish();
      // Turn buzzer on.
      myBuzzer.on();
      // Track error state.
      error = true;
    }
    // Flit state of LED.
    if (digitalRead(LED_PIN)) {
      myLed.off();
    } else {
      myLed.on();
    }
  }
  // Error resolved.
  error = false;

  // start the server
  //server.begin();
  //myOutput->addPersistentOutputText("IP:    ", String(Ethernet.localIP()));

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
