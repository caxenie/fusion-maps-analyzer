/**
 * Simple recurrent network that converges
 * so that each of the relations to be satisfied.
 * Entry point.
 */

#include "data-engine.h"
#include "core.h"

short g_verbose = 0;

#define log_message(format,args...) \
    do{ \
    if(g_verbose) \
    fprintf(stderr,format,args); \
    } while(0);


/* entry point */
int
main (int argc, char **argv)
{
    /* register signals */
    signal(SIGCONT, resume_network);
    signal(SIGUSR1, restart_network);
    signal(SIGTERM, stop_network);

    /*initialize random number generator seed */
    srand (time (NULL));

    int rand_map = 0;
    int update_state[MAPS_NUM+1] = {0,0,0,0,0,0,0};

    /* map initialization */
    /* for the current setup we populate the neighbor list by hand */
    M1 = init_map (1, 1, MAP_1D, LINK1);
    M2 = init_map (2, 1, MAP_1D, LINK2);
    M3 = init_map (3, 1, MAP_1D, LINK1);
    M4 = init_map (4, 1, MAP_1D, LINK2);
    M5 = init_map (5, 1, MAP_1D, LINK1);
    M6 = init_map (6, 1, MAP_1D, LINK2);

    E1 = (double *) calloc (LINK1, sizeof (double));
    E2 = (double *) calloc (LINK2, sizeof (double));
    E3 = (double *) calloc (LINK1, sizeof (double));
    E4 = (double *) calloc (LINK2, sizeof (double));
    E5 = (double *) calloc (LINK1, sizeof (double));
    E6 = (double *) calloc (LINK1, sizeof (double));

    E1[0] = 0.0;
    E2[0] = 0.0;
    E2[1] = 0.0;
    E3[0] = 0.0;
    E4[0] = 0.0;
    E4[1] = 0.0;
    E5[0] = 0.0;
    E6[0] = 0.0;

    e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0, e6 = 0;

    double M1ant = 0.0f, M2ant = 0.0f, M3ant = 0.0f, M4ant = 0.0f, M5ant = 0.0f, M6ant = 0.0f;

    /* starts the data transfer engine */
    start_data_transfer_engine();

    /* some timing info */
    struct timespec start, stop;

    /* loop the network */
    while (1)
    {
        /* start time */
        if( clock_gettime( CLOCK_REALTIME , &start) == -1 ) {
              printf( "clock gettime" );
              exit( EXIT_FAILURE );
            }

        /* non local goto for self-restarting */
        if(sigsetjmp(jmpbuf, 2)) {
            fprintf(stderr, "\nCORE: RESTARTED NETWORK\n");
            srand (time (NULL));
            rand_map = 0;
            for(int i=0;i<MAPS_NUM+1;i++){
                    update_state[i] = 0;
            }
            M1 = init_map (1, 1, MAP_1D, LINK1);
            M2 = init_map (2, 1, MAP_1D, LINK2);
            M3 = init_map (3, 1, MAP_1D, LINK1);
            M4 = init_map (4, 1, MAP_1D, LINK2);
            M5 = init_map (5, 1, MAP_1D, LINK1);
            M6 = init_map (6, 1, MAP_1D, LINK1);

            E1[0] = 0.0; E2[0] = 0.0; E2[1] = 0.0; E3[0] = 0.0; E4[0] = 0.0; E4[1] = 0.0; E5[0] = 0.0; E6[0] = 0.0;
            e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0, e6 = 0;
            M1ant = 0.0f, M2ant = 0.0f, M3ant = 0.0f, M4ant = 0.0f, M5ant = 0.0f, M6ant = 0.0f;

        }

        /*
          The relationships hardcoded in the network:

            M2 = 3*M1
            M3 = M2*M4
            M4 = M5+2*M6

        */

        /* get a map from the net */
        rand_map = (rand () % (MAPS_NUMBER) + 1);

        if (rand_map == 1)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M1ant = %lf\n",
                                 M1ant);

                    M1.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M1.data.cells[i][j].val[0] +
                            2 / 3 * ETA * M2.data.cells[i][j].val[0]; // compute new value for the map

                    log_message
                            ("CORE: Updated Map  %d \n",
                             rand_map);
                    log_message ("CORE: M1 = %lf\n",
                                 M1.data.cells[i][j].val[0]); // just verbose

                    e1 = fabs(M1.data.cells[i][j].val[0] - M1ant); // update error

                    M1ant = M1.data.cells[i][j].val[0]; // update history

                    update_state[rand_map] = 1;
                }
            }
        }

        if (rand_map == 2)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M2ant = %lf\n",
                                 M2ant);

                    M2.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M2.data.cells[i][j].val[0] +
                            6 * ETA * M1.data.cells[i][j].val[0];
                    log_message
                            ("CORE: Updated Map  %d with respect tp R1 \n",
                             rand_map);
                    log_message ("CORE: M2 = %lf\n",
                                 M2.data.cells[i][j].val[0]);
                    M2.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M2.data.cells[i][j].val[0] +
                            2 * ETA * (M3.data.cells[i][j].val[0] /
                                       M4.data.cells[i][j].val[0]);
                    log_message
                            ("CORE: Updated Map  %d with respect to R2 \n",
                             rand_map);
                    log_message ("CORE: M2 = %lf\n",
                                 M2.data.cells[i][j].val[0]);


                    e2 = fabs(M2.data.cells[i][j].val[0] - M2ant);

                    M2ant = M2.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

        if (rand_map == 3)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M3ant = %lf\n",
                                 M3ant);

                    M3.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M3.data.cells[i][j].val[0] +
                            2 * ETA * M2.data.cells[i][j].val[0] *
                            M4.data.cells[i][j].val[0];

                    log_message
                            ("CORE: Updated Map  %d  \n",
                             rand_map);
                    log_message ("CORE: M3 = %lf\n",
                                 M3.data.cells[i][j].val[0]);

                    e3 = fabs(M3.data.cells[i][j].val[0] - M3ant);

                    M3ant = M3.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

        if (rand_map == 4)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M4ant = %lf\n",
                                 M4ant);

                    M4.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M4.data.cells[i][j].val[0] +
                            2 * ETA * (M3.data.cells[i][j].val[0] /
                                       M2.data.cells[i][j].val[0]);
                    log_message
                            ("CORE: Updated Map  %d with respect to R2 \n",
                             rand_map);
                    log_message ("CORE: M4 = %lf\n",
                                 M4.data.cells[i][j].val[0]);

                    M4.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M4.data.cells[i][j].val[0] +
                            2 * ETA * (M5.data.cells[i][j].val[0] +
                                       2 * M6.data.cells[i][j].val[0]);
                    log_message
                            ("CORE: Updated Map  %d with respect to R3 \n",
                             rand_map);
                    log_message ("CORE: M4 = %lf\n",
                                 M4.data.cells[i][j].val[0]);

                    e4 = fabs(M4.data.cells[i][j].val[0] - M4ant);

                    M4ant = M4.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

        if (rand_map == 5)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M5ant = %lf\n",
                                 M5ant);

                    M5.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M5.data.cells[i][j].val[0] -
                            2 * ETA * (2 * M6.data.cells[i][j].val[0] -
                                       M4.data.cells[i][j].val[0]);
                    log_message
                            ("CORE: Updated Map  %d  \n",
                             rand_map);
                    log_message ("CORE: M5 = %lf\n",
                                 M5.data.cells[i][j].val[0]);

                    e5 = fabs(M5.data.cells[i][j].val[0] - M5ant);

                    M5ant = M5.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

        if (rand_map == 6)
        {
            for (int i = 0; i < MAP_SIZE; i++)
            {
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    log_message ("CORE: Extracted map %d\n", rand_map);

                    log_message ("CORE: M6ant = %lf\n",
                                 M6ant);

                    M6.data.cells[i][j].val[0] =
                            (1 - 2 * ETA) * M6.data.cells[i][j].val[0] +
                            ETA *
                            ((M4.data.cells[i][j].val[0] -
                              M5.data.cells[i][j].val[0]));
                    log_message
                            ("CORE: Updated Map  %d \n",
                             rand_map);
                    log_message ("CORE: M6 = %lf\n",
                                 M6.data.cells[i][j].val[0]);

                    e6 = fabs(M6.data.cells[i][j].val[0] - M6ant);

                    M6ant = M6.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

         /* check for floating point exceptions and fix the representation */
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if(isnan(M1.data.cells[i][j].val[0])!=0) M1.data.cells[i][j].val[0] = 0.0000001;
                if(isnan(M2.data.cells[i][j].val[0])!=0) M2.data.cells[i][j].val[0] = 0.0000001;
                if(isnan(M3.data.cells[i][j].val[0])!=0) M3.data.cells[i][j].val[0] = 0.0000001;
                if(isnan(M4.data.cells[i][j].val[0])!=0) M4.data.cells[i][j].val[0] = 0.0000001;
                if(isnan(M5.data.cells[i][j].val[0])!=0) M5.data.cells[i][j].val[0] = 0.0000001;
                if(isnan(M6.data.cells[i][j].val[0])!=0) M6.data.cells[i][j].val[0] = 0.0000001;

                if(isinf(M1.data.cells[i][j].val[0])!=0) M1.data.cells[i][j].val[0] = 1.0000001;
                if(isinf(M2.data.cells[i][j].val[0])!=0) M2.data.cells[i][j].val[0] = 1.0000001;
                if(isinf(M3.data.cells[i][j].val[0])!=0) M3.data.cells[i][j].val[0] = 1.0000001;
                if(isinf(M4.data.cells[i][j].val[0])!=0) M4.data.cells[i][j].val[0] = 1.0000001;
                if(isinf(M5.data.cells[i][j].val[0])!=0) M5.data.cells[i][j].val[0] = 1.0000001;
                if(isinf(M6.data.cells[i][j].val[0])!=0) M6.data.cells[i][j].val[0] = 1.0000001;
            }
        }

        log_message
                ("\nCORE: Errors: E1 = %lf | E2 = %lf | E3 = %lf | E4 = %lf | E5 = %lf | E6 = %lf \n",
                e1, e2, e3, e4, e5, e6);

        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {

                log_message("\nCORE: maps state M1: %f | M2 %f | M3 %f | M4 %f | M5 %f | M6 %f\n",
                            M1.data.cells[i][j].val[0],
                            M2.data.cells[i][j].val[0],
                            M3.data.cells[i][j].val[0],
                            M4.data.cells[i][j].val[0],
                            M5.data.cells[i][j].val[0],
                            M6.data.cells[i][j].val[0]);

                // errors with respect to the relationships in which each map is involved
                E1[0] = pow(M1.data.cells[i][j].val[0]-1/3*M2.data.cells[i][j].val[0], 2);
                E2[0] = pow(M2.data.cells[i][j].val[0]-3*M1.data.cells[i][j].val[0], 2);
                E2[1] = pow(M2.data.cells[i][j].val[0]-M3.data.cells[i][j].val[0]/M4.data.cells[i][j].val[0], 2);
                E3[0] = pow(M3.data.cells[i][j].val[0]-M2.data.cells[i][j].val[0]*M4.data.cells[i][j].val[0], 2);
                E4[0] = pow(M4.data.cells[i][j].val[0]-M3.data.cells[i][j].val[0]/M2.data.cells[i][j].val[0], 2);
                E4[1] = pow(M4.data.cells[i][j].val[0]-M5.data.cells[i][j].val[0] - 2*M6.data.cells[i][j].val[0], 2);
                E5[0] = pow(M5.data.cells[i][j].val[0]-M4.data.cells[i][j].val[0] - 2*M6.data.cells[i][j].val[0], 2);
                E6[0] = pow(M6.data.cells[i][j].val[0]-(M4.data.cells[i][j].val[0]-M5.data.cells[i][j].val[0])/2, 2);

            }

        }

        log_message
                ("===================================================================%s\n",
                 "=");
        /* check network state */
        if(update_state[1] == 1  && update_state[2] == 1 && update_state[3] == 1 && update_state[4] == 1 && update_state[5] == 1 && update_state[6] == 1){

            if (e1 <= RELAXATION_THRESHOLD && e2 <= RELAXATION_THRESHOLD && e3 <= RELAXATION_THRESHOLD &&
                    e4 <= RELAXATION_THRESHOLD && e5 <= RELAXATION_THRESHOLD && e6 <= RELAXATION_THRESHOLD)
            {
                for(int i = 0; i< MAPS_NUM+1;i++) update_state[i] = 0;

                for (int i = 0; i < MAP_SIZE; i++)
                {
                    for (int j = 0; j < MAP_SIZE; j++)
                    {
                        fprintf
                                (stderr,"===========================================\n");
                        fprintf
                                (stderr,"CORE: network relaxed: M1: %f | M2 %f | M3 %f | M4 %f | M5 %f | M6 %f\n",
                                 M1.data.cells[i][j].val[0],
                                 M2.data.cells[i][j].val[0],
                                 M3.data.cells[i][j].val[0],
                                 M4.data.cells[i][j].val[0],
                                 M5.data.cells[i][j].val[0],
                                 M6.data.cells[i][j].val[0]);

                    }
                }

            }
        }

        // sync with analyzer
        usleep(SYNC_DATA);

        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
          perror( "clock gettime" );
          exit( EXIT_FAILURE );
        }

        log_message("Loop time: %f ms\n",(double) (stop.tv_nsec-start.tv_nsec)/1000000); // get time in ms

    }
    return 0;
}
