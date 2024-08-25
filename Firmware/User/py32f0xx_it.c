#include "main.h"
#include "py32f0xx_it.h"

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  if(LL_TIM_IsActiveFlag_UPDATE(TIM1) && LL_TIM_IsEnabledIT_UPDATE(TIM1))
  {
    LL_TIM_ClearFlag_UPDATE(TIM1);
    APP_TIM1UpdateCallback();
  }
}


const char serial[] = {"ProfPlum"};
uint8_t i2c_idx;
/**
  * Brief   This function handles I2C1 (Slave) event interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_IRQHandler(void)
{
  if(LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
    LL_I2C_ClearFlag_ADDR(I2C1);
    LL_I2C_EnableIT_BUF(I2C1);
    i2c_idx=0;
    /* Verify the transfer direction, a read direction, Slave enters transmitter mode */
    if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ) {
      /* Enable Transmit Interrupt */
      LL_I2C_EnableIT_TX(I2C1);
    }
    else {
      LL_I2C_EnableIT_RX(I2C1);
    }
  }
  if(LL_I2C_IsActiveFlag_TXE(I2C1)) {
    LL_I2C_TransmitData8(I2C1, serial[(i2c_idx++) % 8]);
  }
  if(!LL_I2C_IsActiveFlag_RXNE(I2C1)) {
    LL_I2C_ReceiveData8(I2C1);
  }
  if(LL_I2C_IsActiveFlag_AF(I2C1)) {
    /* End of Transfer */
    LL_I2C_ClearFlag_AF(I2C1);
  }
  if(LL_I2C_IsActiveFlag_STOP(I2C1)) {
    LL_I2C_DisableIT_BUF(I2C1);
    LL_I2C_ClearFlag_STOP(I2C1);
  }
  //if(LL_I2C_IsActiveFlag_ARLO(I2C1)) {
  //  LL_I2C_ClearFlag_ARLO(I2C1);
  //}
  //if(LL_I2C_IsActiveFlag_BERR(I2C1)) {
  //  LL_I2C_ClearFlag_BERR(I2C1);
  //}

}