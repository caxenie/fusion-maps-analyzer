/**
 * Simple recurrent network that converges
 * so that each of the relations to be satisfied.
 * Core functionality implementation.
 */

#include "shared-data.h"

/* random number generator */
double
randomize ()
{
  return (double) rand () / (double) RAND_MAX;
}

/* initialize a map with size, state and type */
map
init_map (int id, int sz, int tp, int lnk)
{
  map in;
  in.id = id;
  in.links = lnk;
  in.data.size = sz;
  in.data.cells = (cell **) calloc (sz, sizeof (cell *));
  for (int i = 0; i < sz; i++)
    {
      in.data.cells[i] = (cell *) calloc (sz, sizeof (cell));
    }
  for (int i = 0; i < sz; i++)
    {
      for (int j = 0; j < sz; j++)
        {
          in.data.cells[i][j].type = tp;
          in.data.cells[i][j].val = (double *) calloc (tp, sizeof (double));
          for (int t = 0; t < tp; t++)
            {
              in.data.cells[i][j].val[0] = randomize ();
            }
        }
    }
  return in;
}

/* free an already allocated map */
void
free_map (map in)
{
  if (in.data.size == MAP_SIZE)
    {
      for (int i = 0; i < MAP_SIZE; i++)
        {
          for (int j = 0; j < MAP_SIZE; j++)
            {
              if (in.data.cells[i][j].val)
                free (in.data.cells[i][j].val);
            }
        }
      if (in.data.cells)
        free (in.data.cells);
    }
  else
    {
      if (in.data.cells[0][0].val)
        free (in.data.cells[0][0].val);
      if (in.data.cells)
        free (in.data.cells);
    }
}

/* simple commands to manage the state of the network */

/* restart command for the network while paused */
void 
resume_network()
{	
  fprintf(stderr, "\nCORE: NETWORK IS RESUMED - CONTEXT IS RESTORED\n");
  for(int i=0;i<MAP_SIZE;i++){
      for(int j=0;j<MAP_SIZE;j++){
          fprintf
              (stderr, "CORE: network state: M1: %f | M2 %f | M3 %f | M4 %f | M5 %f | M6 %f\n",
               M1.data.cells[i][j].val[0],
               M2.data.cells[i][j].val[0],
               M3.data.cells[i][j].val[0],
               M4.data.cells[i][j].val[0],
               M5.data.cells[i][j].val[0],
               M6.data.cells[i][j].val[0]);
        }
    }
  fprintf
      (stderr, "CORE: Errors: E1 = %lf | E2 = %lf - E2 = %lf | E3 = %lf | E4 = %lf - E4 = %lf | E5 = %lf | E6 = %lf \n",
       E1[0], E2[0], E2[1], E3[0], E4[0], E4[1], E5[0],
       E6[0]);
}

/* restart network from the initial state */
void 
restart_network()
{
  siglongjmp(jmpbuf, 2);
}

/* stops the network by exiting the main loop */
void 
stop_network()
{
  fprintf(stderr, "\nCORE: NETWORK IS STOPPED - CONTEXT IS DUMPED\n");
  for(int i=0;i<MAP_SIZE;i++){
      for(int j=0;j<MAP_SIZE;j++){
          fprintf
              (stderr, "CORE: network state: M1: %f | M2 %f | M3 %f | M4 %f | M5 %f | M6 %f\n",
               M1.data.cells[i][j].val[0],
               M2.data.cells[i][j].val[0],
               M3.data.cells[i][j].val[0],
               M4.data.cells[i][j].val[0],
               M5.data.cells[i][j].val[0],
               M6.data.cells[i][j].val[0]);
        }
    }
  fprintf
      (stderr, "CORE: Errors: E1 = %lf | E2 = %lf - E2 = %lf | E3 = %lf | E4 = %lf - E4 = %lf | E5 = %lf | E6 = %lf \n",
       E1[0], E2[0], E2[1], E3[0], E4[0], E4[1], E5[0],
       E6[0]);
  exit(0);
}

