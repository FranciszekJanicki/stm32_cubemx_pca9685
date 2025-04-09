#include "pca9685.hpp"

namespace PCA9685 {

    PCA9685::PCA9685(I2CDevice&& i2c_device, Config const& config) noexcept
    {
        this->initialize(config);
    }

    PCA9685::~PCA9685() noexcept
    {
        this->deinitialize();
    }

    void PCA9685::set_channel_min_compare(this PCA9685 const& self, Channel const channel) noexcept
    {
        self.set_pwm_full_off(channel, true);
        self.set_pwm_full_on(channel, false);
    }

    void PCA9685::set_channel_max_compare(this PCA9685 const& self, Channel const channel) noexcept
    {
        self.set_pwm_full_off(channel, false);
        self.set_pwm_full_on(channel, true);
    }

    void PCA9685::set_channel_compare(this PCA9685 const& self,
                                      Channel const channel,
                                      std::uint16_t const compare) noexcept
    {
        self.set_pwm_on(channel, compare_to_pwm_on(compare));
        self.set_pwm_off(channel, compare_to_pwm_off(compare));
    }

    void PCA9685::set_channels_min_compare(this PCA9685 const& self) noexcept
    {
        self.set_all_pwm_full_off(true);
        self.set_all_pwm_full_on(false);
    }

    void PCA9685::set_channels_max_compare(this PCA9685 const& self) noexcept
    {
        self.set_all_pwm_full_off(false);
        self.set_all_pwm_full_on(true);
    }

    void PCA9685::set_channels_compare(this PCA9685 const& self,
                                       std::uint16_t const compare) noexcept
    {
        self.set_all_pwm_on(compare_to_pwm_on(compare));
        self.set_all_pwm_off(compare_to_pwm_off(compare));
    }

    void PCA9685::send_software_reset_command(this PCA9685 const& self) noexcept
    {
        self.write_byte(std::to_underlying(CMD::SOFTWARE_RESET), 0x00);
    }

    std::uint8_t PCA9685::read_byte(this PCA9685 const& self, std::uint8_t const address) noexcept
    {
        return self.i2c_device_.read_byte(address);
    }

    void PCA9685::write_byte(this PCA9685 const& self,
                             std::uint8_t const address,
                             std::uint8_t const data) noexcept
    {
        self.i2c_device_.write_byte(address, data);
    }

    void PCA9685::initialize(this PCA9685& self, Config const& config) noexcept
    {
        if (1) {
            self.set_mode1_register(config.mode1);
            self.initialized_ = true;
        }
    }

    void PCA9685::deinitialize(this PCA9685& self) noexcept
    {
        if (1) {
            self.initialized_ = false;
        }
    }

    void PCA9685::set_pwm_on(this PCA9685 const& self,
                             Channel const channel,
                             std::uint16_t const pwm_on) noexcept
    {
        auto pwm = self.get_pwm_on_registers(channel);
        pwm.pwm_on_h = pwm_on >> 8;
        pwm.pwm_on_l = pwm_on;
        self.set_pwm_on_registers(channel, pwm);
    }

    void PCA9685::set_pwm_off(this PCA9685 const& self,
                              Channel const channel,
                              std::uint16_t const pwm_off) noexcept
    {
        auto pwm = self.get_pwm_off_registers(channel);
        pwm.pwm_off_h = pwm_off >> 8;
        pwm.pwm_off_l = pwm_off;
        self.set_pwm_off_registers(channel, pwm);
    }

    void PCA9685::set_pwm_full_off(this PCA9685 const& self,
                                   Channel const channel,
                                   bool const pwm_full_off) noexcept
    {
        auto pwm = self.get_pwm_off_registers(channel);
        pwm.pwm_full_off = pwm_full_off;
        self.set_pwm_off_registers(channel, pwm);
    }

    void PCA9685::set_pwm_full_on(this PCA9685 const& self,
                                  Channel const channel,
                                  bool const pwm_full_on) noexcept
    {
        auto pwm = self.get_pwm_on_registers(channel);
        pwm.pwm_full_on = pwm_full_on;
        self.set_pwm_on_registers(channel, pwm);
    }

    void PCA9685::set_all_pwm_full_off(this PCA9685 const& self,
                                       bool const all_pwm_full_off) noexcept
    {
        auto pwm = self.get_all_pwm_off_registers();
        pwm.all_pwm_full_off = all_pwm_full_off;
        self.set_all_pwm_off_registers(pwm);
    }

    void PCA9685::set_all_pwm_full_on(this PCA9685 const& self, bool const all_pwm_full_on) noexcept
    {
        auto pwm = self.get_all_pwm_on_registers();
        pwm.all_pwm_full_on = all_pwm_full_on;
        self.set_all_pwm_on_registers(pwm);
    }

    void PCA9685::set_all_pwm_off(this PCA9685 const& self,
                                  std::uint16_t const all_pwm_off) noexcept
    {
        auto pwm = self.get_all_pwm_off_registers();
        pwm.all_pwm_off_h = all_pwm_off >> 8;
        pwm.all_pwm_off_l = all_pwm_off;
        self.set_all_pwm_off_registers(pwm);
    }

    void PCA9685::set_all_pwm_on(this PCA9685 const& self, std::uint16_t const all_pwm_on) noexcept
    {
        auto pwm = self.get_all_pwm_on_registers();
        pwm.all_pwm_on_h = all_pwm_on >> 8;
        pwm.all_pwm_on_l = all_pwm_on;
        self.set_all_pwm_on_registers(pwm);
    }

