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
#define PORTE_PCR21 (*(volatile uint32_t *)0x4004D054) // Pin Control Register n
#define USB0_CLK_RECOVER_IRC_EN (*(volatile uint8_t *)0x40072144)
#define LPUART0_BAUD (*(volatile uint32_t *)0x40054000)
#define LPUART0_CTRL (*(volatile uint32_t *)0x40054008)
#define LPUART0_DATA (*(volatile uint32_t *)0x4005400C)
#define LPUART0_STAT (*(volatile uint32_t *)0x40054004)

#define MCG_C1 (*(volatile uint8_t *)0x40064000) // MCG Control 1 Register

enum LPUART_CLOCK { LPUART_CLOCK_LIRC, LPUART_CLOCK_USB };

enum LPUART_PIN_PAIR { LPUART0_PTA1_PTA2 };

class LPUARTBase {};

template <LPUART_CLOCK CLK> class LPUART : public LPUARTBase {};

// void lpuart_init_base() {

//}

template <LPUART_CLOCK CLK, LPUART_PIN_PAIR PAIR>
void lpuart_init(); // __attribute__((noinline));
// extern template
// void lpuart_init<LPUART_CLOCK_LIRC>();

/*
template<LPUART_CLOCK CLK>
void lpuart_init() {
  if (CLK == LPUART_CLOCK_LIRC) {
    MCG_C1 |= (1 << 1);
  }
  SIM_SCGC5 |= (1 << 20);
  // UART0_TX
  PORTA_PCR2 = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(2);
  // UART0_RX
  PORTA_PCR1 = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(2);

  //USB0_CLK_RECOVER_IRC_EN |= (1 << 1);
// to set clock
  if (CLK == LPUART_CLOCK_LIRC) {
    SIM_SOPT2 |= (3 << 26);
  } else {
    SIM_SOPT2 |= (1 << 26);
    SIM_SOPT2 &= ~(1 << 27);
  }

  LPUART0_BAUD = calculateBaud();

  LPUART0_CTRL |= (1 << 19);
}
*/

void lpuart0_putc(uint8_t c);

#if 0
template<>
void lpuart_init<LPUART_CLOCK_LIRC>() {
  MCG_C1 |= (1 << 1);
}
#endif
