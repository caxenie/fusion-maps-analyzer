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
#include <float.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ucontext.h>
#include <fenv.h>

#define _GNU_SOURCE

#define MAP_SIZE 	   	     1
#define MAPS_NUMBER 		     6
#define RELAXATION_THRESHOLD         0.00001f
#define VERBOSE 		     1
#define ETA                         0.0002
#define ETA12                        ETA//0.0002956f
#define ETA21                        ETA// 0.0002106f
#define ETA234                       ETA//0.0002884f
#define ETA432                       ETA//0.0002423f
#define ETA456                       ETA//0.0002576f
#define ETA654                       ETA//0.0002345f
#define ETA_EXT1                     ETA//0.0002343f
#define ETA_EXT2                     ETA//0.0002243f
#define ETA_EXT3                     ETA//0.0002143f
#define ETA_EXT4                     ETA//0.0002003f
#define ETA_EXT5                     ETA//0.0002023f
#define ETA_EXT6                     ETA//0.0002343f


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
/* compute the time interval for integration or derivation */
double compute_dt(struct timeval *difference,
             struct timeval *end_time,
             struct timeval *start_time
            );















