#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "py32f0xx_ll_adc.h"
#include "py32f0xx_ll_bus.h"
#include "py32f0xx_ll_cortex.h"
#include "py32f0xx_ll_dma.h"
#include "py32f0xx_ll_exti.h"
#include "py32f0xx_ll_gpio.h"
#include "py32f0xx_ll_pwr.h"
#include "py32f0xx_ll_rcc.h"
#include "py32f0xx_ll_i2c.h"
#include "py32f0xx_ll_system.h"
#include "py32f0xx_ll_tim.h"
#include "py32f0xx_ll_utils.h"

#define I2C_SLAVE_OWN_ADDR  (0x28 << 1) //40

void APP_ErrorHandler(void);
void APP_TIM1UpdateCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
