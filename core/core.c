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

/* dumps the memory saved log file to the disk */
int
dump_log_file(char *fname, struct log* buffer, int buffer_size)
{
  FILE *f = fopen(fname, "w+");
  if(f==NULL){
      fprintf(stderr, "CORE: Cannot open log file!\n");
      return 1;
    }
  for(int i=0;i<buffer_size;i++){
          for(int j=0;j<14;j++){
              fprintf(f, "%lf ", buffer[i].vals[j]);
            }
          fprintf(f, "%d\n", buffer[i].iter);
        }
  fclose(f);
  return 0;
}


/* stops the network by exiting the main loop */
void 
stop_network()
{
    //if(dump_log_file("fusion-analyzer-data.log", log_data, iter)==0){
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
   // }
    exit(0);
}

/* compute the time interval for integration or derivation */
double
compute_dt(struct timeval *difference,
                  struct timeval *end_time,
                  struct timeval *start_time
                  )
{
    struct timeval temp_diff;

    if(difference==NULL)
    {
        difference=&temp_diff;
    }

    difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
    difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

    /* Using while instead of if below makes the code slightly more robust. */

    while(difference->tv_usec<0)
    {
        difference->tv_usec+=1000000;
        difference->tv_sec -=1;
    }

    return ((double)(1000000*difference->tv_sec+
                     difference->tv_usec));

}


