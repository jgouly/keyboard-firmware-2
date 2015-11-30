#include "config.h"

ResultT scan(LayoutT l);

int app_main(LayoutT l) {
  int c = 0;
  while (1) {
    (void)scan(l);
    c++;
    /* do nothing */;
  }
while(1);
  //__builtin_unreachable();
  return 0;
}
