#ifndef PCA9685_REGISTERS_HPP
#define PCA9685_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace PCA9685 {

    struct MODE1 {
        std::uint8_t restart : 1;
        std::uint8_t extclk : 1;
        std::uint8_t sleep : 1;
        std::uint8_t sub1 : 1;
        std::uint8_t sub2 : 1;
        std::uint8_t sub3 : 1;
        std::uint8_t allcall : 1;
    } PACKED;

    struct MODE2 {
        std::uint8_t : 3;
        std::uint8_t invrt : 1;
        std::uint8_t och : 1;
        std::uint8_t outdrv : 1;
        std::uint8_t outne : 2;
    } PACKED;

    struct PWM_ON {
        std::uint8_t pwm_on_l : 8;
        std::uint8_t : 3;
        std::uint8_t pwm_full_on : 1;
        std::uint8_t pwm_on_h : 4;
    } PACKED;

    struct PWM_OFF {
        std::uint8_t pwm_off_l : 8;
        std::uint8_t : 3;
        std::uint8_t pwm_full_off : 1;
        std::uint8_t pwm_off_h : 4;
    } PACKED;

    struct ALL_PWM_ON {
        std::uint8_t all_pwm_on_l : 8;
        std::uint8_t : 3;
        std::uint8_t all_pwm_full_on : 1;
        std::uint8_t all_pwm_on_h : 4;
    } PACKED;

    struct ALL_PWM_OFF {
        std::uint8_t all_pwm_off_l : 8;
        std::uint8_t : 3;
        std::uint8_t all_pwm_full_off : 1;
        std::uint8_t all_pwm_off_h : 4;
    } PACKED;

    struct PRE_SCALE {
        std::uint8_t pre_scale : 8;
    } PACKED;

    struct SUBADR1 {
        std::uint8_t a1 : 7;
        std::uint8_t : 1;
    } PACKED;

    struct SUBADR2 {
        std::uint8_t a2 : 7;
        std::uint8_t : 1;
    } PACKED;

    struct SUBADR3 {
        std::uint8_t a3 : 7;
        std::uint8_t : 1;
    } PACKED;

    struct ALLCALLADR {
        std::uint8_t ac : 7;
        std::uint8_t : 1;
    } PACKED;

    struct TEST_MODE {
        std::uint8_t mode : 8;
    } PACKED;

}; // namespace PCA9685

#undef PACKED

#endif // PCA9685_REGISTERS_HPP