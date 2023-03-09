/** External Code Import(s) **/
#include "Arduino_SensorKit.h"

/** Local Code Import(s) **/
// NoOp

/** Local Macro Import(s) **/
#include "hardware_config.h"

/** Local Macro(s) **/
// NoOp

/** Local Global Variable(s) **/
// NoOp


class Output {
  private:
    bool oled_;
    bool serial_;
    String outputText_;

  public:
    Output (bool oled = true, bool serial = true, int baud = SERIAL_BAUD) {
      // Track what form(s) of output will be used.
      oled_ = oled;
      serial_ = serial;
      // Setup output methods requested by caller.
      if (oled_) {
        Oled.begin();
        // Set screen rotation.
        Oled.setFlipMode(true);
        // Set font.
        Oled.setFont(u8x8_font_chroma48medium8_r);
      }
      if (serial_) {
        Serial.begin(baud);
      }
    }

    void addOutput(String msg) {
      outputText_ += msg + "\n";
    }

    void addOutput(String title, String msg) {
      outputText_ += title + msg + "\n";
    }

    void addOutput(String title, String msg, String units) {
      outputText_ += title + msg + units + "\n";
    }

    void publish() {
      if (oled_) {
        /* OLED Reset */
        // TODO
        //Oled.clear();
        // Set screen origen.
        Oled.setCursor(0, 0);
        /* OLED Publish & Reset */
        Oled.print(outputText_);
        Oled.refreshDisplay();
      }
      if (serial_) {
        /* Serial Publish & Reset */
        Serial.println(outputText_);
      }
      outputText_ = "";
    }
};
