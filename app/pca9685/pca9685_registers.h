#ifndef PCA9685_PCA9685_REGISTERS_H
#define PCA9685_PCA9685_REGISTERS_H

#include <stdint.h>

typedef struct {
    uint8_t restart : 1;
    uint8_t extclk : 1;
    uint8_t ai : 1;
    uint8_t sleep : 1;
    uint8_t sub1 : 1;
    uint8_t sub2 : 1;
    uint8_t sub3 : 1;
    uint8_t allcall : 1;
} pca9685_mode1_reg_t;

typedef struct {
    uint8_t invrt : 1;
    uint8_t och : 1;
    uint8_t outdrv : 1;
    uint8_t outne : 2;
} pca9685_mode2_reg_t;

typedef struct {
    uint16_t pwm_on : 12;
    uint8_t pwm_full_on : 1;
} pca9685_pwm_on_reg_t;

typedef struct {
    uint16_t pwm_off : 12;
    uint8_t pwm_full_off : 1;
} pca9685_pwm_off_reg_t;

typedef struct {
    uint16_t all_pwm_on : 12;
    uint8_t all_pwm_full_on : 1;
} pca9685_all_pwm_on_reg_t;

typedef struct {
    uint16_t all_pwm_off : 12;
    uint8_t all_pwm_full_off : 1;
} pca9685_all_pwm_off_reg_t;

typedef struct {
    uint8_t pre_scale : 8;
} pca9685_pre_scale_reg_t;

typedef struct {
    uint8_t a1 : 7;
} pca9685_subadr1_reg_t;

typedef struct {
    uint8_t a2 : 7;
} pca9685_subadr2_reg_t;

typedef struct {
    uint8_t a3 : 7;
} pca9685_subadr3_reg_t;

typedef struct {
    uint8_t ac : 7;
} pca9685_allcalladr_reg_t;

typedef struct {
    uint8_t mode : 8;
} pca9685_test_mode_reg_t;

#endif // PCA9685_PCA9685_REGISTERS_H