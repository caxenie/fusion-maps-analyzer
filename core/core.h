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

#define MAP_SIZE 					 1
#define MAPS_NUMBER 				 6
#define RELAXATION_THRESHOLD         0.00001f
#define VERBOSE 					 1
#define ETA12                        0.0002956f
#define ETA21                        0.0002106f
#define ETA234                       0.0002884f
#define ETA432                       0.0002423f
#define ETA456                       0.0002576f
#define ETA654                       0.0002345f
#define ETA_EXT1                     0.0002343f
#define ETA_EXT2                     0.0002243f
#define ETA_EXT3                     0.0002143f
#define ETA_EXT4                     0.0002003f
#define ETA_EXT5                     0.0002023f
#define ETA_EXT6                     0.0002343f

#define TO_MS(x) ((double)x)/1000.0

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
/* compute the time interval for integration or derivation */
double compute_dt(struct timeval *difference, struct timeval *end_time, struct timeval *start_time);
