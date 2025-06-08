#include "pca9685.h"
#include "pca9685_utility.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

static pca9685_err_t pca9685_bus_init(pca9685_t const* pca9685)
{
    return pca9685->interface.bus_init ? pca9685->interface.bus_init(pca9685->interface.bus_user)
                                       : PCA9685_ERR_NULL;
}

static pca9685_err_t pca9685_bus_deinit(pca9685_t const* pca9685)
{
    return pca9685->interface.bus_deinit
               ? pca9685->interface.bus_deinit(pca9685->interface.bus_user)
               : PCA9685_ERR_NULL;
}

static pca9685_err_t pca9685_bus_write(pca9685_t const* pca9685,
                                       uint8_t address,
                                       uint8_t const* data,
                                       size_t data_size)
{
    return pca9685->interface.bus_write
               ? pca9685->interface.bus_write(pca9685->interface.bus_user, address, data, data_size)
               : PCA9685_ERR_NULL;
}

static pca9685_err_t pca9685_bus_read(pca9685_t const* pca9685,
                                      uint8_t address,
                                      uint8_t* data,
                                      size_t data_size)
{
    return pca9685->interface.bus_read
               ? pca9685->interface.bus_read(pca9685->interface.bus_user, address, data, data_size)
               : PCA9685_ERR_NULL;
}

pca9685_err_t pca9685_initialize(pca9685_t* pca9685,
                                 pca9685_config_t const* config,
                                 pca9685_interface_t const* interface)
{
    assert(pca9685 && config && interface);

    memset(pca9685, 0, sizeof(*pca9685));
    memcpy(&pca9685->config, config, sizeof(*config));
    memcpy(&pca9685->interface, interface, sizeof(*interface));

    return pca9685_bus_init(pca9685);
}

pca9685_err_t pca9685_deinitialize(pca9685_t* pca9685)
{
    assert(pca9685);

    pca9685_err_t err = pca9685_bus_deinit(pca9685);

    memset(pca9685, 0, sizeof(*pca9685));

    return err;
}

pca9685_err_t pca9685_send_software_reset_cmd(pca9685_t const* pca9685)
{
    assert(pca9685);

    return pca9685_bus_write(pca9685, PCA9685_COMMAND_SOFTWARE_RESET, NULL, 0UL);
}

pca9685_err_t pca9685_set_channel_compare(pca9685_t const* pca9685,
                                          pca9685_channel_t channel,
                                          uint16_t compare)
{
    assert(pca9685);

    pca9685_pwm_on_reg_t on_reg = {.pwm_on = pca9685_compare_to_pwm_on(compare),
                                   .pwm_full_on = false};
    pca9685_pwm_off_reg_t off_reg = {.pwm_off = pca9685_compare_to_pwm_off(compare),
                                     .pwm_full_off = false};

    pca9685_err_t err = pca9685_set_pwm_on_reg(pca9685, channel, &on_reg);
    err |= pca9685_set_pwm_off_reg(pca9685, channel, &off_reg);

    return err;
}

pca9685_err_t pca9685_set_channel_min_compare(pca9685_t const* pca9685, pca9685_channel_t channel)
{
    assert(pca9685);

    pca9685_pwm_on_reg_t on_reg = {.pwm_full_on = false};
    pca9685_pwm_off_reg_t off_reg = {.pwm_full_off = true};

    pca9685_err_t err = pca9685_set_pwm_on_reg(pca9685, channel, &on_reg);
    err |= pca9685_set_pwm_off_reg(pca9685, channel, &off_reg);

    return err;
}

pca9685_err_t pca9685_set_channel_max_compare(pca9685_t const* pca9685, pca9685_channel_t channel)
{
    assert(pca9685);

    pca9685_pwm_on_reg_t on_reg = {.pwm_full_on = true};
    pca9685_pwm_off_reg_t off_reg = {.pwm_full_off = false};

    pca9685_err_t err = pca9685_set_pwm_on_reg(pca9685, channel, &on_reg);
    err |= pca9685_set_pwm_off_reg(pca9685, channel, &off_reg);

    return err;
}

