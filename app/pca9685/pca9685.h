#ifndef PCA9685_PCA9685_H
#define PCA9685_PCA9685_H

#include "pca9685_config.h"
#include "pca9685_registers.h"

typedef struct {
    pca9685_config_t config;
    pca9685_interface_t interface;
} pca9685_t;

pca9685_err_t pca9685_initialize(pca9685_t* pca9685,
                                 pca9685_config_t const* config,
                                 pca9685_interface_t const* interface);
pca9685_err_t pca9685_deinitialize(pca9685_t* pca9685);

pca9685_err_t pca9685_send_software_reset_cmd(pca9685_t const* pca9685);

pca9685_err_t
pca9685_set_channel_compare(pca9685_t const* pca9685, pca9685_channel_t channel, uint16_t compare);
pca9685_err_t pca9685_set_channel_min_compare(pca9685_t const* pca9685, pca9685_channel_t channel);
pca9685_err_t pca9685_set_channel_max_compare(pca9685_t const* pca9685, pca9685_channel_t channel);

pca9685_err_t pca9685_set_channels_compare(pca9685_t const* pca9685, uint16_t compare);
pca9685_err_t pca9685_set_channels_min_compare(pca9685_t const* pca9685);
pca9685_err_t pca9685_set_channels_max_compare(pca9685_t const* pca9685);

pca9685_err_t pca9685_get_mode1_reg(pca9685_t const* pca9685, pca9685_mode1_reg_t* reg);
pca9685_err_t pca9685_set_mode1_reg(pca9685_t const* pca9685, pca9685_mode1_reg_t const* reg);

pca9685_err_t pca9685_get_mode2_reg(pca9685_t const* pca9685, pca9685_mode2_reg_t* reg);
pca9685_err_t pca9685_set_mode2_reg(pca9685_t const* pca9685, pca9685_mode2_reg_t const* reg);

pca9685_err_t pca9685_get_subadr1_reg(pca9685_t const* pca9685, pca9685_subadr1_reg_t* reg);
pca9685_err_t pca9685_set_subadr1_reg(pca9685_t const* pca9685, pca9685_subadr1_reg_t const* reg);

pca9685_err_t pca9685_get_subadr2_reg(pca9685_t const* pca9685, pca9685_subadr2_reg_t* reg);
pca9685_err_t pca9685_set_subadr2_reg(pca9685_t const* pca9685, pca9685_subadr2_reg_t const* reg);

pca9685_err_t pca9685_get_subadr3_reg(pca9685_t const* pca9685, pca9685_subadr3_reg_t* reg);
pca9685_err_t pca9685_set_subadr3_reg(pca9685_t const* pca9685, pca9685_subadr3_reg_t const* reg);

pca9685_err_t pca9685_get_allcalladr_reg(pca9685_t const* pca9685, pca9685_allcalladr_reg_t* reg);
pca9685_err_t pca9685_set_allcalladr_reg(pca9685_t const* pca9685,
                                         pca9685_allcalladr_reg_t const* reg);

pca9685_err_t pca9685_get_pwm_on_reg(pca9685_t const* pca9685,
                                     pca9685_channel_t channel,
                                     pca9685_pwm_on_reg_t* reg);
pca9685_err_t pca9685_set_pwm_on_reg(pca9685_t const* pca9685,
                                     pca9685_channel_t channel,
                                     pca9685_pwm_on_reg_t const* reg);

pca9685_err_t pca9685_get_pwm_off_reg(pca9685_t const* pca9685,
                                      pca9685_channel_t channel,
                                      pca9685_pwm_off_reg_t* reg);
pca9685_err_t pca9685_set_pwm_off_reg(pca9685_t const* pca9685,
                                      pca9685_channel_t channel,
                                      pca9685_pwm_off_reg_t const* reg);

pca9685_err_t pca9685_get_all_pwm_on_reg(pca9685_t const* pca9685, pca9685_all_pwm_on_reg_t* reg);
pca9685_err_t pca9685_set_all_pwm_on_reg(pca9685_t const* pca9685,
                                         pca9685_all_pwm_on_reg_t const* reg);

pca9685_err_t pca9685_get_all_pwm_off_reg(pca9685_t const* pca9685, pca9685_all_pwm_off_reg_t* reg);
pca9685_err_t pca9685_set_all_pwm_off_reg(pca9685_t const* pca9685,
                                          pca9685_all_pwm_off_reg_t const* reg);

pca9685_err_t pca9685_get_pre_scale_reg(pca9685_t const* pca9685, pca9685_pre_scale_reg_t* reg);
pca9685_err_t pca9685_set_pre_scale_reg(pca9685_t const* pca9685,
                                        pca9685_pre_scale_reg_t const* reg);

pca9685_err_t pca9685_get_test_mode_reg(pca9685_t const* pca9685, pca9685_test_mode_reg_t* reg);
pca9685_err_t pca9685_set_test_mode_reg(pca9685_t const* pca9685,
                                        pca9685_test_mode_reg_t const* reg);

#endif // PCA9685_PCA9685_H