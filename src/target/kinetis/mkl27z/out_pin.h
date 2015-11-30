typedef unsigned int uint32_t;
#define GPIOD_PSOR                                                             \
  (*(volatile uint32_t *)0x400FF0C4) // Port Set Output Register
#define GPIOB_PSOR                                                             \
  (*(volatile uint32_t *)0x400FF044) // Port Set Output Register
#define GPIOD_PCOR (*(volatile uint32_t *)0x400FF0C8)
#define GPIOB_PCOR (*(volatile uint32_t *)0x400FF048)

class MKL27ZOutputPin {
public:
  MKL27ZOutputPin(unsigned N) : Num(N) {}
  void outputHigh() const {
    switch (Num) {
    case 0:
      GPIOD_PSOR |= (1 << 7);
      break;
    case 1:
      GPIOD_PSOR |= (1 << 0);
      break;
    case 2:
      GPIOB_PSOR |= (1 << 1);
      break;
    }
  }

  void outputLow() const {
    switch (Num) {
    case 0:
      GPIOD_PCOR |= (1 << 7);
      break;
    case 1:
      GPIOD_PCOR |= (1 << 0);
      break;
    case 2:
      GPIOB_PCOR |= (1 << 1);
      break;
    }
  }

private:
  unsigned Num;
};
