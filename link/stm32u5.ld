MEMORY {
  FLASH   (RX) : ORIGIN = 0x08000000, LENGTH = 32K/* TODO */
  SRAM    (RWX) : ORIGIN = 0x20000000, LENGTH = 4K/* TODO */
  /* Add XIP, PSRAM */
}

ENTRY(handler_reset);
 
SECTIONS
{
  .text :
  {
    . = ALIGN(4);
    _text_end = .;
    __text_end__ = _text_end;

    KEEP(*(.init_vec));
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);

    _text_end = .;
    __text_end__ = _text_end;
  } > FLASH

  .data :
  {
    _data_begin = .;
    __data_begin__ = _data_begin;

    *(.data)
    *(.data*)
    . = ALIGN(4);
    
    _data_end = .;
    __data_end__ = _data_end;
  } > SRAM

  .bss :
  {
    _bss_begin = .;
    __bss_start__ = _bss_begin;

    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    
    _bss_end = .;
    __bss_end__ = _bss_end;
  } > SRAM

  _stack_size = 1024;
  _stack_end = ORIGIN(SRAM) + LENGTH(SRAM);
  _stack_begin = _stack_end - _stack_size;
  . = _stack_begin;
  ._stack :
  {
    . = . + _stack_size;
  } > SRAM
}
