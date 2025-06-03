#ifndef PCA9685_PCA9685_UTILITY_H
#define PCA9685_PCA9685_UTILITY_H

#include "pca9685_config.h"
#include <stdint.h>

inline uint16_t pca9685_compare_to_pwm_on(uint16_t compare)
{
    if (compare > PCA9685_MAX_COMPARE) {
        compare = PCA9685_MAX_COMPARE;
    } else if (compare < PCA9685_MIN_COMPARE) {
        compare = PCA9685_MIN_COMPARE;
    }

    return compare;
}

inline uint16_t pca9685_compare_to_pwm_off(uint16_t compare)
{
    return PCA9685_MAX_COMPARE - pca9685_compare_to_pwm_on(compare);
}

inline uint8_t pca9685_channel_to_pwm_on_reg_address(pca9685_channel_t channel)
{
    return PCA9685_REG_ADDRESS_PWM0_ON_L + 4 * channel;
}

inline uint8_t pca9865_channel_to_pwm_off_reg_address(pca9685_channel_t channel)
{
    return PCA9685_REG_ADDRESS_PWM0_OFF_L + 4 * channel;
}

#endif // PCA9685_PCA9685_UTILITY_H