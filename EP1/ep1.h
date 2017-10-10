#ifndef EP_H
#define EP_H

#include <stdio.h> /* printf(), fscanf() */
#include <stdlib.h> /* malloc(), atoi(), exit() */

#include "process.h" /* Process, create_process() */
#include "RR.h" /* RR() */
#include "SJF.h" /* SJF() */
#include "PS.h" /* PS() */

extern int context;
extern int finished;

#endif /* EP_H */
