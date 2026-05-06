/*
 * mpu6050.h
 *
 *  Created on: May 4, 2026
 *      Author: nachiket
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "main.h"

typedef enum{
	MPU6050_OK,
	MPU6050_ERR
}mpu_6050_status_t;

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}acceleratometer_data_t;

typedef enum{
	DLPF_CFG_260HZ = 0,
	DLPF_CFG_184HZ = 1,
	DLPF_CFG_94HZ  = 2,
	DLPF_CFG_44HZ  = 3,
	DLPF_CFG_21HZ  = 4,
	DLPF_CFG_10HZ  = 5,
	DLPF_CFG_5HZ   = 6,

}mpu6050_dlpf_config_t;

static uint8_t mpu6050_i2c_addr;

#define MPU6050_REG_WHOAMI               117
#define MPU6050_REG_PWRMGMT1             107
#define MPU6050_REG_ACCEL_START_ADDRESS   59
#define MPU6050_REG_CONFIG                26


//fucntion defines
mpu_6050_status_t mpu6050_init(I2C_HandleTypeDef *hi2c, uint8_t i2c_dev_addr);
mpu_6050_status_t mpu6050_read_byte(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data);
mpu_6050_status_t mpu6050_write_byte(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data);
mpu_6050_status_t mpu6050_read(I2C_HandleTypeDef *hi2c, uint8_t reg_base_addr, uint8_t *buffer, uint32_t length);
mpu_6050_status_t mpu6050_read_accelerometer_data(I2C_HandleTypeDef *hi2c, uint8_t i2c_dev_addr, acceleratometer_data_t *accel_data);
acceleratometer_data_t mpu6050_accelerometer_calibration(const acceleratometer_data_t *error_offfset, acceleratometer_data_t *raw_data);
mpu_6050_status_t mpu6050_config_low_pass_filter(I2C_HandleTypeDef *hi2c, mpu6050_dlpf_config_t dlpf);

#endif /* INC_MPU6050_H_ */
