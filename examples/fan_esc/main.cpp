// Fan-ESC-Test: fährt einen bidirektionalen ESC (Neutral 1500 µs) an D9
// langsam von Neutral auf 900 µs und zurück. Versuch für den Rollantrieb.
//
//   pio run -e fan_esc -t upload
#include <Arduino.h>
#include <Servo.h>

constexpr uint8_t  PIN_ESC        = 9;
constexpr int      ESC_NEUTRAL_US = 1500;
constexpr int      ESC_SWEEP_US   = 600;    // bis 900 µs
constexpr uint32_t STEP_MS        = 10;
constexpr uint32_t PAUSE_MS       = 5000;

Servo esc;

void setup(){
  esc.attach(PIN_ESC);
  esc.writeMicroseconds(ESC_NEUTRAL_US);   // ESC initialisiert sich auf Neutral
  delay(2000);
}

void loop(){
  for (int i = 0; i <= ESC_SWEEP_US; ++i){
    esc.writeMicroseconds(ESC_NEUTRAL_US - i);
    delay(STEP_MS);
  }
  esc.writeMicroseconds(ESC_NEUTRAL_US);
  delay(PAUSE_MS);
}
