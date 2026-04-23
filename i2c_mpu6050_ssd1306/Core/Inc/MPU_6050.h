/*
 * MPU_6050.h
 *
 *  Created on: Apr 16, 2026
 *      Author: Tiago_gran
 */

#ifndef INC_MPU_6050_H_
#define INC_MPU_6050_H_

#include "stm32f4xx_hal.h"

#define MPU6050_ADDR       (0x68 << 1) 	//MPU6050 default address (0x68) shifted left (HAL expects the address in 8-bit format)
#define SMPLRT_DIV_REG 	   0x19			// Sample rate divider
#define GYRO_CONFIG_REG    0x1B  		// Gyroscope configuration
#define ACCEL_CONFIG_REG   0x1C  		// Accelerometer configuration
#define ACCEL_XOUT_H_REG   0x3B  		// Accelerometer data start (6 bytes)
#define GYRO_XOUT_H_REG    0x43  		// Gyroscope data start (6 bytes)
#define PWR_MGMT_1_REG     0x6B  		// Power management (sleep/wake control)
#define WHO_AM_I_REG       0x75  		// Device ID register (expected value: 0x68)


//16-bit values directly read from the sensor registers
extern int16_t Accel_X_RAW;
extern int16_t Accel_Y_RAW;
extern int16_t Accel_Z_RAW;

extern int16_t Gyro_X_RAW;
extern int16_t Gyro_Y_RAW;
extern int16_t Gyro_Z_RAW;

//Converted values to acceleration and angular velocities
extern float Ax, Ay, Az; 	// unit: g (FS = ±2g)
extern float Gx, Gy, Gz; 	// unit: °/s (FS = ±250°/s)

extern float Roll, Pitch; 	// Computed from gyro and acceleration data (in degrees)

void MPU6050_Init (I2C_HandleTypeDef *hi2c);          	// Initializes the MPU6050 (wake-up and basic configuration)
void MPU6050_Read_Accel (I2C_HandleTypeDef *hi2c);		// Reads accelerometer data and converts it to g
void MPU6050_Read_Ang_Vel (I2C_HandleTypeDef *hi2c);	// Reads gyroscope data and converts it to °/s
void MPU6050_Get_Angles (void);							// Computes Roll and Pitch angles



#endif /* INC_MPU_6050_H_ */
