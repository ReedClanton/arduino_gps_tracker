/** External Import(s) **/
// NoOp

/** Local Code Import(s) **/
// NoOp

/** Local Macro Import(s) **/
#include "hardware_config.h"

/** Local Macro(s) **/
// NoOp

/** Local Global Variable(s) **/
// NoOp


class Potentiometer {
  private:
    unsigned char pin_;
    bool state_;

  public:
    Potentiometer (unsigned char pin = POTENTIOMETER_PIN) {
      pin_ = pin;
      pinMode(pin_, INPUT);
    }

    float val(float startRange=0, float endRange=1) {
      return startRange + ((endRange - startRange) / 1023) * analogRead(pin_);
    }
};
