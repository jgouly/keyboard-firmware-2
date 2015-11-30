
typedef unsigned int uint32_t;
#define GPIOE_PDIR                                                             \
  (*(volatile uint32_t *)0x400FF110) // Port Data Input Register
#define GPIOC_PDIR                                                             \
  (*(volatile uint32_t *)0x400FF090) // Port Data Input Register

class MKL27ZInputPin {
public:
  MKL27ZInputPin(unsigned N) : Num(N) {}

  unsigned readInput() const {
    switch (Num) {
    case 0:
      return (GPIOE_PDIR & (1 << 23) ? 1 : 0);
      break;
    case 1:
      return (GPIOC_PDIR & (1 << 9) ? 1 : 0);
      break;
    }
  }

private:
  unsigned Num;
};
