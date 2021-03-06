/**
 * Distributed cognitive systems design demo.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
 * Entry point.
 */

#include "shared-data.h"

pthread_mutex_t net_data_mutex = PTHREAD_MUTEX_INITIALIZER;

short g_verbose = 0;

#define log_message(format,args...) \
    do{ \
    if(g_verbose) \
    fprintf(stderr,format,args); \
    } while(0);

/* entry point */
int
main (int UNUSED(argc), char** UNUSED(argv))
{
#ifdef VERBOSE
    FILE *f = fopen("fusion-analyzer-data.log","w+");
    long timer = 0;
    /* logging utils */
    iter = 0;
    log_data = (struct log*)calloc(1, sizeof(struct log));
#endif
  /* register signals */
  signal(SIGCONT, resume_network);
  signal(SIGUSR1, restart_network);
  signal(SIGTERM, stop_network);

  /*initialize random number generator seed */
  srand (time (NULL));

    int rand_edge = 0;
    int edges = 14;
    int rand_map = 0;

  /* map initialization */
  /* for the current setup we populate the neighbor list by hand */
  M1 = init_map (1, 1, MAP_1D, LINK2);
  M2 = init_map (2, 1, MAP_1D, LINK3);
  M3 = init_map (3, 1, MAP_1D, LINK2);
  M4 = init_map (4, 1, MAP_1D, LINK3);
  M5 = init_map (5, 1, MAP_1D, LINK2);
  M6 = init_map (6, 1, MAP_1D, LINK2);

  E1 = (double *) calloc (LINK1, sizeof (double));
  E2 = (double *) calloc (LINK2, sizeof (double));
  E3 = (double *) calloc (LINK1, sizeof (double));
  E4 = (double *) calloc (LINK2, sizeof (double));
  E5 = (double *) calloc (LINK1, sizeof (double));
  E6 = (double *) calloc (LINK1, sizeof (double));

  E1[0] = 0.0; E2[0] = 0.0; E2[1] = 0.0;E3[0] = 0.0;
  E4[0] = 0.0; E4[1] = 0.0; E5[0] = 0.0;E6[0] = 0.0;

  e1 = 0; e2 = 0; e3 = 0; e4 = 0; e5 = 0; e6 = 0;

  double M1ant = 0.0f, M2ant = 0.0f, M3ant = 0.0f, M4ant = 0.0f, M5ant = 0.0f, M6ant = 0.0f;

  // initialize map connections to user/sensor
  for(int i=0;i<MAPS_NUM+1;i++){
      user_connected[i] = 0;
      sensor_connected[i] = 0;
    }

  /* starts the data transfer engine */
  start_data_transfer_engine();

    /* loop the network */
    while (1)
    {
        /* non local goto for self-restarting */
        if(sigsetjmp(jmpbuf, 2)) {
            fprintf(stderr, "\nCORE: RESTARTED NETWORK\n");
            srand (time (NULL));
            rand_map = 0;
            rand_edge = 0;
            pthread_mutex_lock(&net_data_mutex);
            for(int i=0;i<MAPS_NUM+1;i++){
                user_connected[i] = 0;
                sensor_connected[i] = 0;
            }
          M1 = init_map (1, 1, MAP_1D, LINK2);
          M2 = init_map (2, 1, MAP_1D, LINK3);
          M3 = init_map (3, 1, MAP_1D, LINK2);
          M4 = init_map (4, 1, MAP_1D, LINK3);
          M5 = init_map (5, 1, MAP_1D, LINK2);
          M6 = init_map (6, 1, MAP_1D, LINK2);

          E1[0] = 0.0; E2[0] = 0.0; E2[1] = 0.0; E3[0] = 0.0; E4[0] = 0.0; E4[1] = 0.0; E5[0] = 0.0; E6[0] = 0.0;
          e1 = 0; e2 = 0; e3 = 0; e4 = 0; e5 = 0; e6 = 0;
          M1ant = 0.0f; M2ant = 0.0f; M3ant = 0.0f; M4ant = 0.0f; M5ant = 0.0f; M6ant = 0.0f;

        }

        pthread_mutex_lock(&net_data_mutex);

        /*
          The relationships hardcoded in the network:

          M2 = 5*pow(M1,2);
          M3 = atan(M2) - 4*pow(M4, 2);
          M4 = 8*atan(M5) + pow(M6, 2)

        */

      /* get a map from the net */


      rand_map = (rand () % (MAPS_NUMBER) + 1);


      if (rand_map == M1.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M1.links) + 1);

                  if(rand_edge==1){
                      M1.data.cells[i][j].val[0] = (1.0 - 2.0*ETA)*M1.data.cells[i][j].val[0] +
                              2.0*ETA*sqrt(fabs(M2.data.cells[i][j].val[0])/5.0);
                    }
                  if(rand_edge==2){
                      if(user_connected[rand_map] == 1){
                          M1.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT1) * M1.data.cells[i][j].val[0] +
                              2.0*ETA_EXT1*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M1.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT1) * M1.data.cells[i][j].val[0] +
                              2.0*ETA_EXT1*sensor_data[rand_map];
                        }
                    }

                  e1 = fabs(M1.data.cells[i][j].val[0] - M1ant); // update error

                  M1ant = M1.data.cells[i][j].val[0]; // update history

               }
            }
        }

      if (rand_map == M2.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M2.links) + 1);

                  if(rand_edge==1){
                              M2.data.cells[i][j].val[0] =
                                  (1.0 - 2.0 * ETA12) * M2.data.cells[i][j].val[0] +
                                  10.0 * ETA12 * pow(M1.data.cells[i][j].val[0], 2);
                    }

                  if(rand_edge==2){
                      M2.data.cells[i][j].val[0] = (1.0 - 2.0*ETA)*M2.data.cells[i][j].val[0]+
                              2.0*ETA*tan(M3.data.cells[i][j].val[0] + 4.0*pow(M4.data.cells[i][j].val[0], 2));
                    }

                  if(rand_edge==3){
                      if(user_connected[rand_map] == 1){
                          M2.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT2) * M2.data.cells[i][j].val[0] +
                              2.0*ETA_EXT2*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M2.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT2) * M2.data.cells[i][j].val[0] +
                              2.0*ETA_EXT2*sensor_data[rand_map];
                        }
                    }

                  e2 = fabs(M2.data.cells[i][j].val[0] - M2ant);

                  M2ant = M2.data.cells[i][j].val[0];
                }
            }
        }

      if (rand_map == M3.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M3.links) + 1);

                  if(rand_edge==1){
                      M3.data.cells[i][j].val[0] =
                                          (1.0 - 2.0 * ETA432) * M3.data.cells[i][j].val[0] +
                                              2.0 * ETA*(atan(M2.data.cells[i][j].val[0]) - 4.0*pow(M4.data.cells[i][j].val[0] , 2));
                    }

                  if(rand_edge==2){
                      if(user_connected[rand_map] == 1){
                          M3.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT3) * M3.data.cells[i][j].val[0] +
                              2.0*ETA_EXT3*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M3.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT3) * M3.data.cells[i][j].val[0] +
                              2.0*ETA_EXT3*sensor_data[rand_map];
                        }
                    }

                  e3 = fabs(M3.data.cells[i][j].val[0] - M3ant);

                  M3ant = M3.data.cells[i][j].val[0];
                }
            }
        }

      if (rand_map == M4.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M4.links) + 1);

                  if(rand_edge==1){
                      M4.data.cells[i][j].val[0] = (1.0 - 2.0*ETA)*M4.data.cells[i][j].val[0]+
                              2.0*ETA*sqrt(fabs((atan(M2.data.cells[i][j].val[0]) - M3.data.cells[i][j].val[0]))/4.0);

                    }

                  if(rand_edge==2){
                      M4.data.cells[i][j].val[0] = (1.0-2.0*ETA654)*M4.data.cells[i][j].val[0] +
                              2.0*ETA*(8.0*atan(M5.data.cells[i][j].val[0]) + pow( M6.data.cells[i][j].val[0], 2));
                    }

                  if(rand_edge==3){
                      if(user_connected[rand_map] == 1){
                          M4.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT4) * M4.data.cells[i][j].val[0] +
                              2.0*ETA_EXT4*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M4.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT4) * M4.data.cells[i][j].val[0] +
                              2.0*ETA_EXT4*sensor_data[rand_map];
                        }
                    }

                  e4 = fabs(M4.data.cells[i][j].val[0] - M4ant);

                  M4ant = M4.data.cells[i][j].val[0];
                }
            }
        }

      if (rand_map == M5.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M5.links) + 1);

                  if(rand_edge==1){
                      M5.data.cells[i][j].val[0] = (1.0 - 2.0*ETA)*M5.data.cells[i][j].val[0] +
                                                2.0*ETA*tan((M4.data.cells[i][j].val[0] - pow(M6.data.cells[i][j].val[0], 2))/8.0);


                    }

                  if(rand_edge==2){
                      if(user_connected[rand_map] == 1){
                          M5.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT5) * M5.data.cells[i][j].val[0] +
                              2.0*ETA_EXT5*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M5.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT5) * M5.data.cells[i][j].val[0] +
                              2.0*ETA_EXT5*sensor_data[rand_map];
                        }
                    }

                  e5 = fabs(M5.data.cells[i][j].val[0] - M5ant);

                  M5ant = M5.data.cells[i][j].val[0];

                }
            }
        }

      if (rand_map == M6.id)
        {
          for (int i = 0; i < MAP_SIZE; i++)
            {
              for (int j = 0; j < MAP_SIZE; j++)
                {
                  rand_edge = (rand() % (M6.links) + 1);

                  if(rand_edge==1){
                      M6.data.cells[i][j].val[0] =  (1.0 - 2.0*ETA)*M6.data.cells[i][j].val[0] +
                              2.0*ETA*sqrt(fabs(M4.data.cells[i][j].val[0] - 8.0*atan(M5.data.cells[i][j].val[0])));

                    }

                  if(rand_edge==2){
                      if(user_connected[rand_map] == 1){
                          M6.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT6) * M6.data.cells[i][j].val[0] +
                              2.0*ETA_EXT6*user_data[rand_map];
                        }
                      if(sensor_connected[rand_map] == 1){
                          M6.data.cells[i][j].val[0] = (1.0-2.0*ETA_EXT6) * M6.data.cells[i][j].val[0] +
                              2.0*ETA_EXT6*sensor_data[rand_map];
                        }
                    }

                  e6 = fabs(M6.data.cells[i][j].val[0] - M6ant);

                  M6ant = M6.data.cells[i][j].val[0];

                }
            }
        }

      for (int i = 0; i < MAP_SIZE; i++)
        {
          for (int j = 0; j < MAP_SIZE; j++)
            {

              // full errors
              // Map 1 with respect to R12
              if(isnan(E1[0] = M1.data.cells[i][j].val[0]-sqrt(M2.data.cells[i][j].val[0]/5.0))!=0) E1[0] = 0.0f;
              E1[0] = fabs(E1[0]);
              // Map 2 with  respect to R12 and R34
              if(isnan(E2[0] = M2.data.cells[i][j].val[0]-5.0*pow(M1.data.cells[i][j].val[0], 2))!=0) E2[0] = 0.0f;
              E2[0] = fabs(E2[0]);
              if(isnan(E2[1] = M2.data.cells[i][j].val[0]- tan(M3.data.cells[i][j].val[0] + 4.0*pow(M4.data.cells[i][j].val[0], 2)))!=0) E2[1] = 0.0f;
              E2[1] = fabs(E2[1]);
              // Map 3 with respect to R34
              if(isnan(E3[0] = M3.data.cells[i][j].val[0]-atan(M2.data.cells[i][j].val[0]) + 4*pow(M4.data.cells[i][j].val[0], 2))!=0) E3[0] = 0.0f;
              E3[0] = fabs(E3[0]);
              // Map 4 with  respect to R34 and R56
              if(isnan(E4[0] = M4.data.cells[i][j].val[0]-sqrt((atan(M2.data.cells[i][j].val[0]) - M3.data.cells[i][j].val[0])/4.0))!=0) E4[0] = 0.0f;
              E4[0] = fabs(E4[0]);
              if(isnan(E4[1] = M4.data.cells[i][j].val[0]-(8.0*atan(fabs(M5.data.cells[i][j].val[0])) + pow(M6.data.cells[i][j].val[0], 2)))!=0) E4[1] = 0.0f;
              E4[1] = fabs(E4[1]);
              // Map 5 with respect to R56
              if(isnan(E5[0] = M5.data.cells[i][j].val[0]-tan(((M4.data.cells[i][j].val[0] - pow(M6.data.cells[i][j].val[0], 2))/8.0)))!=0) E5[0] = 0.0f;
              E5[0] = fabs(E5[0]);
              // Map 6 with respect to R56
              if(isnan(E6[0] = M6.data.cells[i][j].val[0]-sqrt(M4.data.cells[i][j].val[0]-8.0*atan(M5.data.cells[i][j].val[0])))!=0) E6[0] =  0.0f;
              E6[0] = fabs(E6[0]);
            }

        }
#ifdef VERBOSE  
	if(timer%SAMPLE_TIME==0){      
	log_data->iter=iter;
        log_data->vals[0] = M1.data.cells[0][0].val[0];
        log_data->vals[1] = M2.data.cells[0][0].val[0];
        log_data->vals[2] = M3.data.cells[0][0].val[0];
        log_data->vals[3] = M4.data.cells[0][0].val[0];
        log_data->vals[4] = M5.data.cells[0][0].val[0];
        log_data->vals[5] = M6.data.cells[0][0].val[0];
        log_data->vals[6] = E1[0];
        log_data->vals[7] = E2[0];
        log_data->vals[8] = E2[1];
        log_data->vals[9] = E3[0];
        log_data->vals[10] = E4[0];
        log_data->vals[11] = E4[1];
        log_data->vals[12] = E5[0];
        log_data->vals[13] = E6[0];
	iter++;
	dump_log_data(f, log_data);
	}
	timer++;
#endif
        pthread_mutex_unlock(&net_data_mutex);
    }
#ifdef VERBOSE 
   fclose(f);
#endif
    return 0;
}
