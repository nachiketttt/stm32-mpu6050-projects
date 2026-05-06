# STM32F446RE based MPU6050 Projects

STM32F446RE based projects using the MPU6050 IMU sensor, built with HAL drivers and custom firmware. Part of the MCU2 course by FastBit Embedded Brain Academy.


## Projects

| Project | Description | Status |
|---------|-------------|--------|
| [PWM LED Control](./PWM_LED_Control/) | Tilt-based dual channel PWM control using accelerometer + Kalman filter | ✅ Complete |
| [PWM LED Control — FreeRTOS](./PWM_LED_Control_RTOS/) | Same project implemented with FreeRTOS tasks | 🚧 In Progress |


## Hardware

- **MCU:** STM32F446RE (Nucleo-64)
- **Sensor:** MPU6050 (I2C, address `0x68`)
- **Clock:** 25MHz HSE crystal on X3 pad → 120MHz SYSCLK
- **I2C:** PB6 (SCL), PB7 (SDA)
- **PWM:** TIM2 CH1 (PA0), TIM2 CH2 (PA1)


## Tools Used

- STM32CubeIDE
- STM32CubeMonitor
- PulseView (Sigrok) + Logic Analyzer
- STM32 HAL Drivers


## Clock Configuration

```
HSE = 25MHz
PLL: /25 × 240 / 2 = 120MHz SYSCLK
APB1 = 30MHz → TIM2 CLK = 60MHz
Prescaler = 5999 → Timer tick = 10kHz
Period = 19999 → PWM period = 2.0s (0.5Hz)
```

