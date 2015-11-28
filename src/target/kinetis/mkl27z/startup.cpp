typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#include "port.h"
#include "sim.h"
//#include "lpuart.h"
#include "lpuart0.h"
#define p_addr32(addr) (*(volatile uint32_t *)addr)

extern int main();

void disable_watchdog() { SIM_COPC = 0; }

void delay() __attribute__((noinline));
void delay() {
  for (int i = 0; i < 100000; ++i) {
    __asm("mov r0,r0");
  }
}

void copy_rom_to_ram() {
  extern uint32_t _etext;
  extern uint32_t _sdata;
  extern uint32_t _edata;
  extern uint32_t _sbss;
  extern uint32_t _ebss;

  uint32_t *src = &_etext;
  uint32_t *dest = &_sdata;
  // TODO: do this while the PLL is waiting to lock....
  while (dest < &_edata)
    *dest++ = *src++;
  dest = &_sbss;
  while (dest < &_ebss)
    *dest++ = 0;
}

#define SIM_SCGC4 p_addr32(0x40048034)
#define SIM_SCGC4_USBOTG ((uint32_t)0x00040000)  // USB Clock Gate Control
#define MCG_S (*(volatile uint8_t *)0x40064006)  // MCG Status Register
#define MCG_C1 (*(volatile uint8_t *)0x40064000) // MCG Control 1 Register
//#define USB0_CLK_RECOVER_IRC_EN (*(volatile uint8_t  *)0x40072144) // OSC
//Control Register
#define USB0_CLK_RECOVER_CTRL                                                  \
  (*(volatile uint8_t *)0x40072140)              // OSC Control Register
#define MCG_MC (*(volatile uint8_t *)0x40064018) // OSC Control Register
#define GPIOB_PTOR                                                             \
  (*(volatile uint32_t *)0x400FF04C) // Port Toggle Output Register
static void new_init_clocks() {
  // GPIOB_PTOR |= (1 << 19);
  USB0_CLK_RECOVER_IRC_EN |= (1 << 1);
  USB0_CLK_RECOVER_CTRL |= (1 << 7);
  MCG_MC |= (1 << 7);
  MCG_C1 &= ~((1 << 6) | (1 << 7));
  while ((MCG_S & 12) != 0)
    ;
  // GPIOB_PTOR |= (1 << 19);
}

extern "C" __attribute__((section(".startup"))) void reset_handler_isr() {
  disable_watchdog();
  // copy_rom_to_ram();
  // SIM_SCGC4 = SIM_SCGC4_USBOTG | 0xF0000030;
  // new_init_clocks();
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

#define SELECTED_LPUART_CLK LPUART_CLOCK_LIRC
#define SELECTED_LPUART_PAIR LPUART0_PTA1_PTA2
  lpuart_init<SELECTED_LPUART_CLK, SELECTED_LPUART_PAIR>();

  while (1) {
    lpuart0_putc('a');
    lpuart0_putc('b');
    lpuart0_putc('c');
    lpuart0_putc('e');
    lpuart0_putc('i');
    lpuart0_putc('0');
    lpuart0_putc('3');

#define GPIOC_PTOR                                                             \
  (*(volatile uint32_t *)0x400FF08C) // Port Toggle Output Register
#define GPIOB_PTOR                                                             \
  (*(volatile uint32_t *)0x400FF04C) // Port Toggle Output Register
    GPIOC_PTOR |= (1 << 0);
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();

    GPIOC_PTOR |= (1 << 0);
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();

    GPIOB_PTOR |= (1 << 19);
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();

    GPIOB_PTOR |= (1 << 19);
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
    delay();
  }

  main();
  __builtin_unreachable();
}
