#include <stdint.h>

#define PERIPHERAL_START (0x40000000U)
#define PERIPHERAL_AHB1 (PERIPHERAL_START + 0x20000U)
#define PERIPHERAL_AHB2 (PERIPHERAL_START + 0x8000000U)
#define GPIOA (PERIPHERAL_AHB2)

typedef struct {
  uint32_t MODER;
  uint32_t OTYPER; 
  uint32_t OSPEEDR;
  uint32_t PUPDR;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t LCKR;
  uint32_t AFRL;
  uint32_t AFRH;
  uint32_t BRR;
} volatile GPIO;

#define PIN_SET ((uint32_t)1U)
#define PIN_UNSET ((uint32_t)0U)

#define PIN5 (1U << 5U)
#define PIN5_WIDTH2 (1U << 10U)

// ahbn clock enable register
#define RCC_START (PERIPHERAL_AHB1 + 0x1000U)
#define RCC_AHBENR ((volatile uint32_t*)(RCC_START + 0x14U))
#define ENABLE_RCC_GPIOA (1U << 17U)

void main() {
  *RCC_AHBENR |= ENABLE_RCC_GPIOA;

  GPIO *gpioa = (GPIO*)(PERIPHERAL_AHB2);
  gpioa->MODER |= PIN5_WIDTH2;

  // blink for a bit, then leave light on
    int counter = 0;
  while (1) {
    if (counter < 10) {
      gpioa->ODR ^= PIN5;
    } else {
      gpioa->ODR = PIN5;
    }

    for (uint32_t i = 0; i < 100000; i++);
    counter++;
  }
}
