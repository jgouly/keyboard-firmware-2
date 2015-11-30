#include <cstdio>

#include "config.h"

extern int app_main(LayoutT);

int main(void) {
  LayoutT m;
  m.reconfigure(10, 2);
  printf("m[%d][%d]\n", m.getNumRows(), m.getNumColumns());
  // app_main(m);
  m.reconfigure(2, 3);
  printf("m[%d][%d]\n", m.getNumRows(), m.getNumColumns());
  app_main(m);
  return 0;
}
