/***
 * Demo: TIM1 PWM 
 * 
 * CH1:PA8  -> CH1N:PA7
 * CH2:PA9  -> CH2N:PB0
 * CH3:PA10 -> CH3N:PB1
 */
#include "main.h"
#include "py32f0xx_bsp_clock.h"

static void APP_PWMChannelConfig(void);
static void APP_TIM1BaseConfig(void);
static void APP_I2CConfig(void);

int main(void)
{
  BSP_RCC_HSI_24MConfig();

  //BSP_USART_Config(115200);
  //printf("TIM1 PWM Demo\r\nClock: %ld \r\n", SystemCoreClock);

  APP_TIM1BaseConfig();
  APP_PWMChannelConfig();
  
  //LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  //LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);

  APP_I2CConfig();

  while (1)
  {
    //LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_1);
    //LL_mDelay(500);
  }
}

const uint16_t heart_pat[48] ={500,990,600,300,100,0,0,0,500,990,700,500,400,300,250,200,150,100,50,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

const uint16_t sineLookupTable[] = {
0x1f4, 0x200, 0x20c, 0x218, 0x224, 0x231, 0x23d, 0x249, 0x255, 0x261, 0x26d, 0x279, 0x284, 0x290, 0x29c, 0x2a7, 0x2b3, 0x2be, 0x2c9, 0x2d4, 0x2df, 0x2ea, 0x2f4, 0x2ff, 0x309, 0x313, 0x31d, 0x327, 0x330, 0x33a, 0x343, 0x34c,
0x355, 0x35d, 0x366, 0x36e, 0x376, 0x37d, 0x385, 0x38c, 0x393, 0x39a, 0x3a0, 0x3a6, 0x3ac, 0x3b2, 0x3b7, 0x3bc, 0x3c1, 0x3c6, 0x3ca, 0x3ce, 0x3d1, 0x3d5, 0x3d8, 0x3db, 0x3dd, 0x3e0, 0x3e2, 0x3e3, 0x3e5, 0x3e6, 0x3e6, 0x3e7,
0x3e7, 0x3e7, 0x3e6, 0x3e6, 0x3e5, 0x3e3, 0x3e2, 0x3e0, 0x3dd, 0x3db, 0x3d8, 0x3d5, 0x3d1, 0x3ce, 0x3ca, 0x3c6, 0x3c1, 0x3bc, 0x3b7, 0x3b2, 0x3ac, 0x3a6, 0x3a0, 0x39a, 0x393, 0x38c, 0x385, 0x37d, 0x376, 0x36e, 0x366, 0x35d,
0x355, 0x34c, 0x343, 0x33a, 0x330, 0x327, 0x31d, 0x313, 0x309, 0x2ff, 0x2f4, 0x2ea, 0x2df, 0x2d4, 0x2c9, 0x2be, 0x2b3, 0x2a7, 0x29c, 0x290, 0x284, 0x279, 0x26d, 0x261, 0x255, 0x249, 0x23d, 0x231, 0x224, 0x218, 0x20c, 0x200,
0x1f4, 0x1e7, 0x1db, 0x1cf, 0x1c3, 0x1b6, 0x1aa, 0x19e, 0x192, 0x186, 0x17a, 0x16e, 0x163, 0x157, 0x14b, 0x140, 0x134, 0x129, 0x11e, 0x113, 0x108, 0xfd, 0xf3, 0xe8, 0xde, 0xd4, 0xca, 0xc0, 0xb7, 0xad, 0xa4, 0x9b,
0x92, 0x8a, 0x81, 0x79, 0x71, 0x6a, 0x62, 0x5b, 0x54, 0x4d, 0x47, 0x41, 0x3b, 0x35, 0x30, 0x2b, 0x26, 0x21, 0x1d, 0x19, 0x16, 0x12, 0x0f, 0x0c, 0x0a, 0x07, 0x05, 0x04, 0x02, 0x01, 0x01, 0x00,
0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x05, 0x07, 0x0a, 0x0c, 0x0f, 0x12, 0x16, 0x19, 0x1d, 0x21, 0x26, 0x2b, 0x30, 0x35, 0x3b, 0x41, 0x47, 0x4d, 0x54, 0x5b, 0x62, 0x6a, 0x71, 0x79, 0x81, 0x8a,
0x92, 0x9b, 0xa4, 0xad, 0xb7, 0xc0, 0xca, 0xd4, 0xde, 0xe8, 0xf3, 0xfd, 0x108, 0x113, 0x11e, 0x129, 0x134, 0x140, 0x14b, 0x157, 0x163, 0x16e, 0x17a, 0x186, 0x192, 0x19e, 0x1aa, 0x1b6, 0x1c3, 0x1cf, 0x1db, 0x1e7};

int heart_idx=0;
void APP_TIM1UpdateCallback(void)
{
  //LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_1);
  LL_TIM_OC_SetCompareCH4(TIM1, sineLookupTable[(++heart_idx) % 256]);
}


static void APP_I2CConfig(void) 
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  NVIC_EnableIRQ(I2C1_IRQn);
  NVIC_SetPriority(I2C1_IRQn,0);
  
  // PF1 SCL , PF0 SDA
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1 | LL_GPIO_PIN_0;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);

  LL_I2C_InitTypeDef I2C_InitStruct;
  /*
   * Clock speed:
   * - standard = 100khz
   * - fast     = 400khz
  */
  I2C_InitStruct.ClockSpeed      = LL_I2C_MAX_SPEED_FAST;
  I2C_InitStruct.DutyCycle       = LL_I2C_DUTYCYCLE_2;
  I2C_InitStruct.OwnAddress1     = I2C_SLAVE_OWN_ADDR;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  LL_I2C_Init(I2C1, &I2C_InitStruct);


  LL_I2C_Enable(I2C1);
  
  LL_I2C_EnableIT_EVT(I2C1); //Any event 
  //LL_I2C_EnableIT_ERR(I2C1); //Error INT
}

static void APP_PWMChannelConfig(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* PA1 -> TIM1_CH4*/
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_1;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_13;
  LL_GPIO_Init(GPIOA, &TIM1CH1MapInit);

  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW;

  TIM_OC_Initstruct.CompareValue  = 999;
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH4, &TIM_OC_Initstruct);
}

static void APP_TIM1BaseConfig(void)
{
  LL_TIM_InitTypeDef TIM1CountInit = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
 
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;
  TIM1CountInit.Prescaler           = 300-1;
  TIM1CountInit.Autoreload          = 1000-1;
  TIM1CountInit.RepetitionCounter   = 0;
  LL_TIM_Init(TIM1,&TIM1CountInit);
  LL_TIM_EnableAllOutputs(TIM1);

  LL_TIM_EnableIT_UPDATE(TIM1);
  LL_TIM_EnableCounter(TIM1);

  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
}

void APP_ErrorHandler(void)
{
  while (1);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1);
}
#endif /* USE_FULL_ASSERT */