/** External Code Import(s) **/
// NoOp

/** Local Code Import(s) **/
// NoOp

/** Local Macro Import(s) **/
#include "hardware_config.h"

/** Local Macro(s) **/
// NoOp

/** Local Global Variable(s) **/
// NoOp


class MyBuzzer {
  private:
    unsigned char pin_;
    unsigned char tone_;
    bool state_;

  public:
    MyBuzzer (unsigned char pin = BUZZER_PIN, unsigned char buzTone = DEFAULT_BUZZER_TONE, bool state = false) {
      pin_ = pin;
      tone_ = buzTone;
      state_ = state;
      if (state_) {
        tone(pin_, tone_);
      } else {
        noTone(pin_);
      }
    }

    void on() {
      state_ = true;
      tone(pin_, tone_);
    }

    void off() {
      state_ = false;
      noTone(pin_);
    }

    void setTone(unsigned char buzTone) {
      tone_ = buzTone;
    }

    unsigned char getTone() {
      return tone_;
    }

    void setState(bool state) {
      state_ = state;
    }

    bool getState() {
      return state_;
    }
};