pca9685_err_t pca9685_set_channels_compare(pca9685_t const* pca9685, uint16_t compare)
{
    assert(pca9685);

    pca9685_all_pwm_on_reg_t all_on_reg = {.all_pwm_on = pca9685_compare_to_pwm_on(compare),
                                           .all_pwm_full_on = false};
    pca9685_all_pwm_off_reg_t all_off_reg = {.all_pwm_off = pca9685_compare_to_pwm_off(compare),
                                             .all_pwm_full_off = false};

    pca9685_err_t err = pca9685_set_all_pwm_on_reg(pca9685, &all_on_reg);
    err |= pca9685_set_all_pwm_off_reg(pca9685, &all_off_reg);

    return err;
}

pca9685_err_t pca9685_set_channels_min_compare(pca9685_t const* pca9685)
{
    assert(pca9685);

    pca9685_all_pwm_on_reg_t all_on_reg = {.all_pwm_full_on = false};
    pca9685_all_pwm_off_reg_t all_off_reg = {.all_pwm_full_off = true};

    pca9685_err_t err = pca9685_set_all_pwm_on_reg(pca9685, &all_on_reg);
    err |= pca9685_set_all_pwm_off_reg(pca9685, &all_off_reg);

    return err;
}

pca9685_err_t pca9685_set_channels_max_compare(pca9685_t const* pca9685)
{
    assert(pca9685);

    pca9685_all_pwm_on_reg_t all_on_reg = {.all_pwm_full_on = true};
    pca9685_all_pwm_off_reg_t all_off_reg = {.all_pwm_full_off = false};

    pca9685_err_t err = pca9685_set_all_pwm_on_reg(pca9685, &all_on_reg);
    err |= pca9685_set_all_pwm_off_reg(pca9685, &all_off_reg);

    return err;
}

pca9685_err_t pca9685_get_mode1_reg(pca9685_t const* pca9685, pca9685_mode1_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_MODE1, &data, sizeof(data));

    reg->restart = (data >> 7U) & 0x01U;
    reg->extclk = (data >> 6U) & 0x01U;
    reg->ai = (data >> 5U) & 0x01U;
    reg->sleep = (data >> 4U) & 0x01U;
    reg->sub1 = (data >> 3U) & 0x01U;
    reg->sub2 = (data >> 2U) & 0x01U;
    reg->sub3 = (data >> 1U) & 0x01U;
    reg->allcall = data & 0x01U;

    return err;
}

pca9685_err_t pca9685_set_mode1_reg(pca9685_t const* pca9685, pca9685_mode1_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    data |= (reg->restart & 0x01U) << 7U;
    data |= (reg->extclk & 0x01U) << 6U;
    data |= (reg->ai & 0x01U) << 5U;
    data |= (reg->sleep & 0x01U) << 4U;
    data |= (reg->sub1 & 0x01U) << 3U;
    data |= (reg->sub2 & 0x01U) << 2U;
    data |= (reg->sub3 & 0x01U) << 1U;
    data |= reg->allcall & 0x01U;

    return pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_MODE1, &data, sizeof(data));
}

pca9685_err_t pca9685_get_mode2_reg(pca9685_t const* pca9685, pca9685_mode2_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_MODE2, &data, sizeof(data));

    reg->invrt = (data >> 4U) & 0x01U;
    reg->och = (data >> 3U) & 0x01U;
    reg->outdrv = (data >> 2U) & 0x01U;
    reg->outne = data & 0x03U;

    return err;
}

pca9685_err_t pca9685_set_mode2_reg(pca9685_t const* pca9685, pca9685_mode2_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_MODE2, &data, sizeof(data));

    data &= ~((0x01U << 4U) | (0x01 << 3U) | (0x01 << 2U) | 0x03U);

    data |= (reg->invrt & 0x01U) << 4U;
    data |= (reg->och & 0x01U) << 3U;
    data |= (reg->outdrv & 0x01U) << 2U;
    data |= reg->outne & 0x03U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_MODE2, &data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_subadr1_reg(pca9685_t const* pca9685, pca9685_subadr1_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR1, &data, sizeof(data));

    reg->a1 = (data >> 1U) & 0x0EFU;

    return err;
}

