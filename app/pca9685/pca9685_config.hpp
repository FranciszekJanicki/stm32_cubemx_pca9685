#ifndef PCA9685_CONFIG_HPP
#define PCA9685_CONFIG_HPP

#include "i2c_device.hpp"
#include "pca9685_registers.hpp"
#include <cstdint>
#include <utility>

#define PACKED __attribute__((__packed__))

namespace PCA9685 {

    using I2CDevice = STM32_Utility::I2CDevice;

    struct SA {
        std::uint8_t reserved : 1 = 0x01;
        std::uint8_t address : 6;
        std::uint8_t : 1;
    } PACKED;

    enum struct CMD : std::uint8_t {
        SOFTWARE_RESET = 0b00000110,
    };

    enum struct RA : std::uint8_t {
        MODE1 = 0x00,
        MODE2 = 0x01,
        SUBADR1 = 0x02,
        SUBADR2 = 0x03,
        SUBADR3 = 0x04,
        ALLCALLADR = 0x05,
        PWM0_ON_L = 0x06,
        PWM0_ON_H = 0x07,
        PWM0_OFF_L = 0x08,
        PWM0_OFF_H = 0x09,
        ALL_PWM_ON_L = 0xFA,
        ALL_PWM_ON_H = 0xFB,
        ALL_PWM_OFF_L = 0xFC,
        ALL_PWM_OFF_H = 0xFD,
        PRE_SCALE = 0xFE,
        TEST_MODE = 0xFF,
    };

    enum struct Channel : std::uint8_t {
        PWM_0,
        PWM_1,
        PWM_2,
        PWM_3,
        PWM_4,
        PWM_5,
        PWM_6,
        PWM_7,
        PWM_8,
        PWM_9,
        PWM_10,
        PWM_11,
        PWM_12,
        PWM_13,
        PWM_14,
        PWM_15,
    };

    enum struct AutoInc : std::uint8_t {
        AUTO_INC_EN = 0x01,
        AUTO_INC_DIS = 0x00,
    };

    enum struct OutputChange : std::uint8_t {
        CHANGE_ON_ACK = 0x01,
        CHANGE_ON_STOP = 0x00,
    };

    enum struct Mode : std::uint8_t {
        NORMAL = 0x00,
        LOW_POWER = 0x01,
    };

    enum struct Drive : std::uint8_t {
        OPEN_DRAIN = 0x00,
        TOTEM_POLE = 0x01,
    };

    struct Config {
        MODE1 mode1 = {};
        MODE2 mode2 = {};
        PRE_SCALE pre_scale = {};
        SUBADR1 subadr1 = {};
        SUBADR2 subadr2 = {};
        SUBADR3 subadr3 = {};
        ALLCALLADR allcalladr = {};
        TEST_MODE test_mode = {};
    };

    constexpr auto MIN_FREQ_HZ = 1526U;
    constexpr auto MAX_FREQ_HZ = 24U;
    constexpr auto MIN_COMPARE = std::uint16_t{0U};
    constexpr auto MAX_COMPARE = std::uint16_t{4096U};
    constexpr auto GENERAL_CALL_ADDRESS = 0x00;

    inline std::uint16_t compare_to_pwm_on(std::uint16_t const compare) noexcept
    {
        return std::clamp(compare, MIN_COMPARE, MAX_COMPARE);
    }

    inline std::uint16_t compare_to_pwm_off(std::uint16_t const compare) noexcept
    {
        return MAX_COMPARE - std::clamp(compare, MIN_COMPARE, MAX_COMPARE);
    }

    inline std::uint8_t channel_to_pwm_on_l_reg_address(Channel const channel) noexcept
    {
        return std::to_underlying(RA::PWM0_ON_L) + 4 * std::to_underlying(channel);
    }

    inline std::uint8_t channel_to_pwm_on_h_reg_address(Channel const channel) noexcept
    {
        return std::to_underlying(RA::PWM0_ON_H) + 4 * std::to_underlying(channel);
    }

    inline std::uint8_t channel_to_pwm_off_l_reg_address(Channel const channel) noexcept
    {
        return std::to_underlying(RA::PWM0_OFF_L) + 4 * std::to_underlying(channel);
    }

    inline std::uint8_t channel_to_pwm_off_h_reg_address(Channel const channel) noexcept
    {
        return std::to_underlying(RA::PWM0_OFF_H) + 4 * std::to_underlying(channel);
    }

}; // namespace PCA9685

#undef PACKED

#endif // PCA9685_CONFIG_HPP