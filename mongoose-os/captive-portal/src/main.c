#include <stdio.h>
#include "fw/src/mgos.h"

enum mgos_app_init_result mgos_app_init(void) {
  printf("Hello world from my firmware");
  return MGOS_APP_INIT_SUCCESS;
}
