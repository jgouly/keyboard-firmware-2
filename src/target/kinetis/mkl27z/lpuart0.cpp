#include <stdint.h>
#include "sim.h"
#define p_addr32(addr) (*(volatile uint32_t *)addr)

#define SIM_SOPT2                                                              \
  (*(volatile uint32_t *)0x40048004) // System Options Register 2

#define PORTA_PCR1 (*(volatile uint32_t *)0x40049004) // Pin Control Register n
#define PORTA_PCR2 (*(volatile uint32_t *)0x40049008) // Pin Control Register n

#define PORTE_PCR20 (*(volatile uint32_t *)0x4004D050) // Pin Control Register n
#define PORT_PCR_SRE ((uint32_t)0x00000004)            // Slew Rate Enable
#define PORT_PCR_PE ((uint32_t)0x00000002)             // Pull Enable
#define PORT_PCR_DSE ((uint32_t)0x00000040)            // Drive Strength Enable
#define PORT_PCR_PS ((uint32_t)0x00000001)             // Pull Select
#define PORT_PCR_PFE ((uint32_t)0x00000010)            // Passive Filter Enable
#define PORT_PCR_MUX(n) ((uint32_t)(((n)&7) << 8))     // Pin Mux Control
#define PORTE_PCR21 (*(volatile uint32_t *)0x4004D054) // Pin Control Register n
#define USB0_CLK_RECOVER_IRC_EN (*(volatile uint8_t *)0x40072144)
#define LPUART0_BAUD (*(volatile uint32_t *)0x40054000)
#define LPUART0_CTRL (*(volatile uint32_t *)0x40054008)
#define LPUART0_DATA (*(volatile uint32_t *)0x4005400C)
#define LPUART0_STAT (*(volatile uint32_t *)0x40054004)

#define MCG_C1 (*(volatile uint8_t *)0x40064000) // MCG Control 1 Register

#define LIRC_LPUART 1
void lpuart0_init(void) {
#if LIRC_LPUART
  // lirc 2m
  MCG_C1 |= (1 << 1);
#endif
  SIM_SCGC5 |= (1 << 20);
  // UART0_TX
  PORTA_PCR2 = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(2);
  // UART0_RX
  PORTA_PCR1 = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(2);

// USB0_CLK_RECOVER_IRC_EN |= (1 << 1);
// to set clock
#if LIRC_LPUART
  SIM_SOPT2 |= (3 << 26);
#else
  SIM_SOPT2 |= (1 << 26);
  SIM_SOPT2 &= ~(1 << 27);
#endif

// baud clock / ((OSR+1) × SBR)
// clock = lirc, 2000000
// osr = default 16
// 9600 = 2000000 / (16 * SBR)
// SBR = 2000000 / (16 * 9600)
// LPUART0_BAUD |= 13;

// uint32_t sbr = (uint32_t)(((sourceClockInHz * 10)/(desiredBaudRate *
// kLPUART_OSR_Value)) + 5) / 10;
// sbr = (((2000000*10)/(19200 * 4)) + 5) / 10
// LPUART0_BAUD = (3 << 24) | 26;

// uint32_t sbr = (uint32_t)(((sourceClockInHz * 10)/(desiredBaudRate *
// kLPUART_OSR_Value)) + 5) / 10;
// sbr = (((2000000*10)/(9600 * 4)) + 5) / 10
#if LIRC_LPUART
  LPUART0_BAUD |= (3 << 24) | 52;
#else
  //(((48000000*10)/(9600 * 4)) + 5)/10
  // LPUART0_BAUD |= (3 << 24) | 1250;
  //(((48000000*10)/(9600 * 16)) + 5)/10
  LPUART0_BAUD |= 313;
#endif

  LPUART0_CTRL |= (1 << 19);
}

#define GPIOB_PTOR                                                             \
  (*(volatile uint32_t *)0x400FF04C) // Port Toggle Output Register
void lpuart0_putc(uint8_t c) {
  GPIOB_PTOR |= (1 << 19);
  while ((LPUART0_STAT & (1 << 22)) == 0)
    ;
  while ((LPUART0_STAT & (1 << 23)) == 0)
    ;
  LPUART0_DATA |= c;
  /*(LPUART0_CTRL &= ~(1 << 19);
  while (LPUART0_CTRL & (1 << 19)){
  GPIOB_PTOR |= (1 << 19);}
  LPUART0_CTRL |= (1 << 19);
  while ((LPUART0_STAT & (1 << 23)) == 0);*/
  GPIOB_PTOR |= (1 << 19);
}

void lpuart0_putch(uint8_t c) {
  lpuart0_putc('0');
  lpuart0_putc('b');
  lpuart0_putc(c & (1 << 7) ? '1' : '0');
  lpuart0_putc(c & (1 << 6) ? '1' : '0');
  lpuart0_putc(c & (1 << 5) ? '1' : '0');
  lpuart0_putc(c & (1 << 4) ? '1' : '0');
  lpuart0_putc(c & (1 << 3) ? '1' : '0');
  lpuart0_putc(c & (1 << 2) ? '1' : '0');
  lpuart0_putc(c & (1 << 1) ? '1' : '0');
  lpuart0_putc(c & (1 << 0) ? '1' : '0');
}
