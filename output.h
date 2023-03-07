/** External Import(s) **/
#include "Arduino_SensorKit.h"

/** Define Macro(s) **/
#define OLED_USED true
#define SERIAL_USED true
#define SERIAL_BAUD 9600

/** Global Variable(s) **/
// Tracks text to be sent to output.
String output_text = "";
// Tracks if the OLED display should be used.
bool oled_used = OLED_USED;
// Tracks if serial output should be used.
bool serial_used = SERIAL_USED;


void outputSetup(bool use_oled = OLED_USED, bool use_serial = SERIAL_USED, int serial_baud = SERIAL_BAUD) {
  // Track what type(s) of output will be used.
  oled_used = use_oled;
  serial_used = use_serial;

  /* Initialize Utilized Output Type(s) */
  if (oled_used) {
    Oled.begin();
    // Set screen rotation.
    Oled.setFlipMode(true);
    // Set font.
    Oled.setFont(u8x8_font_chroma48medium8_r);
    // TODO: Remove.
    //Oled.setFont(u8x8_font_8x13B_1x2_f);
  }
  
  if (serial_used) {
    Serial.begin(serial_baud);
  }
}

void outputAdd(String msg) {
  if (oled_used || serial_used) {
    output_text += msg + "\n";
    //if (new_line) {
    //  output_text += "\n";
    //}
  }
}

void outputAdd(String title, String msg) {
  if (oled_used || serial_used) {
    output_text += title + msg + "\n";
    //if (new_line) {
    //  output_text += "\n";
    //}
  }
}

void outputAdd(String title, String msg, String units) {
  if (oled_used || serial_used) {
    output_text += title + msg + units + "\n";
    //if (new_line) {
    //  output_text += "\n";
    //}
  }
}

void outputPublish() {
  if (oled_used) {
    /* OLED Reset */
    // TODO
    //Oled.clear();
    // Set screen origen.
    Oled.setCursor(0, 0);
    /* OLED Publish & Reset */
    Oled.print(output_text);
    Oled.refreshDisplay();
  }
  if (serial_used) {
    /* Serial Publish & Reset */
    Serial.println(output_text);
  }
  output_text = "";
}
