#ifndef EP_H
#define EP_H

#include <stdio.h> /* printf(), fscanf() */
#include <stdlib.h> /* malloc(), atoi(), exit() */

#include "process.h" /* Process, create_process() */
#include "RR.h" /* RR() */
#include "SJF.h" /* SJF() */
#include "PS.h" /* PS() */

#define DEBUG 0
#define DEBUG_RR 0
#define DEBUG_SJF 0
#define DEBUG_PS 0

extern int context; 

#endif /* EP_H */
