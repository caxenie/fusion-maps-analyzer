/**
 * Data transfer engine between the core network and the
 * visualizer using the DBus system bus.
 * Data engine functionality definition.
 */
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dbus/dbus.h>
#include <string.h>
#include <signal.h>
#include <time.h>

/* bus attributes */
#define SERVER_BUS_NAME 			"org.fusionmaps.network"
#define SERVER_SIGNAL_INTERFACE                 "org.fusionmaps.signals"
#define SERVER_METHOD_INTERFACE                 "org.fusionmaps.methods"

/* method aliases on the bus */
#define METHOD1 "update_values"
#define SIGNAL1 "sensor_data_connected" 
#define SIGNAL2 "update_rate_changed"
#define SIGNAL3 "user_data_connected"
#define SIGNAL4 "update_user_data_changed"

/* network parameters */
#define MAPS_NUM    6
#define SYNC_DATA   1000 // us - adjusted to 1ms loop time of net
#define US_TO_MS    1000

#define DATA_ENGINE_THREAD 2

/* g++ warnings shut up */
#ifdef __GNUC__
    #define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
    #define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
    #define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
    #define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

/* update rate timer types */
enum{
  ONE_SHOT,
  PERIODIC
};

/* thread id for data engine thread */
pthread_t data_engine_thread;
/* connection to the DBus system bus */
DBusConnection* conn;
/* error handler */
DBusError err;

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

/* init connection to the system bus and add signal filters */
void init_system_bus_connection();
/* handle client method calls coming on the system bus to request data updates */
void handle_client_methods(DBusMessage *msg);
/* handle signals form clients on the system bus and updates netwrok parameters */
void handle_client_signals(DBusMessage *msg);
/* the main loop that handles requests from clients */
void listen_to_data_clients();
/* initialize the data engine thread properties and sets up executing code */
void* data_engine_functionality(void* UNUSED(data));
/* start the data engine code */
void start_data_transfer_engine();
/* cancel the data engine thread */
void cancel_data_transfer_engine();
/* timers for maps update - we need timers for updating from user data or from sensor input */
timer_t* user_timer;
timer_t* sensor_timer;
/*
  signal handler for the timers when capturing the SIGRTMIN signal.
  the function takes a pointer to a timer_t variable that will be filled with the timer ID created by timer_create().  .
  this pointer is also saved in the sival_ptr variable right before calling timer_create().
  in this function notice that we always use the SIGRTMIN signal, so expiration of any timer causes this signal to be raised.
*/
void rate_timer_handler( int UNUSED(sig), siginfo_t *si, void * UNUSED(uc));
/* timing interface for updating the maps value when we have user/sensor
   connection activated. Create timers for both user and sensor interfaces
   on a per-map and per-rate basis.
*/
int create_rate_timer(timer_t *timer_id, int max_val, int interval, int mode );
/* disarms a rate timer created apriori for the user / sensor data update rate */
int cancel_rate_timer(timer_t timer_id);

