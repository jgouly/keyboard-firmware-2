#include "port.h"
#include "sim.h"
#define p_addr32(addr) (*(volatile uint32_t *)addr)

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern int main();

typedef void(isr_fn)();
extern "C" void default_isr() {}
extern "C" void reset_handler_isr();

#define INT(name) void name##_isr() __attribute__((weak, alias("default_isr")));
#include "interrupts.def"
#undef INT

// Provided by the linker.
extern uint32_t _estack;

__attribute__((section(".vectors"), used)) isr_fn *VectorFlash[] = {
    (isr_fn *)((unsigned long)&_estack), //  0 ARM: Initial Stack Pointer
    reset_handler_isr,
#define INT(name) name##_isr,
#include "interrupts.def"
#undef INT
};

__attribute__((section(".flashconfig"), used))
const uint8_t flashconfigbytes[16] = {
    // 8-byte Backdoor Key.
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // 4-byte FPROT.
    0xFF, 0xFF, 0xFF, 0xFF,
    // 2-bytes reserved.
    0xFF, 0xFF,
    // 1-byte FOPT.
    0xFF,
    // 1-byte FSEC.
    0xFF};

void disable_watchdog() { SIM_COPC = 0; }

extern "C" void reset_handler_isr() {
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
