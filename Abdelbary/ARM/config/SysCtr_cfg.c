
#include "SysCtr_cfg.h"
/*
 * configuration structure to be filled by the user */
str_sysCtrCfg_t str_sysCtlCfg =
{
     F_OSC_16MHZ,        /* crystal frequency */
     PIOSC,              /* source of clock to be used (internal, external...)*/
     SYS_CLK_FREQ_80_000 /* required system clock frequency */
};
