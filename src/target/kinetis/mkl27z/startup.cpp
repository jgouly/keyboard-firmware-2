#include "port.h"
#include "sim.h"
#define p_addr32(addr) (*(volatile uint32_t *)addr)

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern int main();

void disable_watchdog() { SIM_COPC = 0; }

extern "C" __attribute__((section(".startup"))) void reset_handler_isr() {
  disable_watchdog();

  // Enable the clock gating to all GPIO ports.
  SIM_SCGC5 = SIM_SCGC5_PORTA | SIM_SCGC5_PORTB | SIM_SCGC5_PORTC |
              SIM_SCGC5_PORTD | SIM_SCGC5_PORTE;

  // init LED
  /// red LED
  PORTC_PCR0 = PORT_PCR_MUX(1);
  GPIOC_PDDR |= (1 << 0);
  GPIOC_PSOR |= (1 << 0);

  PORTB_PCR19 = PORT_PCR_MUX(1);
  GPIOB_PDDR |= (1 << 19);
  GPIOB_PSOR |= (1 << 19);

  main();
  __builtin_unreachable();
}
