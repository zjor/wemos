#include <stdio.h>
#include "fw/src/mgos.h"

enum mgos_app_init_result mgos_app_init(void) {
    printf("Hello from printf");
    LOG(LL_INFO, ("Hello from log"));
    return MGOS_APP_INIT_SUCCESS;
}
