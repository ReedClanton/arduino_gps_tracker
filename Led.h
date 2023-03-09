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


class Led {
  private:
    unsigned char pin_;
    bool state_;

  public:
    Led (unsigned char ledPin = LED_PIN) {
      pin_ = ledPin;
      state_ = LOW;
      pinMode(pin_, OUTPUT);
    }

    void on() {
      state_ = HIGH;
      digitalWrite(pin_, state_);
    }

    void off() {
      state_ = LOW;
      digitalWrite(pin_, state_);
    }

    bool state() {
      return state_;
    }
};
