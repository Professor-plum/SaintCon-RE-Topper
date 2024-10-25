#include "main.h"
#include "py32f0xx_it.h"
#include <stdbool.h>
#include <stdlib.h>

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


extern int ptn;

bool serialmode = 0;

const uint8_t memory_data[10][8] = {
  "ZSandals", 
  "Hydra   ", 
  "Scrooge ",
  "Greed   ",
  "ExtraDmg", 
  "GlassCan", 
  "RevShell", //Guess
  "SavingTh", //Guess
  "Simplify", //Guess
  "SpellChk"  //Guess
};

//"ZSandals",
//b'\t \x87\x04T\x10\x04R\x8cX\xa0\x80\xa0\x80\x00\x8e'

//b'Greed   '
//b'\t \x87\x04T\x10\x04P\xbc`\xa0\x80\xa0\x80\x00\t'
//b'\t \x87\x04T\x10\x04Q\x9cp\xa0\x80\xa0\x80\x00\xbc'

//b'Scrooge '
//b'\t \x87\x04T\x10\x04R\xb46\xa0\x80\xa0\x80\x00\xd2'
//b'\t \x87\x04T\x10\x04R\xd07\xa0\x80\xa0\x80\x00t',

//b'GlassCan' //could be lowercase C


/*
b'ExtraDmg'
b'\t \x87\x04T\x10\x04QLO\xa0\x80\xa0\x80\x00\xbb'
b'Hydra   '
b'\t \x87\x04T\x10\x04P\x9ca\xa0\x80\xa0\x80\x00\xa0'
b'SavingTh'
b'\t \x87\x04T\x10\x04Q`^\xa0\x80\xa0\x80\x00\x9e'
b'ZSandals'
b'\t \x87\x04T\x10\x04P\xe4n\xa0\x80\xa0\x80\x00\x87'
b'RevShell'
b'\t \x87\x04T\x10\x04P\x84&\xa0\x80\xa0\x80\x00\x8d'
b'Simplify'
b'\t \x87\x04T\x10\x04P\xc4e\xa0\x80\xa0\x80\x00\x18'
b'Scrooge '
b'\t \x87\x04T\x10\x04R4\x88\xa0\x80\xa0\x80\x00W'
b'Greed   '
b'\t \x87\x04T\x10\x04QDf\xa0\x80\xa0\x80\x00\xcc'
b'SpellChk'
b"\t \x87\x04T\x10\x04Qt'\xa0\x80\xa0\x80\x00\xf5"



*/

uint8_t rand_serial[16] = "\t \x87\x04T\x10\x06XXX\xa0\x80\xa0\x80\x00X";

const uint8_t serial_data[10][16] = {
  "\t \x87\x04T\x10\x04P\xe4n\xa0\x80\xa0\x80\x00\x87",
  "\t \x87\x04T\x10\x04P\x9c\x91\xa0\x80\xa0\x80\x00\xa0",
  "\t \x87\x04T\x10\x04R\xb4\x36\xa0\x80\xa0\x80\x00\xd2",
  "\t \x87\x04T\x10\x04QDf\xa0\x80\xa0\x80\x00\xcc",
  "\t \x87\x04T\x10\x04QLO\xa0\x80\xa0\x80\x00\xbb",
  "\t \x87\x04T\x10\x04R\xb4\x36\xa0\x80\xa0\x80\x00\xd2",
  "\t \x87\x04T\x10\x04P\x84&\xa0\x80\xa0\x80\x00\x8d",
  "\t \x87\x04T\x10\x04Q`^\xa0\x80\xa0\x80\x00\x9e",
  "\t \x87\x04T\x10\x04P\xc4\x60\xa0\x80\xa0\x80\x00\x18",
  "\t \x87\x04T\x10\x04Qt'\xa0\x80\xa0\x80\x00\xf5"
};

uint8_t i2c_idx;
extern int ser_counter;

void FlipI2CAddr() {
  //return;
  serialmode = !serialmode;
  if (serialmode) {
    LL_I2C_SetOwnAddress1(I2C1, 0x58 << 1, 0);
    rand_serial[7] = rand();
    rand_serial[8] = rand();
    rand_serial[9] = rand();
    rand_serial[15] = rand();
    ser_counter = 0;
  }
  else {
    LL_I2C_SetOwnAddress1(I2C1, 0x50 << 1, 0);
    ser_counter = 6000;
  }
}

void ResetI2CAddr() {
  serialmode = false;
  LL_I2C_SetOwnAddress1(I2C1, 0x50 << 1, 0);
  ser_counter = 6000;
}

void I2C1_IRQHandler(void)
{
  // A master is addressing us? 
  if (LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
    // Clear the flag 
    LL_I2C_ClearFlag_ADDR(I2C1);
    
    i2c_idx=0;
  }
  // Stop condition flag set 
  else if (LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    // Clear the flag 
    LL_I2C_ClearFlag_STOP(I2C1);
    // ACK the next byte addressed to us 
    //FlipI2CAddr();
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  }
  // TX empty flag set 
  else if (LL_I2C_IsActiveFlag_TXE(I2C1))
  {
    if (serialmode) {
      LL_I2C_TransmitData8(I2C1, rand_serial[i2c_idx++ %16]); //serial_data[ptn][i2c_idx++ %16]);
      if ((i2c_idx % 16) == 0){
        FlipI2CAddr();
      }
    }
    else {
      LL_I2C_TransmitData8(I2C1, memory_data[ptn][i2c_idx++ %8]);
      if ((i2c_idx % 8) == 0) {
        FlipI2CAddr();
      }
    }
  }
  // RX not empty flag set 
  else if (LL_I2C_IsActiveFlag_RXNE(I2C1))
  {
    // Are we receiving the index? 
    LL_I2C_ReceiveData8(I2C1);
  }

  if(LL_I2C_IsActiveFlag_AF(I2C1)) {
    // End of Transfer 
    //FlipI2CAddr();
    LL_I2C_ClearFlag_AF(I2C1);
  }
}