    MODE1 PCA9685::get_mode1_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<MODE1>(self.read_byte(std::to_underlying(RA::MODE1)));
    }

    void PCA9685::set_mode1_register(this PCA9685 const& self, MODE1 const mode1) noexcept
    {
        self.write_byte(std::to_underlying(RA::MODE1), std::bit_cast<std::uint8_t>(mode1));
    }

    MODE2 PCA9685::get_mode2_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<MODE2>(self.read_byte(std::to_underlying(RA::MODE2)));
    }

    void PCA9685::set_mode2_register(this PCA9685 const& self, MODE2 const mode2) noexcept
    {
        self.write_byte(std::to_underlying(RA::MODE2), std::bit_cast<std::uint8_t>(mode2));
    }

    SUBADR1 PCA9685::get_subadr1_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<SUBADR1>(self.read_byte(std::to_underlying(RA::SUBADR1)));
    }

    void PCA9685::set_subadr1_register(this PCA9685 const& self, SUBADR1 const subadr1) noexcept
    {
        self.write_byte(std::to_underlying(RA::SUBADR1), std::bit_cast<std::uint8_t>(subadr1));
    }

    SUBADR2 PCA9685::get_subadr2_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<SUBADR2>(self.read_byte(std::to_underlying(RA::SUBADR2)));
    }

    void PCA9685::set_subadr2_register(this PCA9685 const& self, SUBADR2 const subadr2) noexcept
    {
        self.write_byte(std::to_underlying(RA::SUBADR2), std::bit_cast<std::uint8_t>(subadr2));
    }

    SUBADR3 PCA9685::get_subadr3_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<SUBADR3>(self.read_byte(std::to_underlying(RA::SUBADR3)));
    }

    void PCA9685::set_subadr3_register(this PCA9685 const& self, SUBADR3 const subadr3) noexcept
    {
        self.write_byte(std::to_underlying(RA::SUBADR3), std::bit_cast<std::uint8_t>(subadr3));
    }

    ALLCALLADR PCA9685::get_allcalladr_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<ALLCALLADR>(self.read_byte(std::to_underlying(RA::ALLCALLADR)));
    }

    void PCA9685::set_allcalladr_register(this PCA9685 const& self,
                                          ALLCALLADR const allcalladr) noexcept
    {
        self.write_byte(std::to_underlying(RA::ALLCALLADR),
                        std::bit_cast<std::uint8_t>(allcalladr));
    }

    PWM_ON PCA9685::get_pwm_on_registers(this PCA9685 const& self, Channel const channel) noexcept
    {
        return std::bit_cast<PWM_ON>(
            self.read_bytes<sizeof(PWM_ON)>(channel_to_pwm_on_l_reg_address(channel)));
    }

    void PCA9685::set_pwm_on_registers(this PCA9685 const& self,
                                       Channel const channel,
                                       PWM_ON const pwm_on) noexcept
    {
        self.write_bytes(channel_to_pwm_on_l_reg_address(channel),
                         std::bit_cast<std::array<std::uint8_t, sizeof(PWM_ON)>>(pwm_on));
    }

    PWM_OFF PCA9685::get_pwm_off_registers(this PCA9685 const& self, Channel const channel) noexcept
    {
        return std::bit_cast<PWM_OFF>(
            self.read_bytes<sizeof(PWM_OFF)>(channel_to_pwm_off_l_reg_address(channel)));
    }

    void PCA9685::set_pwm_off_registers(this PCA9685 const& self,
                                        Channel const channel,
                                        PWM_OFF const pwm_off) noexcept
    {
        self.write_bytes(channel_to_pwm_off_l_reg_address(channel),
                         std::bit_cast<std::array<std::uint8_t, sizeof(PWM_OFF)>>(pwm_off));
    }

    ALL_PWM_ON PCA9685::get_all_pwm_on_registers(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<ALL_PWM_ON>(
            self.read_bytes<sizeof(ALL_PWM_ON)>(std::to_underlying(RA::ALL_PWM_ON_L)));
    }

    void PCA9685::set_all_pwm_on_registers(this PCA9685 const& self,
                                           ALL_PWM_ON const all_pwm_on) noexcept
    {
        self.write_bytes(std::to_underlying(RA::ALL_PWM_ON_L),
                         std::bit_cast<std::array<std::uint8_t, sizeof(ALL_PWM_ON)>>(all_pwm_on));
    }

    ALL_PWM_OFF PCA9685::get_all_pwm_off_registers(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<ALL_PWM_OFF>(
            self.read_bytes<sizeof(ALL_PWM_OFF)>(std::to_underlying(RA::ALL_PWM_OFF_L)));
    }

    void PCA9685::set_all_pwm_off_registers(this PCA9685 const& self,
                                            ALL_PWM_OFF const all_pwm_off) noexcept
    {
        self.write_bytes(std::to_underlying(RA::ALL_PWM_OFF_L),
                         std::bit_cast<std::array<std::uint8_t, sizeof(ALL_PWM_OFF)>>(all_pwm_off));
    }

    PRE_SCALE PCA9685::get_pre_scale_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<PRE_SCALE>(self.read_byte(std::to_underlying(RA::PRE_SCALE)));
    }

    void PCA9685::set_pre_scale_register(this PCA9685 const& self,
                                         PRE_SCALE const pre_scale) noexcept
    {
        self.write_byte(std::to_underlying(RA::PRE_SCALE), std::bit_cast<std::uint8_t>(pre_scale));
    }

    TEST_MODE PCA9685::get_test_mode_register(this PCA9685 const& self) noexcept
    {
        return std::bit_cast<TEST_MODE>(self.read_byte(std::to_underlying(RA::TEST_MODE)));
    }

    void PCA9685::set_test_mode_register(this PCA9685 const& self,
                                         TEST_MODE const test_mode) noexcept
    {
        self.write_byte(std::to_underlying(RA::TEST_MODE), std::bit_cast<std::uint8_t>(test_mode));
    }

}; // namespace PCA9685