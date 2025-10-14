/*
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include <I2Cdev.h>
#include <MPU6050.h>

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE) && !defined (PARTICLE)
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;



// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

#if defined (PARTICLE)
#define LED_PIN D7 // (Particle is D7)
#else
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
#endif

bool blinkState = false;




void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values
    
    Serial.println("Updating internal sensor offsets...");
    // -76	-2359	1688	0	0	0


    accelgyro.setXGyroOffset(0);// /4
    accelgyro.setYGyroOffset(0);
    accelgyro.setZGyroOffset(0);
    accelgyro.setXAccelOffset(0);
    accelgyro.setYAccelOffset(0);
    accelgyro.setZAccelOffset(0);

    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
  

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

float angleX = 0, angleY = 0, angleZ = 0;

void loop() {

  unsigned long loopStart = micros();
  //int sum = 0;
  //int64_t gx_sum = 0;
  //int64_t gy_sum = 0;
  //int64_t gz_sum = 0;

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


  float gyroX = (gx+21.3)/16.348;  // je nach config
  float gyroY = (gy-4.6)/16.348;
  float gyroZ = (gz-7.1)/16.348;

  float dt = 0.01;

  angleX += gyroX * dt;
  angleY += gyroY * dt;
  angleZ += gyroZ * dt;


  Serial.print(">AngleX:");
  Serial.println(angleX);
  Serial.print(">AngleY:");
  Serial.println(angleY);
  Serial.print(">AngleZ:");
  Serial.println(angleZ);

  while (micros() - loopStart < 10000) {
    // Nichts tun (Busy-Wait)
  }



  //Serial.print("offset gx: ");
  //Serial.println(gx_sum/(double)sum);
  //Serial.print("offset gy: ");
  //Serial.println(gy_sum/(double)sum);
  //Serial.print("offset zx: ");
  //Serial.println(gz_sum/(double)sum);



}

*/

// HC-12 Sender (Nano, AVR)
// Verdrahtung: D11 -> HC-12 RX (über Teiler!), D10 <- HC-12 TX, GND gemeinsam
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial hc12(10, 11); // RX, TX (D10 liest von HC-TX, D11 sendet zu HC-RX)

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
  Serial.println(F("HC-12 Sender startet"));
}

void loop() {
  static unsigned long n = 0;
  hc12.print(F("Hello #"));
  hc12.println(n++);
  delay(1000);
}



/*
// camera test
#include <Arduino.h>

int cameraPin = 7;  // D7 mit Spannungsteiler

void setup() {
  pinMode(cameraPin, OUTPUT);
  digitalWrite(cameraPin, LOW); // Start LOW
}

void loop() {
  // Start Videoaufnahme
  // Für Foto (nur 100 ms Impuls)
  digitalWrite(cameraPin, HIGH);
  delay(1000);
  digitalWrite(cameraPin, LOW);
  delay(1000); 

}

*/
/*
// Test Fan ESC mit Arduino Nano
//pwm 2100
#include <Arduino.h>
#include <Servo.h>

Servo esc;

void setup() {
  esc.attach(9);                 // Pin D5: PWM-Pin für ESC
  esc.writeMicroseconds(1500);  // Neutraler Wert für ESC
  delay(2000);                  // Zeit geben, um zu initialisieren
}

void loop() {

  for (int i = 0; i <= 600; i++)
  {
    esc.writeMicroseconds(1500-i); 
    delay(10);  
  }
  delay(0);
  esc.writeMicroseconds(1500);
  delay(5000);


}
*/
