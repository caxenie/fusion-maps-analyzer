/**
 * Distributed cognitive systems design demo.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
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

/* file logging support */
FILE *f;
char* log_bufferw;
long timer;

/* entry point */
int
main (int argc, char *argv[])
{
    f = fopen("fusion-analyzer-data.log","w+");
    log_bufferw = (char*)calloc(20000, sizeof(char));
    timer = 0;
    /* register signals */
    signal(SIGCONT, resume_network);
    signal(SIGUSR1, restart_network);
    signal(SIGTERM, stop_network);

    /*initialize random number generator seed */
    srand (time (NULL));

    int rand_edge = 0;
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

    // initialize map connections to user/sensor
    for(int i=0;i<MAPS_NUM+1;i++){
        update_state[i] = 0;
        user_connected[i] = 0;
        sensor_connected[i] = 0;
    }

    /* starts the data transfer engine */
    start_data_transfer_engine();

    /* some timing info */
    struct timespec start, stop;

    /* loop the network */
    while (1)
    {
        /* start time */
        if( clock_gettime( CLOCK_REALTIME , &start) == -1 ) {
            exit( EXIT_FAILURE );
        }

        /* non local goto for self-restarting */
        if(sigsetjmp(jmpbuf, 2)) {
            fprintf(stderr, "\nCORE: RESTARTED NETWORK\n");
            srand (time (NULL));
            rand_map = 0;
            rand_edge = 0;
            for(int i=0;i<MAPS_NUM+1;i++){
                update_state[i] = 0;
                user_connected[i] = 0;
                sensor_connected[i] = 0;
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
                    rand_edge = (rand() % (M1.links+1) + 1);

                    if(rand_edge==1){
                        M1.data.cells[i][j].val[0] =
                                (1 - 18 * ETA21) * M1.data.cells[i][j].val[0] +
                                6 * ETA21 * M2.data.cells[i][j].val[0]; // compute new value for the map
                    }

                    if(rand_edge==2){
                        if(user_connected[rand_map] == 1){
                            M1.data.cells[i][j].val[0] = (1-2*ETA_EXT1) * M1.data.cells[i][j].val[0] +
                                    2*ETA_EXT1*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M1.data.cells[i][j].val[0] = (1-2*ETA_EXT1) * M1.data.cells[i][j].val[0] +
                                    2*ETA_EXT1*sensor_data[rand_map];
                        }
                    }

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
                    rand_edge = (rand() % (M2.links+1) + 1);

                   if(rand_edge==1){
                        M2.data.cells[i][j].val[0] =
                                (1 - 2 * ETA12) * M2.data.cells[i][j].val[0] +
                                6 * ETA12 * M1.data.cells[i][j].val[0];
                    }

                    if(rand_edge==2){
                        M2.data.cells[i][j].val[0] =
                                (1 - 2 * ETA432 * pow(M4.data.cells[i][j].val[0],2) ) * M2.data.cells[i][j].val[0] +
                                2 * ETA432*M3.data.cells[i][j].val[0]*M4.data.cells[i][j].val[0];
                    }

                    if(rand_edge==3){
                        if(user_connected[rand_map] == 1){
                            M2.data.cells[i][j].val[0] = (1-2*ETA_EXT2) * M2.data.cells[i][j].val[0] +
                                    2*ETA_EXT2*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M2.data.cells[i][j].val[0] = (1-2*ETA_EXT2) * M2.data.cells[i][j].val[0] +
                                    2*ETA_EXT2*sensor_data[rand_map];
                        }
                    }

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
                    rand_edge = (rand() % (M3.links+1) + 1);

                    if(rand_edge==1){
                        M3.data.cells[i][j].val[0] =
                                (1 - 2 * ETA432) * M3.data.cells[i][j].val[0] +
                                2 * ETA432 * M2.data.cells[i][j].val[0] *
                                M4.data.cells[i][j].val[0];
                    }

                    if(rand_edge==2){
                        if(user_connected[rand_map] == 1){
                            M3.data.cells[i][j].val[0] = (1-2*ETA_EXT3) * M3.data.cells[i][j].val[0] +
                                    2*ETA_EXT3*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M3.data.cells[i][j].val[0] = (1-2*ETA_EXT3) * M3.data.cells[i][j].val[0] +
                                    2*ETA_EXT3*sensor_data[rand_map];
                        }
                    }

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
                    rand_edge = (rand() % (M4.links+1) + 1);

                    if(rand_edge==1){
                        M4.data.cells[i][j].val[0] =
                                (1 - 2 * ETA234 * pow(M2.data.cells[i][j].val[0], 2)) * M4.data.cells[i][j].val[0] +
                                2 * ETA234 * (M3.data.cells[i][j].val[0] *
                                              M2.data.cells[i][j].val[0]);
                    }

                    if(rand_edge==2){
                        M4.data.cells[i][j].val[0] =
                                (1 - 2 * ETA654) * M4.data.cells[i][j].val[0] +
                                2 * ETA654 * (M5.data.cells[i][j].val[0] +
                                              2 * M6.data.cells[i][j].val[0]);
                    }

                    if(rand_edge==3){
                        if(user_connected[rand_map] == 1){
                            M4.data.cells[i][j].val[0] = (1-2*ETA_EXT4) * M4.data.cells[i][j].val[0] +
                                    2*ETA_EXT4*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M4.data.cells[i][j].val[0] = (1-2*ETA_EXT4) * M4.data.cells[i][j].val[0] +
                                    2*ETA_EXT4*sensor_data[rand_map];
                        }
                    }

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
                    rand_edge = (rand() % (M5.links+1) + 1);

                    if(rand_edge==1){
                        M5.data.cells[i][j].val[0] =
                                (1 - 2 * ETA456) * M5.data.cells[i][j].val[0] +
                                2 * ETA456 * (M4.data.cells[i][j].val[0] - 2 * M6.data.cells[i][j].val[0]);
                    }

                    if(rand_edge==2){
                        if(user_connected[rand_map] == 1){
                            M5.data.cells[i][j].val[0] = (1-2*ETA_EXT5) * M5.data.cells[i][j].val[0] +
                                    2*ETA_EXT5*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M5.data.cells[i][j].val[0] = (1-2*ETA_EXT5) * M5.data.cells[i][j].val[0] +
                                    2*ETA_EXT5*sensor_data[rand_map];
                        }
                    }

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
                    rand_edge = (rand() % (M6.links+1) + 1);

                    if(rand_edge==1){
                        M6.data.cells[i][j].val[0] =
                                (1 - 8 * ETA456) * M6.data.cells[i][j].val[0] +
                                4 * ETA456 *
                                ((M4.data.cells[i][j].val[0] -
                                  M5.data.cells[i][j].val[0]));
                    }

                    if(rand_edge==2){
                        if(user_connected[rand_map] == 1){
                            M6.data.cells[i][j].val[0] = (1-2*ETA_EXT6) * M6.data.cells[i][j].val[0] +
                                    2*ETA_EXT6*user_data[rand_map];
                        }
                        if(sensor_connected[rand_map] == 1){
                            M6.data.cells[i][j].val[0] = (1-2*ETA_EXT6) * M6.data.cells[i][j].val[0] +
                                    2*ETA_EXT6*sensor_data[rand_map];
                        }
                    }

                    e6 = fabs(M6.data.cells[i][j].val[0] - M6ant);

                    M6ant = M6.data.cells[i][j].val[0];

                    update_state[rand_map] = 1;
                }
            }
        }

        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {

                // full errors
                E1[0] = M1.data.cells[i][j].val[0]-M2.data.cells[i][j].val[0]/3;
                E2[0] = M2.data.cells[i][j].val[0]-3*M1.data.cells[i][j].val[0];
                E2[1] = M2.data.cells[i][j].val[0]-M3.data.cells[i][j].val[0]/M4.data.cells[i][j].val[0];
                E3[0] = M3.data.cells[i][j].val[0]-M2.data.cells[i][j].val[0]*M4.data.cells[i][j].val[0];
                E4[0] = M4.data.cells[i][j].val[0]-M3.data.cells[i][j].val[0]/M2.data.cells[i][j].val[0];
                E4[1] = M4.data.cells[i][j].val[0]-M5.data.cells[i][j].val[0] - 2*M6.data.cells[i][j].val[0];
                E5[0] = M5.data.cells[i][j].val[0]-M4.data.cells[i][j].val[0] + 2*M6.data.cells[i][j].val[0];
                E6[0] = M6.data.cells[i][j].val[0]-(M4.data.cells[i][j].val[0]-M5.data.cells[i][j].val[0])/2;



            }

        }

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

        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        log_message("Loop time: %f ms\n",(double) (stop.tv_nsec-start.tv_nsec)/1000000); // get time in ms
        //        sprintf(log_bufferw, " Time: %f\n", (double) (stop.tv_nsec-start.tv_nsec)/1000000);
        //        fwrite(log_bufferw, strlen(log_bufferw), 1, f);

#ifdef VERBOSE
        timer++;
        sprintf(log_bufferw, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %ld\n",
                M1.data.cells[0][0].val[0],
                M2.data.cells[0][0].val[0],
                M3.data.cells[0][0].val[0],
                M4.data.cells[0][0].val[0],
                M5.data.cells[0][0].val[0],
                M6.data.cells[0][0].val[0],
                E1[0],
                E2[0],
                E2[1],
                E3[0],
                E4[0],
                E4[1],
                E5[0],
                E6[0],
                timer);
        fwrite(log_bufferw, strlen(log_bufferw), 1, f);
#endif
    }
    return 0;
}
