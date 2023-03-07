/** External Import(s) **/
// NoOp

/** Define Macro(s) **/
// NoOp

/** Custom Import(s) **/
// Assign Pin(s).
#include "pins.h"

/** Global Variable(s) **/
// NoOp

int getButtonState() {
  return digitalRead(BUTTON_PIN);
}
