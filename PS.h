#ifndef PS_H
#define PS_H

#include "process.h"
#include "heap.h"
#include <stdio.h> /* printf() */
#include <unistd.h> /* sleep() */
#include "timer.h"

void PS(Process *v, int size);

#endif /* PS_H */
