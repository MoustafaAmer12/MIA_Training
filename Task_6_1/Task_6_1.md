# Task_6_1

# Precise Self-Localizing

---

### Description

The task is about writing an interface for the MPU_6050 sensor, with some featuring functions.

The required output of the task is to write a function that outputs the yaw angle.

### Code

- Macros
    
    PWR_MGMT_1: Register for the power management
    
    IMU_ADDRESS: Register for the MPU communication
    
    GYRO_CONFIG: Register for the gyroscope configurations
    
    ACCEL_CONFIG: Register for the accelerometer configurations
    
    ACCEL_XOUT_H: Register for the higher byte of the X output of the accelerometer
    
    GYRO_ZOUT_H: Register for the higher byte of the Z output of the gyroscope
    
    PI: Mathematical PI
    
    Samples: Samples for the calibration
    
- Functions
    
    MPU_setup:
    
    ```arduino
    // sets the power management bits to the desired ones for communication
    **Wire.write(PWR_MGMT_1);
    Wire.write(0x00**);
    ```
    
    Gyro_config:
    
    ```arduino
    // sets the configuration for the gyroscope output
    **Wire.write(GYRO_CONFIG);
    Wire.write(0x18);** //0b 00011000 ~2000 deg/s
    ```
    
    Accel_config:
    
    ```arduino
    // sets the configuration for the acceleromter output
    **Wire.write(ACCEL_CONFIG);
    Wire.write(0x08);** //0b 00001000 ~8g
    ```
    
    MPU_readAll:
    
    ```arduino
    // reads all teh data that is measured by the sensor and store it in
    // pre-set global variables, that are used later in calibration
    **Wire.requestFrom(IMU_ADDRESS, 14);
    
    while (Wire.available() < 14);
    
    accel_x = Wire.read() << 8 | Wire.read();
    accel_y = Wire.read() << 8 | Wire.read();
    accel_z = Wire.read() << 8 | Wire.read();
    temp = Wire.read() << 8 | Wire.read();
    gyro_x = Wire.read() << 8 | Wire.read();
    gyro_y = Wire.read() << 8 | Wire.read();
    gyro_z = Wire.read() << 8 | Wire.read();**
    ```
    
    MPU_Calib:
    
    ```arduino
    // performs the calibration process, to get the initial
    // error bounds.
    **for (int i = 0; i < Samples; i++)
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
    gyro_offset_z /= Samples;**
    ```
    
    read_yaw:
    
    ```arduino
    // reads the yaw rate of change, and return it after
    // subtracting the error offset.
    **Wire.requestFrom(IMU_ADDRESS, 2);
    
    while (Wire.available() < 2);
    
    yaw_change = Wire.read() << 8 | Wire.read();
    yaw_change -= gyro_offset_z; 
    return yaw_change;**
    ```
    

### Calculation

We calculate the time taken and then, multiply each time interval with the rate of change of the yaw at that instance. Thus, we get an approximate estimate of the yaw angle from the beginning assuming it was 0.

In addition, we divide the measured value with the specified value in the MPU 6050 datasheet, in order to map it to the required interval instead of int16 range.

```arduino
**yaw = yaw + ((read_yaw()/16.4) * elapsed_time)*180/PI;**
```

### Filter

Since the MPU-6050 is occupied with both an accelerometer and a gyroscope and both of them having different range of frequencies to operate on, it would output incomplete data if we use a low-pass or a band pass filter.

Thus, the filter used is known as a complementary filter, which allows both of the sensors to have the desired range of frequencies.

Mainly the complementary filter is used with a parameter α of value 0.98 as most the weights lay on the gyroscope measurement.

******************Equation******************

> *angle = (1 - α) * (angle + gyroscope * dt) + α * accelerometer*
>