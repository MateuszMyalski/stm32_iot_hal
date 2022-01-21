MEMORY {
  ROM_BANK1  (RX) : ORIGIN = 0x08000000, LENGTH = 1M
  ROM_BANK2  (RX) : ORIGIN = 0x08100000, LENGTH = 1M

  /* NS - Secute-Non-Secure */
  NS_SRAM1 (RWX) : ORIGIN = 0x20000000, LENGTH = (192K + 64K + 512K)
  NS_SRAM4 (RWX) : ORIGIN = 0x28000000, LENGTH = 16K

  /* NSC - Secute-Non-Secure callable */
  NSC_SRAM1 (RWX) : ORIGIN = 0x30000000, LENGTH = (192K + 64K + 512K)
  NSC_SRAM4 (RWX) : ORIGIN = 0x38000000, LENGTH = 16K 
}

ENTRY(handler_reset);
 
SECTIONS
{
  .text :
  {
    . = ALIGN(4);

    KEEP(*(.init_vec)); /* Vector table */

    *(.text*)           /* Program code */
    . = ALIGN(4);

    *(.rodata*)         /* Read-only data */
    . = ALIGN(4);
  } > ROM_BANK1

  .data :
  {
    *(.data*)          /* Read-write initialized data */
    *(.ramtext*)       /* "text" functions to run in ram */
    . = ALIGN(4);
    
    __data_end__ = .;
  } > NS_SRAM1

  .bss :
  {
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    
    __bss_end__  = .;
  } > NS_SRAM1

  . = ALIGN(4);
  end = .;
}

PROVIDE(__stack_end__ = ORIGIN(NS_SRAM1) + LENGTH(NS_SRAM1));
