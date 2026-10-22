# kartonaut-ground – Bodenstation für Kartonaut

Arduino Nano mit HC-12-Funkmodul (433 MHz), das Gegenstück zum Flugcomputer der
TVC-Modellrakete [kartonaut](https://github.com/Jan-Philipp-Munsch/kartonaut).
Der Empfänger nimmt die Telemetrie-Zeilen des Flugcomputers entgegen und gibt sie auf
der USB-Konsole aus. Heute ist das der Beacon-Test (`BEACON,<seq>,<millis>`, gesendet
vom Sketch `radio_beacon` der Firmware) samt Zählung verlorener Pakete. Ein echtes
Telemetrieprotokoll kommt mit dem Flugzustandsautomaten der Firmware.

```
Nano D10  <-  HC-12 TXD
Nano D11  ->  HC-12 RXD   (über Spannungsteiler auf 3,3 V)
USB       ->  Monitor, 9600 Bd
```

## Bauen und flashen

```bash
pio run                      # HC-12-Empfänger bauen
pio run -t upload            # flashen (Nano mit altem Bootloader, 57600 Bd)
pio device monitor           # 9600 Bd
pio run -e fan_esc -t upload # einen Test-Sketch flashen
```

## Test-Sketches (`examples/`)

Jeder Ordner ist eine PlatformIO-Umgebung (`build_src_filter` in `platformio.ini`).

| Umgebung | Zweck |
|---|---|
| `mpu6050_gyro` | Gyro-Integration zu Winkeln, Teleplot-Ausgabe. Vorversuch vor der ICM-20948 im Flugcomputer. |
| `camera_trigger` | Pulst D7 für den Auslöser der Bordkamera (1 s Video, 100 ms Foto). |
| `fan_esc` | Fährt einen bidirektionalen ESC an D9 von Neutral aus langsam hoch. Versuch für den Rollantrieb. |

## Lizenz

[MIT](LICENSE).
