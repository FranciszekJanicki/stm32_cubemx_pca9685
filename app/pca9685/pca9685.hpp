#ifndef PCA9685_HPP
#define PCA9685_HPP

#include "pca9685_config.hpp"

namespace PCA9685 {

    struct PCA9685 {
    public:
        PCA9685() noexcept = default;
        PCA9685(I2CDevice&& i2c_device, Config const& config) noexcept;

        PCA9685(PCA9685 const& other) = delete;
        PCA9685(PCA9685&& other) noexcept = default;

        PCA9685& operator=(PCA9685 const& other) = delete;
        PCA9685& operator=(PCA9685&& other) noexcept = default;

        ~PCA9685() noexcept;

        void set_channel_min_compare(this PCA9685 const& self, Channel const channel) noexcept;
        void set_channel_max_compare(this PCA9685 const& self, Channel const channel) noexcept;
        void set_channel_compare(this PCA9685 const& self,
                                 Channel const channel,
                                 std::uint16_t const compare) noexcept;

        void set_channels_min_compare(this PCA9685 const& self) noexcept;
        void set_channels_max_compare(this PCA9685 const& self) noexcept;
        void set_channels_compare(this PCA9685 const& self, std::uint16_t const compare) noexcept;

        void send_software_reset_command(this PCA9685 const& self) noexcept;

        void set_pwm_on(this PCA9685 const& self,
                        Channel const channel,
                        std::uint16_t const pwm_on) noexcept;
        void set_pwm_off(this PCA9685 const& self,
                         Channel const channel,
                         std::uint16_t const pwm_off) noexcept;

        void set_pwm_full_off(this PCA9685 const& self,
                              Channel const channel,
                              bool const pwm_full_off) noexcept;
        void set_pwm_full_on(this PCA9685 const& self,
                             Channel const channel,
                             bool const pwm_full_on) noexcept;

        void set_all_pwm_full_off(this PCA9685 const& self, bool const all_pwm_full_off) noexcept;
        void set_all_pwm_full_on(this PCA9685 const& self, bool const all_pwm_full_on) noexcept;

        void set_all_pwm_off(this PCA9685 const& self, std::uint16_t const all_pwm_off) noexcept;
        void set_all_pwm_on(this PCA9685 const& self, std::uint16_t const all_pwm_on) noexcept;

        void initialize(this PCA9685& self, Config const& config) noexcept;
        void deinitialize(this PCA9685& self) noexcept;

        MODE1 get_mode1_register(this PCA9685 const& self) noexcept;
        void set_mode1_register(this PCA9685 const& self, MODE1 const mode1) noexcept;

        MODE2 get_mode2_register(this PCA9685 const& self) noexcept;
        void set_mode2_register(this PCA9685 const& self, MODE2 const mode2) noexcept;

        SUBADR1 get_subadr1_register(this PCA9685 const& self) noexcept;
        void set_subadr1_register(this PCA9685 const& self, SUBADR1 const subadr1) noexcept;

        SUBADR2 get_subadr2_register(this PCA9685 const& self) noexcept;
        void set_subadr2_register(this PCA9685 const& self, SUBADR2 const subadr2) noexcept;

        SUBADR3 get_subadr3_register(this PCA9685 const& self) noexcept;
        void set_subadr3_register(this PCA9685 const& self, SUBADR3 const subadr3) noexcept;

        ALLCALLADR get_allcalladr_register(this PCA9685 const& self) noexcept;
        void set_allcalladr_register(this PCA9685 const& self,
                                     ALLCALLADR const allcalladr) noexcept;

        PWM_ON get_pwm_on_registers(this PCA9685 const& self, Channel const channel) noexcept;
        void set_pwm_on_registers(this PCA9685 const& self,
                                  Channel const channel,
                                  PWM_ON const pwm_on) noexcept;

        PWM_OFF get_pwm_off_registers(this PCA9685 const& self, Channel const channel) noexcept;
        void set_pwm_off_registers(this PCA9685 const& self,
                                   Channel const channel,
                                   PWM_OFF const pwm_off) noexcept;

        ALL_PWM_ON get_all_pwm_on_registers(this PCA9685 const& self) noexcept;
        void set_all_pwm_on_registers(this PCA9685 const& self,
                                      ALL_PWM_ON const all_pwm_on) noexcept;

        ALL_PWM_OFF get_all_pwm_off_registers(this PCA9685 const& self) noexcept;
        void set_all_pwm_off_registers(this PCA9685 const& self,
                                       ALL_PWM_OFF const all_pwm_off) noexcept;

        PRE_SCALE get_pre_scale_register(this PCA9685 const& self) noexcept;
        void set_pre_scale_register(this PCA9685 const& self, PRE_SCALE const pre_scale) noexcept;

        TEST_MODE get_test_mode_register(this PCA9685 const& self) noexcept;
        void set_test_mode_register(this PCA9685 const& self, TEST_MODE const test_mode) noexcept;

    private:
        std::uint8_t read_byte(this PCA9685 const& self, std::uint8_t const address) noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(this PCA9685 const& self,
                                                  std::uint8_t const address) noexcept;

        void write_byte(this PCA9685 const& self,
                        std::uint8_t const address,
                        std::uint8_t const data) noexcept;

        template <std::size_t SIZE>
        void write_bytes(this PCA9685 const& self,
                         std::uint8_t const address,
                         std::array<std::uint8_t, SIZE> const& data) noexcept;

        bool initialized_ = false;

        I2CDevice i2c_device_ = {};
    };

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> PCA9685::read_bytes(this PCA9685 const& self,
                                                       std::uint8_t const address) noexcept
    {
        return self.i2c_device_.read_bytes<SIZE>(address);
    }

    template <std::size_t SIZE>
    void PCA9685::write_bytes(this PCA9685 const& self,
                              std::uint8_t const address,
                              std::array<std::uint8_t, SIZE> const& data) noexcept
    {
        self.i2c_device_.write_bytes(address, data);
    }

}; // namespace PCA9685

#endif // PCA9685_HPP