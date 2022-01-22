#include "stm32u5_startup.h"
#include "dbg_utils.h"

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
    FMAC_Handler
};

int main(void);
void _entry(void);
void __libc_init_array(void);

void Reset_Handler(void) { 
    _entry(); 
    while(1) {
        /* Hang the device */
    }
}

void NMI_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x2000000);
    while(1) { 
        /* Hang the device */
    } 
}
void Hard_Fault_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x3000000); 
    while(1) { /* Hang the device */}
}
void Mem_Manage_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x4000000);
    
    while(1) {
        /* Hang the device */
    }
}
void Bus_Fault_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x5000000);
    while(1) {
        /* Hang the device */
    }
}
void Usage_Fault_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x6000000);
    while(1) {
        /* Hang the device */
    }
}
void Secure_Fault_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x7000000);
    while(1) {
        /* Hang the device */
    }
}
void SVC_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x8000000);
    while(1) {
        /* Hang the device */
    }
}
void Debug_Monitor_Handler(void) { 
    LL_CANARY_REGISTER_OR(0x9000000);
    while(1) {
        /* Hang the device */
    }
}
void Pend_Sv_Handler(void) { 
    LL_CANARY_REGISTER_OR(0xA000000);
    while(1) {
        /* Hang the device */
    }
}
void Sys_Tick_Handler(void) { 
    LL_CANARY_REGISTER_OR(0xB000000);
    while(1) {
        /* Hang the device */
    }
}

void Default_Handler(void) {
    LL_CANARY_REGISTER_OR(0x1000000);
    while(1) {
        /* Hang the device */
    }
}

void _entry(void) {
    /* Copy init values from text to data */
    extern uint32_t _la_data;
    uint32_t data_size = &_edata - &_sdata;
    uint8_t *data_dst = (uint8_t*)&_sdata; // RAM
    uint8_t *data_src = (uint8_t*)&_la_data; // ROM

    for(int i = 0 ; i < data_size ; i++)
    {
        *data_dst++ = *data_src++;
    }

    /* Clear the zero segment */
    for (int* bss_dst = &_sbss; bss_dst < &_ebss;) {
        *bss_dst++ = 0x00;
    }
    
    __libc_init_array();
    main();
}