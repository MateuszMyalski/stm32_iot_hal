#include <stddef.h>
#include <stdint.h>

/* Linker provided variables ----------- */
extern uint32_t* _stext;
extern uint32_t* _etext;

extern uint32_t* _sdata;
extern uint32_t* _edata;

extern uint32_t* _sbss;
extern uint32_t* _ebss;

extern uint32_t* _estack;
/* ------------------------------------- */

typedef void (*isr_handler)(void);

void _entry(void);
void Default_Handler(void);
void Reset_Handler(void);

void NMI_Handler(void);
void Hard_Fault_Handler(void);
void Hard_Fault_S_Handler(void)
    __attribute__((weak, alias("Hard_Fault_Handler")));
void Mem_Manage_Handler(void);
void Bus_Fault_Handler(void);
void Usage_Fault_Handler(void);
void Secure_Fault_Handler(void);
void SVC_Handler(void);
void Debug_Monitor_Handler(void);
void Pend_Sv_Handler(void);
void Sys_Tick_Handler(void);

void WWDG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_PVM_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_S_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TAMP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RAM_CFG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_S_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GTZC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_S_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI8_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI12_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI13_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI14_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_Handler(void) __attribute__((weak, alias("Default_Handler")));
void IWDG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SAES_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DAC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FDCAN1_IT0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FDCAN1_IT1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TERR_IERR_Handler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_DIR_IDX_Handler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TERR_IERR_Handler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_DIR_IDX_Handler(void)
    __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPUART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM15_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM16_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM17_Handler(void) __attribute__((weak, alias("Default_Handler")));
void COMP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CRS_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FMC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OCTOSPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWR_S3WU_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SDMMC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SDMMC2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH8_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH12_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH13_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH14_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPDMA1_CH15_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SAI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SAI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TSC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void AES_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RNG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HASH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PKA_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C4_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C4_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UCPD1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ICACHE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTFDEC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTFDEC2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DCACHE1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADF1_FLT0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPDMA1_CH0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPDMA1_CH1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPDMA1_CH2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LPDMA1_CH3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2D_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DCMI_PSSI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OCTOSPI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MDF1_FLT5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CORDIC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FMAC_Handler(void) __attribute__((weak, alias("Default_Handler")));

