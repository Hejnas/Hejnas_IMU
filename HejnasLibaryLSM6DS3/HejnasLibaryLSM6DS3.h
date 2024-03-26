#ifndef HejnasLibaryLSM6DS3_h
#define HejnasLibaryLSM6DS3_h

#include <Arduino.h>

/// REGISTER
#define LSM6DS3_WHO_AM_I 0x0F		///< Chip ID register
#define LSM6DS3_CTRL1_XL 0x10		///< Linear acceleration sensor control register 1 (r/w).
#define LSM6DS3_CTRL2_G 0x11		///< Angular rate sensor control register 2 (r/w).
#define LSM6DS3_CTRL3_C 0x12		///< Control register 3 (r/w).
#define LSM6DS3_CTRL4_C 0x13		///< Control register 4 (r/w).
#define LSM6DS3_CTRL5_C 0x14 		///< Control register 5 (r/w).
#define LSM6DS3_CTRL6_C 0x15		///< Angular rate sensor control register 6 (r/w).
#define LSM6DS3_CTRL7_G 0x16		///< Angular rate sensor control register 7 (r/w).
#define LSM6DS3_CTRL8_XL 0x17		///< Linear acceleration sensor control register 8 (r/w).
#define LSM6DS3_CTRL9_XL 0x18		///< Linear acceleration sensor control register 9 (r/w).
#define LSM6DS3_CTRL10_C 0x19		///< Control register 10 (r/w).
#define LSM6DS3_MASTER_CONFIG 0x1A	///< Master configuration register (r/w).
#define LSM6DS3_WAKE_UP_SRC 0x1B	///< Wake up interrupt source register (r).
#define LSM6DS3_TAP_SRC 0x1C		///< Tap source register (r).
#define LSM6DS3_D6D_SRC 0x1D		///< Portrait, landscape, face-up and face-down source register (r)
#define LSM6DS3_STATUS_REG 0x1E		///< The STATUS_REG register is read by the SPI/I2C interface (r).
#define LSM6DS3_OUT_TEMP_L 0x20     ///< Temperature data output register (r). L and H registers together express a 16-bit word in two’s complement.
#define LSM6DS3_OUT_TEMP_H 0x21		///< Temperature data output register (r). L and H registers together express a 16-bit word in two’s complement.
#define LSM6DS3_OUTX_L_G 0x22       ///< First gyro data register and first gyro X data register L
#define LSM6DS3_OUTX_H_G 0x23		///< First gyro data register and first gyro X data register H
#define LSM6DS3_OUTY_L_G 0x24       ///< First gyro Y data register L
#define LSM6DS3_OUTY_H_G 0x25       ///< First gyro Y data register H
#define LSM6DS3_OUTZ_L_G 0x26       ///< First gyro Z data register L
#define LSM6DS3_OUTZ_H_G 0x27       ///< First gyro Z data register H
#define LSM6DS3_OUTX_L_A 0x28       ///< First accel data register and first accel X data register L
#define LSM6DS3_OUTX_H_A 0x29       ///< First accel data register and first accel X data register H
#define LSM6DS3_OUTY_L_A 0x2A       ///< First accel Y data register L
#define LSM6DS3_OUTY_H_A 0x2B       ///< First accel Y data register H
#define LSM6DS3_OUTZ_L_A 0x2C       ///< First accel Z data register L
#define LSM6DS3_OUTZ_H_A 0x2D       ///< First accel Z data register H

/// DECLARATION
#define LSM6DS3_ID	0x69			///< Chip LSM6DS3 ID store in register 0x0F
#define LSM6DS3_ADDR 0x6A			///< Default i2c address

/** The accelerometer data rate */
typedef enum data_rate {
  LSM6DS3_RATE_SHUTDOWN,
  LSM6DS3_RATE_12_5_HZ,
  LSM6DS3_RATE_26_HZ,
  LSM6DS3_RATE_52_HZ,
  LSM6DS3_RATE_104_HZ,
  LSM6DS3_RATE_208_HZ,
  LSM6DS3_RATE_416_HZ,
  LSM6DS3_RATE_833_HZ,
  LSM6DS3_RATE_1_66K_HZ,
  LSM6DS3_RATE_3_33K_HZ,
  LSM6DS3_RATE_6_66K_HZ,
} lsm6ds3_data_rate_t;

/** The accelerometer data range */
typedef enum accel_range {
  LSM6DS3_ACCEL_RANGE_2_G,
  LSM6DS3_ACCEL_RANGE_16_G,
  LSM6DS3_ACCEL_RANGE_4_G,
  LSM6DS3_ACCEL_RANGE_8_G,
} lsm6ds3_accel_range_t;

/** Anti-aliasing filter bandwidth selection.*/
typedef enum accel_filter_bandwidth {
	LSM6DS3_ACCEL_FILTER_BANDWIDTH_400_HZ,
	LSM6DS3_ACCEL_FILTER_BANDWIDTH_200_HZ,
	LSM6DS3_ACCEL_FILTER_BANDWIDTH_100_HZ,
	LSM6DS3_ACCEL_FILTER_BANDWIDTH_50_HZ,
} lsm6ds3_accel_filter_bandwidth_t;

/** The gyro data range */
typedef enum gyro_range {
  LSM6DS3_GYRO_RANGE_250_DPS,
  LSM6DS3_GYRO_RANGE_500_DPS,
  LSM6DS3_GYRO_RANGE_1000_DPS,
  LSM6DS3_GYRO_RANGE_2000_DPS,
} lsm6ds3_gyro_range_t;

#endif
