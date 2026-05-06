/*
 * mpu5060.c
 *
 *  Created on: May 4, 2026
 *      Author: nachiket
 */

#include "mpu6050.h"

#define I2C_TIMEOUT   500UL



mpu_6050_status_t mpu6050_init(I2C_HandleTypeDef *hi2c, uint8_t i2c_dev_addr)
{
	mpu6050_i2c_addr=i2c_dev_addr;

	//1. Read one byte from thes sensors
	uint8_t read_byte=0;
	if(mpu6050_read_byte(hi2c, MPU6050_REG_WHOAMI, &read_byte)!=MPU6050_OK)
	{
		return MPU6050_ERR;
	}
	if(read_byte==0x68 || read_byte==0x70)
	{
		printf("Valid MPU6050 found at %X\n",mpu6050_i2c_addr);
	}else{
		printf("No MPU6050 found at %X\n",mpu6050_i2c_addr);
		return MPU6050_ERR;
	}

	//2. Enabling the accelerometer
	uint8_t pwr_enable=0x00;
	if(mpu6050_write_byte(hi2c, MPU6050_REG_PWRMGMT1, &pwr_enable)!=MPU6050_OK)
	{
		return MPU6050_ERR;
	}

	return MPU6050_OK;
}

mpu_6050_status_t mpu6050_read_byte(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data)
{
	HAL_StatusTypeDef status= \
			HAL_I2C_Mem_Read(hi2c, mpu6050_i2c_addr<<1, reg_addr, 1, data, 1, I2C_TIMEOUT);

	return (status==HAL_OK) ? MPU6050_OK : MPU6050_ERR;
}

mpu_6050_status_t mpu6050_write_byte(I2C_HandleTypeDef *hi2c, uint8_t reg_addr, uint8_t *data)
{
	HAL_StatusTypeDef status= \
			HAL_I2C_Mem_Write(hi2c, mpu6050_i2c_addr<<1, reg_addr, 1, data, 1, I2C_TIMEOUT);

	return (status==HAL_OK) ? MPU6050_OK : MPU6050_ERR;
}

mpu_6050_status_t mpu6050_read(I2C_HandleTypeDef *hi2c, uint8_t reg_base_addr, uint8_t *buffer, uint32_t length)
{
	HAL_StatusTypeDef status= \
			HAL_I2C_Mem_Read(hi2c, mpu6050_i2c_addr<<1, reg_base_addr, 1, buffer, length, I2C_TIMEOUT);

	return (status==HAL_OK) ? MPU6050_OK : MPU6050_ERR;
}


mpu_6050_status_t mpu6050_read_accelerometer_data(I2C_HandleTypeDef *hi2c, uint8_t i2c_dev_addr, acceleratometer_data_t *accel_data)
{
	uint8_t raw_data[6];
	if(mpu6050_read(hi2c, MPU6050_REG_ACCEL_START_ADDRESS, raw_data, sizeof(raw_data))!=MPU6050_OK)
		return MPU6050_ERR;

	accel_data->x=(int16_t)(raw_data[0]<<8 | raw_data[1]);
	accel_data->y=(int16_t)(raw_data[2]<<8 | raw_data[3]);
	accel_data->z=(int16_t)(raw_data[4]<<8 | raw_data[5]);
	return MPU6050_OK;
}

acceleratometer_data_t mpu6050_accelerometer_calibration(const acceleratometer_data_t *error_offfset, acceleratometer_data_t *raw_data)
{
	acceleratometer_data_t accel_calibrated;
	accel_calibrated.x=raw_data->x - error_offfset->x;
	accel_calibrated.y=raw_data->y - error_offfset->y;
	accel_calibrated.z=raw_data->z - error_offfset->z;

	return accel_calibrated;
}

mpu_6050_status_t mpu6050_config_low_pass_filter(I2C_HandleTypeDef *hi2c, mpu6050_dlpf_config_t dlpf)
{
	uint8_t value=0;

	if(mpu6050_read_byte(hi2c, MPU6050_REG_CONFIG, &value)!=MPU6050_OK)
		return MPU6050_ERR;

	value&=~(0x7);
	value|=(uint8_t)dlpf;
	if(mpu6050_write_byte(hi2c, MPU6050_REG_CONFIG, &value)!=MPU6050_OK)
		return MPU6050_ERR;

	return MPU6050_OK;
}