pca9685_err_t pca9685_set_subadr1_reg(pca9685_t const* pca9685, pca9685_subadr1_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR1, &data, sizeof(data));

    data &= ~(0xEFU << 1U);

    data |= (reg->a1 & 0x0EFU) << 1U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_SUBADR1, &data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_subadr2_reg(pca9685_t const* pca9685, pca9685_subadr2_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR2, &data, sizeof(data));

    reg->a2 = (data >> 1U) & 0x0EFU;

    return err;
}

pca9685_err_t pca9685_set_subadr2_reg(pca9685_t const* pca9685, pca9685_subadr2_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR2, &data, sizeof(data));

    data &= ~(0xEFU << 1U);

    data |= (reg->a2 & 0x0EFU) << 1U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_SUBADR2, &data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_subadr3_reg(pca9685_t const* pca9685, pca9685_subadr3_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR3, &data, sizeof(data));

    reg->a3 = (data >> 1U) & 0x0EFU;

    return err;
}

pca9685_err_t pca9685_set_subadr3_reg(pca9685_t const* pca9685, pca9685_subadr3_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err = pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_SUBADR3, &data, sizeof(data));

    data &= ~(0xEFU << 1U);

    data |= (reg->a3 & 0x0EFU) << 1U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_SUBADR3, &data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_allcalladr_reg(pca9685_t const* pca9685, pca9685_allcalladr_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALLCALLADR, &data, sizeof(data));

    reg->ac = (data >> 1U) & 0xEFU;

    return err;
}

pca9685_err_t pca9685_set_allcalladr_reg(pca9685_t const* pca9685,
                                         pca9685_allcalladr_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALLCALLADR, &data, sizeof(data));

    data &= ~(0xEFU << 1U);

    data |= (reg->ac & 0xEFU) << 1U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_ALLCALLADR, &data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_pwm_on_reg(pca9685_t const* pca9685,
                                     pca9685_channel_t channel,
                                     pca9685_pwm_on_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err = pca9685_bus_read(pca9685,
                                         pca9685_channel_to_pwm_on_reg_address(channel),
                                         data,
                                         sizeof(data));

    reg->pwm_on = ((data[0] & 0xFFU) | ((data[1] & 0x0FU) << 8U));
    reg->pwm_full_on = (data[1] >> 4U) & 0x01U;

    return err;
}

