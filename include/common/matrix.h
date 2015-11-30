#ifndef COMMON_MATRIX_H
#define COMMON_MATRIX_H
void lpuart0_putc(unsigned char);
void lpuart0_putch(unsigned char);
template <typename T, int Rows, int Columns> class Matrix {
public:
  void put(unsigned C, unsigned R, unsigned NC, unsigned val) {
    data[C + (R * Columns)] = val;
  }

  void dump() {
    for (unsigned c = 0; c < Columns; ++c) {
      for (unsigned r = 0; r < Rows; ++r) {
        lpuart0_putc('c');
        lpuart0_putch(c);
        lpuart0_putc('r');
        lpuart0_putch(r);
        lpuart0_putc('=');
        lpuart0_putch(data[c + (r * Columns)]);
        lpuart0_putc('\r');
        lpuart0_putc('\n');
      }
    }
  }

private:
  T data[Rows * Columns];
};
#endif
