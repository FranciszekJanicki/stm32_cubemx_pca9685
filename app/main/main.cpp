#include "main.h"
#include "i2c.h"
#include "i2c_device.hpp"
#include "pca9685.hpp"
#include "pca9685_config.hpp"
#include "pca9685_registers.hpp"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_USART2_UART_Init();
    MX_I2C1_Init();

    using namespace PCA9685;

    auto i2c_device = I2CDevice{};

    constexpr auto mode1 = MODE1{};
    constexpr auto mode2 = MODE2{};
    constexpr auto pre_scale = PRE_SCALE{};
    constexpr auto subadr1 = SUBADR1{};
    constexpr auto subadr2 = SUBADR2{};
    constexpr auto subadr3 = SUBADR3{};
    constexpr auto allcalladr = ALLCALLADR{};
    constexpr auto test_mode = TEST_MODE{};

    auto config = Config{.mode1 = mode1,
                         .mode2 = mode2,
                         .pre_scale = pre_scale,
                         .subadr1 = subadr1,
                         .subadr2 = subadr2,
                         .subadr3 = subadr3,
                         .allcalladr = allcalladr,
                         .test_mode = test_mode};

    auto pca9685 = PCA9685::PCA9685{std::move(i2c_device), config};

    while (1) {
    }
}
