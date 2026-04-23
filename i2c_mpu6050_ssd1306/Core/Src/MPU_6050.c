/*
 * MPU_6050.c
 *
 *  Created on: Apr 16, 2026
 *      Author: Tiago_gran
 */

#include "MPU_6050.h"
#include <math.h>

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;
float Ax, Ay, Az;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;
float Gx, Gy, Gz;

float Roll = 0, Pitch = 0;

void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t check;
    uint8_t data;

    // Read WHO_AM_I register to verify communication
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, HAL_MAX_DELAY);

    if (check == 0x68) // Expected device ID
    {
    	// Wake up the sensor (exit sleep mode)
        data = 0;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, HAL_MAX_DELAY);

        // Set sample rate divider
        data = 0x07;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, HAL_MAX_DELAY);

        // Configure accelerometer (±2g full scale)
        data = 0x00;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, HAL_MAX_DELAY);

        // Configure gyroscope (±250°/s full scale)
        data = 0x00;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, HAL_MAX_DELAY);
    }
}

void MPU6050_Read_Accel (I2C_HandleTypeDef *hi2c)
{
    uint8_t Rec_Data[6];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

    // Combine high and low bytes
    Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    // Convert to g (±2g → 16384 LSB/g)
    Ax = (float)Accel_X_RAW / 16384.0;
    Ay = (float)Accel_Y_RAW / 16384.0;
    Az = (float)Accel_Z_RAW / 16384.0;
}

void MPU6050_Read_Ang_Vel (I2C_HandleTypeDef *hi2c)
{
    uint8_t Rec_Data[6];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

    // Combine high and low bytes
    Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    // Convert to °/s (±250°/s → 131 LSB/(°/s))
    Gx = (float)Gyro_X_RAW / 131.0;
    Gy = (float)Gyro_Y_RAW / 131.0;
    Gz = (float)Gyro_Z_RAW / 131.0;
}

void MPU6050_Get_Angles (void)
{
	// Time step calculation (in seconds)
	uint32_t now = HAL_GetTick();
	static uint32_t last = 0;

	float dt = (now - last) / 1000.0f;
	last = now;

	// Complementary filter coefficient
	float alpha = 0.9f;

	// Angles from accelerometer (in degrees)
    float roll_acc  = atan2(Ay, Az) * 57.2957795;
    float pitch_acc = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 57.2957795;

    // Complementary filter fusion
    Roll  = alpha * (Roll  + Gx * dt) + (1 - alpha) * roll_acc;
    Pitch = alpha * (Pitch + Gy * dt) + (1 - alpha) * pitch_acc;
}
