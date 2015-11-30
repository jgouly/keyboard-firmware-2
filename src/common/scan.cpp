#include "config.h"
//#include <cstdio>

extern void delay();

void lpuart0_putc(unsigned char);
void lpuart0_putch(unsigned char);
ResultT scan(LayoutT l) {
  ResultT result = l.createResultMatrix();
  for (unsigned C = 0; C < l.getNumColumns(); ++C) {
    const auto &columnPin = l.getColumnPin(C);
    columnPin.outputHigh();
    //    printf("\n");
    for (unsigned R = 0; R < l.getNumRows(); ++R) {
      // printf("scanning %d %d\n", R, C);
      const auto &rowPin = l.getRowPin(R);
      unsigned val = rowPin.readInput();
      //delay();
      if (val && rowPin.readInput()) {
       // lpuart0_putc('a');
        result.put(C, R, l.getNumColumns(), 1);
      }
    }
    columnPin.outputLow();
  }
  result.dump();
  return result;
}
