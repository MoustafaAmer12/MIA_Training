/*
 * File_name: Kalman_Missile.c
 * Author: Moustafa Esam
 * Description: Task 1.3
 * Date_created: 14/8/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MPU_A 0.78
#define BNO_A 0.92
#define SIZE 10
#define g 9.81
#define pi 3.14

static float mpu6050[SIZE] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26}; // 22
static float bno55[SIZE] = {0.0,9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69}; // 8
static int v_in = 30;
static int angle_in = 46*pi/180;


int main()
{
    float avg[SIZE];
    // Calculate the weighted average of measurements
    for(int i = 0; i < SIZE; i++)
    {
        avg[i] = (MPU_A*mpu6050[i] + BNO_A*bno55[i]) / (BNO_A + MPU_A);
    }
    for(int i = 0; i < SIZE;i++)
    {
        printf("%.5f\n", avg[i]);
    }
    return 0;
}