pca9685_err_t pca9685_set_pwm_on_reg(pca9685_t const* pca9685,
                                     pca9685_channel_t channel,
                                     pca9685_pwm_on_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err = pca9685_bus_read(pca9685,
                                         pca9685_channel_to_pwm_on_reg_address(channel),
                                         data,
                                         sizeof(data));

    data[0] &= ~0xFFU;
    data[1] &= ~(0x0FU | (0x01U << 4U));

    data[0] |= reg->pwm_on & 0xFFU;
    data[1] |= (reg->pwm_on >> 8U) & 0x0FU;
    data[1] |= (reg->pwm_full_on & 0x01U) << 4U;

    err |= pca9685_bus_write(pca9685,
                             pca9685_channel_to_pwm_on_reg_address(channel),
                             data,
                             sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_pwm_off_reg(pca9685_t const* pca9685,
                                      pca9685_channel_t channel,
                                      pca9685_pwm_off_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err = pca9685_bus_read(pca9685,
                                         pca9865_channel_to_pwm_off_reg_address(channel),
                                         data,
                                         sizeof(data));

    reg->pwm_off = (data[0] & 0xFFU) | ((data[1] & 0x0FU) << 8U);
    reg->pwm_full_off = (data[1] >> 4U) & 0x01U;

    return err;
}

pca9685_err_t pca9685_set_pwm_off_reg(pca9685_t const* pca9685,
                                      pca9685_channel_t channel,
                                      pca9685_pwm_off_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err = pca9685_bus_read(pca9685,
                                         pca9865_channel_to_pwm_off_reg_address(channel),
                                         data,
                                         sizeof(data));

    data[0] &= ~0xFFU;
    data[1] &= ~(0x0FU | (0x01U << 4U));

    data[0] |= reg->pwm_off & 0xFFU;
    data[1] |= (reg->pwm_off >> 8U) & 0x0FU;
    data[1] |= (reg->pwm_full_off & 0x01U) << 4U;

    err |= pca9685_bus_write(pca9685,
                             pca9865_channel_to_pwm_off_reg_address(channel),
                             data,
                             sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_all_pwm_on_reg(pca9685_t const* pca9685, pca9685_all_pwm_on_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_ON_L, data, sizeof(data));

    reg->all_pwm_on = (data[0] & 0xFFU) | ((data[1] & 0x0FU) << 8U);

    return err;
}

pca9685_err_t pca9685_set_all_pwm_on_reg(pca9685_t const* pca9685,
                                         pca9685_all_pwm_on_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_ON_L, data, sizeof(data));

    data[0] &= ~0xFFU;
    data[1] &= ~(0x0FU | (0x01U << 4U));

    data[0] |= (reg->all_pwm_on & 0xFFU);
    data[1] |= (reg->all_pwm_on >> 8U) & 0x0FU;
    data[1] |= (reg->all_pwm_full_on & 0x01U) << 4U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_ON_L, data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_all_pwm_off_reg(pca9685_t const* pca9685, pca9685_all_pwm_off_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data[2] = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_OFF_L, data, sizeof(data));

    reg->all_pwm_off = (data[0] & 0xFFU) | ((data[1] & 0x0FU) << 8U);
    reg->all_pwm_full_off = (data[1] >> 4U) & 0x01U;

    return err;
}

pca9685_err_t pca9685_set_all_pwm_off_reg(pca9685_t const* pca9685,
                                          pca9685_all_pwm_off_reg_t const* reg)
{
    assert(pca9685 && reg);
    uint8_t data[2] = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_OFF_L, data, sizeof(data));

    data[0] &= ~0xFFU;
    data[1] &= ~(0x0FU | (0x01U << 1U));

    data[0] |= (reg->all_pwm_off & 0xFFU);
    data[1] |= (reg->all_pwm_off >> 8U) & 0x0FU;
    data[1] |= (reg->all_pwm_full_off & 0x01U) << 4U;

    err |= pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_ALL_PWM_OFF_L, data, sizeof(data));

    return err;
}

pca9685_err_t pca9685_get_pre_scale_reg(pca9685_t const* pca9685, pca9685_pre_scale_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_PRE_SCALE, &data, sizeof(data));

    reg->pre_scale = data & 0xFFU;

    return err;
}

pca9685_err_t pca9685_set_pre_scale_reg(pca9685_t const* pca9685,
                                        pca9685_pre_scale_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    data = reg->pre_scale & 0xFFU;

    return pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_PRE_SCALE, &data, sizeof(data));
}

pca9685_err_t pca9685_get_test_mode_reg(pca9685_t const* pca9685, pca9685_test_mode_reg_t* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    pca9685_err_t err =
        pca9685_bus_read(pca9685, PCA9685_REG_ADDRESS_TEST_MODE, &data, sizeof(data));

    reg->mode = data & 0xFFU;

    return err;
}

pca9685_err_t pca9685_set_test_mode_reg(pca9685_t const* pca9685,
                                        pca9685_test_mode_reg_t const* reg)
{
    assert(pca9685 && reg);

    uint8_t data = {};

    data = reg->mode & 0xFFU;

    return pca9685_bus_write(pca9685, PCA9685_REG_ADDRESS_TEST_MODE, &data, sizeof(data));
}
