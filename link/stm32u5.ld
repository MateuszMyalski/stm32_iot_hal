MEMORY {
  /* Bank 1 */
  ROM  (RX) : ORIGIN = 0x08000000, LENGTH = 1M
  /* Bank 2 */
  /* ROM  (RX) : ORIGIN = 0x08100000, LENGTH = 1M */

  /* NS - Secute-Non-Secure */
  /* SRAM 1, 2, 3 */
  RAM (RWX) : ORIGIN = 0x20000000, LENGTH = (192K + 64K + 512K)
  /* SRAM 4 */
  /* RAM (RWX) : ORIGIN = 0x28000000, LENGTH = 16K */

  /* NSC - Secute-Non-Secure callable */
  /* SRAM 1, 2, 3 */
  /* RAM (RWX) : ORIGIN = 0x30000000, LENGTH = (192K + 64K + 512K) */
  /* SRAM 4 */
  /* RAM (RWX) : ORIGIN = 0x38000000, LENGTH = 16K */
}

ENTRY(_entry);
 
SECTIONS
{  
  STACK_SIZE = 0x2000; /* 8 kB */

  .text :
  {
    . = ALIGN(4);
    _stext = .;
    KEEP(*(.init_vec)); /* Vector table */
    *(.text)            /* Program code */
    *(.text.*)          /* Program code */
    *(.rodata*)         /* Read-only data */
    *(.rodata.*)        /* Read-only data */
    . = ALIGN(4);
    _etext = .;
  } > ROM

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)           /* Read-write initialized data */
    *(.data.*)         /* Read-write initialized data */
    *(.ramtext)        /* "text" functions to run in ram */
    *(.ramtext.*)      /* "text" functions to run in ram */
    . = ALIGN(4);
    _edata = .;
  } > RAM AT> ROM

  .bss (NOLOAD):
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  .stack (NOLOAD):
  {
      . = ALIGN(8);
      . = . + STACK_SIZE;
      . = ALIGN(8);
      _estack = .;
  } > RAM

  . = ALIGN(4);
  end = .;
}
