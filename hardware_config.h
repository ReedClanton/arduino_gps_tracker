/** Define Macro(s) **/
/* Assign Pin(s) */
#define POTENTIOMETER_PIN A0
// TODO:  Button pin works when set to 4, but that conflicts with ethernet shield, need to sort out.
#define BUTTON_PIN 7
#define BUZZER_PIN 5
#define LED_PIN 6
#define DHTPIN 3
/* Set What Hardware is Used */
#define USE_OLED true
#define USE_SERIAL true
#define USE_PRESSURE_SENSOR true
#define USE_BUTTON false
#define USE_LED true
#define USE_BUZZER true
/* Default Value(s) */
#define DEFAULT_BUZZER_TONE 30
#define LOOP_WAIT 0
#define SERIAL_BAUD 9600
