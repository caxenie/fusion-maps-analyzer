/* Data transfer engine between the core network and the
 * visualizer using the DBud system bus.
 * Data engine definition.
 */


#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dbus/dbus.h>
#include <string.h>

#define SERVER_BUS_NAME 			"org.fusionmaps.network"
#define SERVER_SIGNAL_INTERFACE 	"org.fusionmaps.signals"
#define SERVER_METHOD_INTERFACE    "org.fusionmaps.methods"

#define METHOD1 "update_values"
#define SIGNAL1 "sensor_data_connected" 
#define SIGNAL2 "update_sensor_rate_changed"
#define SIGNAL3 "user_data_connected"
#define SIGNAL4 "update_user_data_changed"

#define MAPS_NUM 6
#define SYNC_DATA  100000 // us

/* thread id for data engine thread */
pthread_t data_engine_thread;
/* connection to the DBus system bus */
DBusConnection* conn;
/* error handler */
DBusError err;

/* switches for user data or sensor data inputs */
int user_connected[MAPS_NUM+1];
int sensor_connected[MAPS_NUM+1];
/* stores the data update rate for sensors */
double update_rate[MAPS_NUM+1];
/* stores the data from the user */
double user_data[MAPS_NUM+1];
/* stores the data from the connected sensor */
double sensor_data[MAPS_NUM+1];

/* stores the map id to be connected to user / sensor data */
int map_idx;

/* init connection to the system bus and add signal filters */
void init_system_bus_connection();
/* handle client method calls coming on the system bus to request data updates */
void handle_client_methods(DBusMessage *msg);
/* handle signals form clients on the system bus and updates netwrok parameters */
void handle_client_signals(DBusMessage *msg);
/* the main loop that handles requests from clients */
void listen_to_data_clients();
/* initialize the data engine thread properties and sets up executing code */
void* data_engine_functionality(void *data);
/* start the data engine code */
void start_data_transfer_engine();
/* cancel the data engine thread */
void cancel_data_transfer_engine();
