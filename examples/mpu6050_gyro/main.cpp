// MPU6050-Gyro-Test: integriert die Drehraten zu Winkeln und gibt sie als
// Teleplot-Zeilen (>AngleX:...) auf USB-Serial aus. Diente zum Ausprobieren der
// Gyro-Integration, bevor die ICM-20948 im Flugcomputer zum Einsatz kam.
//
//   pio run -e mpu6050_gyro -t upload
#include <Arduino.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 imu;                         // AD0 low -> 0x68

constexpr float GYRO_LSB_PER_DPS = 16.348f;   // je nach Full-Scale-Range
constexpr float BIAS_X = +21.3f, BIAS_Y = -4.6f, BIAS_Z = -7.1f;   // LSB, am Tisch bestimmt
constexpr uint32_t LOOP_US = 10000;           // 100 Hz

static float angleX = 0, angleY = 0, angleZ = 0;

void setup(){
  Wire.begin();
  Serial.begin(115200);
  imu.initialize();
  Serial.println(imu.testConnection() ? F("MPU6050 ok") : F("MPU6050 nicht gefunden"));
}

void loop(){
  const uint32_t t0 = micros();

  int16_t ax, ay, az, gx, gy, gz;
  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  const float dt = LOOP_US * 1e-6f;
  angleX += (gx + BIAS_X) / GYRO_LSB_PER_DPS * dt;
  angleY += (gy + BIAS_Y) / GYRO_LSB_PER_DPS * dt;
  angleZ += (gz + BIAS_Z) / GYRO_LSB_PER_DPS * dt;

  Serial.print(F(">AngleX:")); Serial.println(angleX);
  Serial.print(F(">AngleY:")); Serial.println(angleY);
  Serial.print(F(">AngleZ:")); Serial.println(angleZ);

  while (micros() - t0 < LOOP_US) {}
}
