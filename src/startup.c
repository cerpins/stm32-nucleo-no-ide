#include <stdint.h>

#define SRAM_START (0x20000000U)
#define SRAM_SIZE (16U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
// last address, stack goes down and heap goes up in SRAM
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

void reset_handler(void);
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hardfault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));

#define ISR_VECTOR_SIZE_WORDS (47)
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
  STACK_POINTER_INIT_ADDRESS,
  (uint32_t)&reset_handler,
  (uint32_t)&nmi_handler,
  (uint32_t)&hardfault_handler,
  (uint32_t)&svcall_handler,
  (uint32_t)&pendsv_handler,
  (uint32_t)&systick_handler,
  // ... add remaining handlers
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

void main(void);

void default_handler(void) {
  while(1);
}

void reset_handler(void) {
  // grab data size of .data section
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  // start of flash .data region
  uint8_t *flash_data = (uint8_t*) &_etext;
  // start of ram region
  uint8_t *sram_data = (uint8_t*) &_sdata;

  for (uint32_t i = 0; i < data_size; i++) {
    sram_data[i] = flash_data[i];
  }

  // zero fill .bss
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i< bss_size; i++) {
    bss[i] = 0;
  }
  
  main();
}
