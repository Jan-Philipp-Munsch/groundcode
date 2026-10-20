// Kamera-Trigger-Test: zieht D7 (über Spannungsteiler an den Auslöser der
// Bordkamera) im Sekundentakt auf HIGH. 1 s Puls startet/stoppt die
// Videoaufnahme, ein 100-ms-Puls löst ein Foto aus.
//
//   pio run -e camera_trigger -t upload
#include <Arduino.h>

constexpr uint8_t  PIN_CAMERA   = 7;
constexpr uint32_t PULSE_MS     = 1000;   // 100 für Foto
constexpr uint32_t PAUSE_MS     = 1000;

void setup(){
  pinMode(PIN_CAMERA, OUTPUT);
  digitalWrite(PIN_CAMERA, LOW);
}

void loop(){
  digitalWrite(PIN_CAMERA, HIGH);
  delay(PULSE_MS);
  digitalWrite(PIN_CAMERA, LOW);
  delay(PAUSE_MS);
}
