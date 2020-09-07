#ifndef IRQ_H
#define IRQ_H

#include "types.h"

bool irq_disable(void);
void irq_enable(bool enable);

#endif
