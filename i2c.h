/*
 * AAC Clyde Space coding test
 * Candidate: Akshay G Jadhav
 * Date:14/04/2024
 */
#ifndef I2C_HEADER_H
#define I2C_HEADER_H

#include <stdint.h>
 /*
  * Defines
  * Included all registers just for completion (might not need all of them)
  *
  */
#define INTERRUPT_ENABLE        (1U<<0)            
#define INTERRUPT_DISABLE       ~(INTERRUPT_ENABLE)

#define OFFSET_X_REG_L_M        0x05
#define OFFSET_X_REG_H_M        0x06
#define OFFSET_Y_REG_L_M        0x07
#define OFFSET_Y_REG_H_M        0x08
#define OFFSET_Z_REG_L_M        0x09
#define OFFSET_Z_REG_H_M        0x0A

#define WHO_AM_I                0x0F

#define CTRL_REG1               0x20                // 3. Data output rate
#define CTRL_REG2               0x21                // 1. Full Scale config
#define CTRL_REG3               0x22
#define CTRL_REG4               0x23
#define CTRL_REG5               0x24

#define STATUS_REG              0x27                // 4. Axis status

#define OUT_X_L                 0x28                // 4. Axis data X-L
#define OUT_X_H                 0x29                // 4. Axis data X-H
#define OUT_Y_L                 0x2A                // 4. Axis data Y-L
#define OUT_Y_H                 0x2B                // 4. Axis data Y-H
#define OUT_Z_L                 0x2C                // 4. Axis data Z-L
#define OUT_Z_H                 0x2D                // 4. Axis data Z-H

#define TEMP_OUT_L              0x2E
#define TEMP_OUT_H              0x2F

#define INT_CFG                 0x30                // 2. Interrupt Enable pin
#define INT_SRC                 0x31
#define INT_THS_L               0x32
#define INT_THS_H               0x33

  /*
  * Full Scale configurations
  */
#define FS_CONFIG_4GAUSS        0x00
#define FS_CONFIG_8GAUSS        0x20
#define FS_CONFIG_12GAUSS       0x40
#define FS_CONFIG_16GAUSS       0x60

  /*
  * Output Data Rates
  */
#define ODR_0_625HZ             0x00
#define ODR_1_25HZ              0x04
#define ODR_2_5HZ               0x08
#define ODR_5HZ                 0x0C
#define ODR_10HZ                0x10
#define ODR_20HZ                0x14
#define ODR_40HZ                0x18
#define ODR_80HZ                0x1C
#define FODR_155HZ              0x10
#define FODR_300HZ              0x14
#define FODR_560HZ              0x18
#define FODR_1000HZ             0x1C

typedef enum {
    STATUS_OK,
    STATUS_ERROR
} status_t;

status_t i2c_read(uint8_t bus_address, uint8_t register_address, uint16_t length, uint8_t* buffer);
status_t i2c_write(uint8_t bus_address, uint8_t register_address, uint16_t length, uint8_t* buffer);
status_t get_full_scale_config(uint8_t bus_address, uint8_t* full_scale_selection);
status_t interrupt_mode(uint8_t bus_address, uint8_t intrupt_pin_status);
status_t set_data_output_rate(uint8_t bus_address, uint8_t data_rate);
status_t get_data_output_rate(uint8_t bus_address, uint8_t* data_rate);
status_t read_axis_data(uint8_t bus_address, char axis, int8_t* output);

#endif
