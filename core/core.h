/**
 * Distributed cognitive systems design demo.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
 * Core functionality definition.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <setjmp.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ucontext.h>
#define _GNU_SOURCE
#include <fenv.h> /* kind of C99 specific */

#define MAP_SIZE 					1
#define MAPS_NUMBER 				6
#define RELAXATION_THRESHOLD        0.0001f
#define VERBOSE 					1
#define ETA                         0.02f

/* fusion maps network code */

/* network type */
enum
{
  MAP_1D = 1,
  MAP_2D,
  MAP_3D
};

/* cardinal number - number of relations in which a map is involved */
enum{
  LINK1 = 1,
  LINK2,
  LINK3
};

/* a map cell that contains data of a certain type */
typedef struct
{
  int type;			/* type of the cell, e.g. 1D, 2D, 3D */
  double *val;      /* value in a cell: e.g. 1 value (1D), 2 values (2D), 3 values (3D) */
} cell;

typedef struct
{
  int size;             /* map size, e.g. squared maps size*size */
  cell **cells;			/* cells that contain data representation */
} data;

/* a map definition that contains multiple cells ancoding a certain feature */
typedef struct
{
  int id;               /* numeric id unique for each map */
  int links;             /* number of relations in which the map is involved */
  data data;			/* the actual map data encapsuled */
} map;

/* globals */
/* maps in the net */
map M1, M2, M3, M4, M5, M6;
/* errors values */
double *E1, *E2, *E3, *E4, *E4, *E5, *E6;
/* error marking how close is a map to the good value */
double e1, e2, e3, e4, e5, e6;
/* for self-restarting the app */
sigjmp_buf jmpbuf;

/* random number generator */
double randomize();
/* initialize a map with size, state and type */
map init_map (int id, int sz, int tp, int lnk);
/* free an already allocated map */
void free_map (map in);

/* simple commands to manage the state of the network */
/* restart command for the network while paused */
void resume_network();
/* restart network from the initial state */
void restart_network();
/* stops the network by exiting the main loop */
void stop_network();
/* the other commands (e.g.: pause, quit) are already embedded in the slots from the analyzer GUI */
















