#include <Wire.h>

#define PWR_MGMT_1 0x6B
#define IMU_ADDRESS 0x68
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_ZOUT_H 0x47

#define PI 3.1415926
#define Samples 5000

int16_t gyro_offset_x = 0, gyro_offset_y = 0, gyro_offset_z= 0;
int16_t accel_offset_x = 0, accel_offset_y = 0, accel_offset_z = 0;

int16_t gyro_x = 0, gyro_y = 0, gyro_z = 0;
int16_t accel_x = 0, accel_y = 0, accel_z = 0;
int16_t temp = 0;

int16_t yaw = 0;
double elapsed_time = 0, previous_time = 0, current_time = 0;

// MPU6050 Setup & Config Functions
void MPU_setup()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Gyro_config()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x18); //0b 00011000 ~2000 deg/s
  Wire.endTransmission();
}

void Accel_config()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0x08); //0b 00001000 ~8g
  Wire.endTransmission();
}

// Calibration Functions in order to get the best estimated outputs
void MPU_readAll()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS, 14);

  while (Wire.available() < 14);

  accel_x = Wire.read() << 8 | Wire.read();
  accel_y = Wire.read() << 8 | Wire.read();
  accel_z = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read();
  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
}

void MPU_Calib()
{
  for (int i = 0; i < Samples; i++)
  {
    MPU_readAll();
    accel_offset_x += accel_x;
    accel_offset_y += accel_y;
    accel_offset_z += accel_z;
    gyro_offset_x += gyro_x;
    gyro_offset_y += gyro_y;
    gyro_offset_z += gyro_z;
  }

  accel_offset_x /= Samples;
  accel_offset_y /= Samples;
  accel_offset_z /= Samples;
  gyro_offset_x /= Samples;
  gyro_offset_y /= Samples;
  gyro_offset_z /= Samples;

}

// Function to read the yaw rate of change and calculate it.
int16_t read_yaw()
{
  int16_t yaw_change = 0;

  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_ZOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS, 2);

  while (Wire.available() < 2);

  yaw_change = Wire.read() << 8 | Wire.read();

  // we subtract the offset from each measurement for Calibration.
  yaw_change -= gyro_offset_z; 
  return yaw_change;
}

void setup(){
  Serial.begin(19200);
  Wire.begin();

  MPU_setup();
  Gyro_config();
  Accel_config();
  MPU_Calib();
  delay(30);
}

void loop() {
  previous_time = current_time;
  current_time = millis();
  elapsed_time = (current_time - previous_time)/1000;
  // 16.4 stated from the datasheet in order to map it,
  // elapsed time to get the average estimate of the angle,
  // then the angle is converted from radian to degrees.
  yaw = yaw + ((read_yaw()/16.4) * elapsed_time)*180/PI;
  Serial.print("Yaw Angle: ");
  Serial.println(yaw);
}
