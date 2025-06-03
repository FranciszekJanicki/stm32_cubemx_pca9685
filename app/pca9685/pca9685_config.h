#ifndef PCA9685_PCA9685_CONFIG_H
#define PCA9685_PCA9685_CONFIG_H

#include <stddef.h>
#include <stdint.h>

#define PCA9685_MIN_FREQ_HZ 1526U
#define PCA9685_MAX_FREQ_HZ 24U
#define PCA9685_MIN_COMPARE 0U
#define PCA9685_MAX_COMPARE ((1U << 12U) - 1U)
#define PCA9685_GENERAL_CALL_ADDRESS 0x00

typedef enum {
    PCA9685_ERR_OK = 0,
    PCA9685_ERR_FAIL = 1 << 0,
    PCA9685_ERR_NULL = 1 << 1,
} pca9685_err_t;

typedef struct {
    uint8_t reserved : 1;
    uint8_t address : 6;
    uint8_t : 1;
} pca9685_dev_address_t;

typedef enum {
    PCA9685_COMMAND_SOFTWARE_RESET = 0b00000110,
} pca9685_command_t;

typedef enum {
    PCA9685_REG_ADDRESS_MODE1 = 0x00,
    PCA9685_REG_ADDRESS_MODE2 = 0x01,
    PCA9685_REG_ADDRESS_SUBADR1 = 0x02,
    PCA9685_REG_ADDRESS_SUBADR2 = 0x03,
    PCA9685_REG_ADDRESS_SUBADR3 = 0x04,
    PCA9685_REG_ADDRESS_ALLCALLADR = 0x05,
    PCA9685_REG_ADDRESS_PWM0_ON_L = 0x06,
    PCA9685_REG_ADDRESS_PWM0_ON_H = 0x07,
    PCA9685_REG_ADDRESS_PWM0_OFF_L = 0x08,
    PCA9685_REG_ADDRESS_PWM0_OFF_H = 0x09,
    PCA9685_REG_ADDRESS_ALL_PWM_ON_L = 0xFA,
    PCA9685_REG_ADDRESS_ALL_PWM_ON_H = 0xFB,
    PCA9685_REG_ADDRESS_ALL_PWM_OFF_L = 0xFC,
    PCA9685_REG_ADDRESS_ALL_PWM_OFF_H = 0xFD,
    PCA9685_REG_ADDRESS_PRE_SCALE = 0xFE,
    PCA9685_REG_ADDRESS_TEST_MODE = 0xFF,
} pca9685_reg_address_t;

typedef enum {
    PCA9685_CHANNEL_PWM_0,
    PCA9685_CHANNEL_PWM_1,
    PCA9685_CHANNEL_PWM_2,
    PCA9685_CHANNEL_PWM_3,
    PCA9685_CHANNEL_PWM_4,
    PCA9685_CHANNEL_PWM_5,
    PCA9685_CHANNEL_PWM_6,
    PCA9685_CHANNEL_PWM_7,
    PCA9685_CHANNEL_PWM_8,
    PCA9685_CHANNEL_PWM_9,
    PCA9685_CHANNEL_PWM_10,
    PCA9685_CHANNEL_PWM_11,
    PCA9685_CHANNEL_PWM_12,
    PCA9685_CHANNEL_PWM_13,
    PCA9685_CHANNEL_PWM_14,
    PCA9685_CHANNEL_PWM_15,
} pca9685_channel_t;

typedef enum {
    PCA9685_AUTO_INC_EN = 0x01,
    PCA9685_AUTO_INC_DIS = 0x00,
} pca9685_auto_inc_t;

typedef enum {
    PCA9685_OUTPUT_CHANGE_ON_ACK = 0x01,
    PCA9685_OUTPUT_CHANGE_ON_STOP = 0x00,
} pca9685_output_change_t;

typedef enum {
    PCA9685_MODE_NORMAL = 0x00,
    PCA9685_MODE_LOW_POWER = 0x01,
} pca9685_mode_t;

typedef enum {
    PCA9685_DRIVE_OPEN_DRAIN = 0x00,
    PCA9685_DRIVE_TOTEM_POLE = 0x01,
} pca9685_drive_t;

typedef struct {
} pca9685_config_t;

typedef struct {
    void* bus_user;
    pca9685_err_t (*bus_init)(void*);
    pca9685_err_t (*bus_deinit)(void*);
    pca9685_err_t (*bus_write)(void*, uint8_t, uint8_t const*, size_t);
    pca9685_err_t (*bus_read)(void*, uint8_t, uint8_t*, size_t);
} pca9685_interface_t;

#endif // PCA9685_PCA9685_CONFIG_H