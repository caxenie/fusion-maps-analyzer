#include <core.h>
#include <data-engine.h>

/* mutex to access the network data safely when requested by analyzer */
extern pthread_mutex_t net_data_mutex;

/* support for logging */
struct log{
    /* snapshot of the map data and errors */
    double vals[14];
    /* snapshot iteration */
    int iter;
};

/* file logging support iterator */
long iter;

struct log *log_data;

/* globals */
/* maps in the net */
map M1, M2, M3, M4, M5, M6;
/* errors values */
double *E1, *E2, *E3, *E4, *E4, *E5, *E6;
/* error marking how close is a map to the good value */
double e1, e2, e3, e4, e5, e6;

/* mask arrays for user data or sensor data inputs */
int user_connected[MAPS_NUM+1];
int sensor_connected[MAPS_NUM+1];
/* stores the data update rate for sensors */
double update_rate_sensor[MAPS_NUM+1];
/* stores the data update rate for user data */
double update_rate_user[MAPS_NUM+1];
/* stores the data from the user */
double  user_data[MAPS_NUM+1];
/* stores the data from the connected sensor */
double sensor_data[MAPS_NUM+1];
