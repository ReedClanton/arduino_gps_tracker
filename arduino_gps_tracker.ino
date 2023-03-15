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
// TODO: Move.
bool error = false;
// TODO: Move and break out port into constent.
EthernetServer server(80);
// TODO: Move.
IPAddress IP(192, 168, 12, 2);
// TODO: Move.
byte MAC[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};


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
  // Start the Ethernet connection.
  Ethernet.begin(MAC, IP);
  // Start the server.
  server.begin();

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
  // Error check ethernet hardware.
  errorCheckEthernetShieldConnected();
  errorCheckEthernetCableConnected();
  // Display network info.
  myOutput->addOutput("IP:     ", String(Ethernet.localIP()));
  // Listen for incoming clients.
  EthernetClient client = server.available();
  if (client) {
    //Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    //Serial.println("client disconnected");
  }

  
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

// TODO: Move out of this file.
void errorCheckEthernetShieldConnected() {
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
    if (myLed.state()) {
      myLed.off();
    } else {
      myLed.on();
    }
    delay(250);
  }
  // Error resolved.
  error = false;
}

// TODO: Move out of this file.
void errorCheckEthernetCableConnected() {
  while (Ethernet.linkStatus() == LinkOFF) {
    if (!error) {
      // Display error message.
      myOutput->addOutput("Ethernet cable");
      myOutput->addOutput("not connected.");
      myOutput->publish();
      // Turn buzzer on.
      myBuzzer.on();
      // Track error state.
      error = true;
    }
    // Flit state of LED.
    if (myLed.state()) {
      myLed.off();
    } else {
      myLed.on();
    }
    delay(250);
  }
  // Error resolved.
  error = false;
}