isr_handler init_vec[] __attribute__((section(".init_vec"))) = {
    (isr_handler)&_estack,  // Stack Pointer
    Reset_Handler,
    NMI_Handler,
    Hard_Fault_S_Handler,
    Hard_Fault_Handler,
    Mem_Manage_Handler,
    Bus_Fault_Handler,
    Usage_Fault_Handler,
    Secure_Fault_Handler,
    0,  // Reserved
    0,  // Reserved
    SVC_Handler,
    Debug_Monitor_Handler,
    0,  // Reserved
    Pend_Sv_Handler,
    Sys_Tick_Handler,
    WWDG_Handler,
    PVD_PVM_Handler,
    RTC_Handler,
    RTC_S_Handler,
    TAMP_Handler,
    RAM_CFG_Handler,
    FLASH_Handler,
    FLASH_S_Handler,
    GTZC_Handler,
    RCC_Handler,
    RCC_S_Handler,
    EXTI0_Handler,
    EXTI1_Handler,
    EXTI2_Handler,
    EXTI3_Handler,
    EXTI4_Handler,
    EXTI5_Handler,
    EXTI6_Handler,
    EXTI7_Handler,
    EXTI8_Handler,
    EXTI9_Handler,
    EXTI10_Handler,
    EXTI11_Handler,
    EXTI12_Handler,
    EXTI13_Handler,
    EXTI14_Handler,
    EXTI15_Handler,
    IWDG_Handler,
    SAES_Handler,
    GPDMA1_CH0_Handler,
    GPDMA1_CH1_Handler,
    GPDMA1_CH2_Handler,
    GPDMA1_CH3_Handler,
    GPDMA1_CH4_Handler,
    GPDMA1_CH5_Handler,
    GPDMA1_CH6_Handler,
    GPDMA1_CH7_Handler,
    ADC1_Handler,
    DAC1_Handler,
    FDCAN1_IT0_Handler,
    FDCAN1_IT1_Handler,
    TIM1_BRK_TERR_IERR_Handler,
    TIM1_UP_Handler,
    TIM1_TRG_COM_DIR_IDX_Handler,
    TIM1_CC_Handler,
    TIM2_Handler,
    TIM3_Handler,
    TIM4_Handler,
    TIM5_Handler,
    TIM6_Handler,
    TIM7_Handler,
    TIM8_BRK_TERR_IERR_Handler,
    TIM8_UP_Handler,
    TIM8_TRG_COM_DIR_IDX_Handler,
    I2C1_EV_Handler,
    I2C1_ER_Handler,
    I2C1_EV_Handler,
    I2C2_ER_Handler,
    SPI1_Handler,
    SPI2_Handler,
    USART1_Handler,
    USART2_Handler,
    USART3_Handler,
    UART4_Handler,
    UART5_Handler,
    LPUART1_Handler,
    LPTIM1_Handler,
    LPTIM2_Handler,
    TIM15_Handler,
    TIM16_Handler,
    TIM17_Handler,
    COMP_Handler,
    OTG_FS_Handler,
    CRS_Handler,
    FMC_Handler,
    OCTOSPI1_Handler,
    PWR_S3WU_Handler,
    SDMMC1_Handler,
    SDMMC2_Handler,
    GPDMA1_CH8_Handler,
    GPDMA1_CH9_Handler,
    GPDMA1_CH10_Handler,
    GPDMA1_CH11_Handler,
    GPDMA1_CH12_Handler,
    GPDMA1_CH13_Handler,
    GPDMA1_CH14_Handler,
    GPDMA1_CH15_Handler,
    I2C3_EV_Handler,
    I2C3_ER_Handler,
    SAI1_Handler,
    SAI2_Handler,
    TSC_Handler,
    AES_Handler,
    RNG_Handler,
    FPU_Handler,
    HASH_Handler,
    PKA_Handler,
    LPTIM3_Handler,
    SPI3_Handler,
    I2C4_ER_Handler,
    I2C4_EV_Handler,
    MDF1_FLT0_Handler,
    MDF1_FLT1_Handler,
    MDF1_FLT2_Handler,
    MDF1_FLT3_Handler,
    UCPD1_Handler,
    ICACHE_Handler,
    OTFDEC1_Handler,
    OTFDEC2_Handler,
    LPTIM4_Handler,
    DCACHE1_Handler,
    ADF1_FLT0_Handler,
    ADC4_Handler,
    LPDMA1_CH0_Handler,
    LPDMA1_CH1_Handler,
    LPDMA1_CH2_Handler,
    LPDMA1_CH3_Handler,
    DMA2D_Handler,
    DCMI_PSSI_Handler,
    OCTOSPI2_Handler,
    MDF1_FLT4_Handler,
    MDF1_FLT5_Handler,
    CORDIC_Handler,
    FMAC_Handler};

void Reset_Handler(void) {
  __asm("LDR  r0, =0x1000000");
  uint32_t tmp = 2;
  __asm("LDR  r0, =0x1000010");

  /* Copy init values from text to data */
  uint32_t* init_values_ptr = &_etext;
  uint32_t* data_value = &_sdata;
  __asm("LDR  r0, =0x1000001");

  if (init_values_ptr != data_value) {
    for (; data_value < &_edata;) {
      *data_value++ = *init_values_ptr++;
      __asm("LDR  r0, =0x1000002");
    }
  }

  /* Clear the zero segment */
  for (int* bss_value = &_sbss; bss_value < &_ebss;) {
    *bss_value++ = 0;
    __asm("LDR  r0, =0x1000003");
  }

  while (1) {
    for (int i = 0; i < 100000; ++i) {
      __asm("nop");
      __asm("LDR  r0, =0x1000004");
    }
  }
}

void NMI_Handler(void) { __asm("LDR  r0, =0x2000000"); }
void Hard_Fault_Handler(void) { __asm("LDR  r0, =0x3000000"); }
void Mem_Manage_Handler(void) { __asm("LDR  r0, =0x4000000"); }
void Bus_Fault_Handler(void) { __asm("LDR  r0, =0x5000000"); }
void Usage_Fault_Handler(void) { __asm("LDR  r0, =0x6000000"); }
void Secure_Fault_Handler(void) { __asm("LDR  r0, =0x7000000"); }
void SVC_Handler(void) { __asm("LDR  r0, =0x8000000"); }
void Debug_Monitor_Handler(void) { __asm("LDR  r0, =0x9000000"); }
void Pend_Sv_Handler(void) { __asm("LDR  r0, =0xA000000"); }
void Sys_Tick_Handler(void) { __asm("LDR  r0, =0xB000000"); }

void Default_Handler(void) {
  __asm("LDR  r0, =0x1010101");
  __asm("LDR  r8, =0x0101010");

  while(1)
    ;
}

void _entry(void) {
  __asm("LDR  r0, =0xA0A0A0A");
  __asm("LDR  r8, =0x0A0A0A0");
}