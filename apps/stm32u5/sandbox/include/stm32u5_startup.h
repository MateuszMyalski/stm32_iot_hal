#ifndef STM32U5_STARTUP_H
#define STM32U5_STARTUP_H

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

/* ISR vector handlers ----------------- */
typedef void (*isr_handler)(void);

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

/* ------------------------------------- */
#endif