#ifndef KEY_H
#define KEY_H
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "IMX6.h"

void key_init(void);
int read_key(void);
int key_get_value(void);

#endif