// groundcode – Bodenstation (Arduino Nano) für die Rakete "Mission Space"
//
// Empfängt die Telemetrie-Zeilen des Flugcomputers über ein HC-12-Funkmodul
// (433 MHz) und gibt sie auf der USB-Konsole aus. Heute versteht sie das
// Beacon-Format des Test-Sketches `radio_beacon` im Repo mission_space:
//
//     BEACON,<seq>,<millis>
//
// und zählt dabei verlorene Pakete. Ein echtes Telemetrieprotokoll kommt mit
// dem Flugzustandsautomaten der Firmware.
//
// Verdrahtung:  D10 <- HC-12 TXD   D11 -> HC-12 RXD (über Spannungsteiler, 3,3 V)
//               USB-Serial bleibt für den Monitor frei (9600 Bd).
#include <Arduino.h>
#include <SoftwareSerial.h>

constexpr uint8_t  PIN_HC12_RX = 10;   // Nano liest hier den HC-12-TXD
constexpr uint8_t  PIN_HC12_TX = 11;   // Nano sendet hier zum HC-12-RXD
constexpr uint32_t HC12_BAUD   = 9600; // Werksdefault des HC-12
constexpr uint32_t USB_BAUD    = 9600;

SoftwareSerial hc12(PIN_HC12_RX, PIN_HC12_TX);

static char   lineBuf[64];
static size_t lineLen   = 0;
static long   lastSeq   = -1;
static long   received  = 0;
static long   lost      = 0;

static void handleBeacon(const char* s){
  // s zeigt hinter "BEACON,"
  char buf[64];
  strncpy(buf, s, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = 0;

  char* tokSeq = strtok(buf, ",");
  char* tokMs  = strtok(nullptr, ",");
  const long seq = tokSeq ? atol(tokSeq) : -1;
  const long ms  = tokMs  ? atol(tokMs)  : -1;

  received++;
  if (lastSeq >= 0 && seq > lastSeq + 1) lost += seq - lastSeq - 1;
  lastSeq = seq;

  Serial.print(F("[RX] seq=")); Serial.print(seq);
  Serial.print(F("  t_ms="));   Serial.print(ms);
  Serial.print(F("  empfangen=")); Serial.print(received);
  Serial.print(F("  verloren=")); Serial.println(lost);
}

static void processLine(const char* s){
  if (strncmp(s, "BEACON,", 7) == 0) { handleBeacon(s + 7); return; }
  // Alles andere unverändert durchreichen
  Serial.print(F("[RX] ")); Serial.println(s);
}

void setup(){
  Serial.begin(USB_BAUD);
  hc12.begin(HC12_BAUD);
  Serial.println(F("\n[RX] HC-12 Empfaenger bereit, erwartet BEACON,<seq>,<ms>"));
}

void loop(){
  while (hc12.available()){
    const char c = (char)hc12.read();
    if (c == '\n' || c == '\r'){
      if (lineLen > 0){
        lineBuf[lineLen] = '\0';
        processLine(lineBuf);
        lineLen = 0;
      }
    } else if (lineLen < sizeof(lineBuf) - 1){
      lineBuf[lineLen++] = c;
    } else {
      lineLen = 0;   // Überlauf: Zeile verwerfen
    }
  }
}
