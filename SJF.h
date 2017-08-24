#ifndef SJF_H
#define SJF_H

#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <unistd.h>
#include "ep.h"
#include <time.h>
#include "heap.h"

void SJF(Process *v, int size);

#endif
