/* Data transfer engine between the core network and the
 * visualizer using the DBud system bus.
 * Data engine implementation.
 */

#include "data-engine.h"
#include "core.h"

/* init connection to the system bus and add signal filters */
void init_system_bus_connection()
{
	int ret;
   // initialise the errors
   dbus_error_init(&err);
   
   // connect to the bus and check for errors
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) {
      printf("CORE: DATA-ENGINE: Connection Error (%s)\n", err.message);
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
      exit(EXIT_FAILURE);
   }
   
   // request our name on the bus and check for errors
   ret = dbus_bus_request_name(conn, 
							   SERVER_BUS_NAME, 
							   DBUS_NAME_FLAG_REPLACE_EXISTING , 
							   &err);
   if (dbus_error_is_set(&err)) { 
      printf("CORE: DATA-ENGINE: Name Error (%s)\n", err.message);
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
      exit(EXIT_FAILURE);
   }

	   // add a rule for which messages we want to see
   dbus_bus_add_match(conn, 
					 "type='signal',interface='org.fusionmaps.signals'", 
					  &err); 
   dbus_connection_flush(conn);
   if (dbus_error_is_set(&err)) { 
      printf("CORE: DATA-ENGINE: Match Error (%s)\n", err.message);
      exit(EXIT_FAILURE); 
   }
    // init the global user / sensor interaction vars
   int i;
   for(i = 0;i<MAPS_NUM;i++){
       sensor_connected[i] = 0;
       user_connected[i] = 0;
       sensor_data[i] = 0.0f;
       user_data[i] = 0.0f;
       update_rate_user[i] = 0;
       update_rate_sensor[i] = 0;
   }
}

/* handle client method calls coming on the system bus to request data updates */
void handle_client_methods(DBusMessage *msg)
{
   DBusMessage* reply;
   DBusMessageIter args;
   double map1_val, map2_val, map3_val , map4_val , map5_val , map6_val;
   double map1_r1, map2_r1, map2_r2, map3_r2, map4_r2 , map4_r3 , map5_r3 , map6_r3;
   dbus_uint32_t serial = 0;
   char* param = "";

   /* get data from the map thread */
   /* FIXME just a hack to check communication - Make it SAFER */
   map1_val = M1.data.cells[0][0].val[0];
   map2_val = M2.data.cells[0][0].val[0];
   map3_val = M3.data.cells[0][0].val[0];
   map4_val = M4.data.cells[0][0].val[0];
   map5_val = M5.data.cells[0][0].val[0];
   map6_val = M6.data.cells[0][0].val[0];

   map1_r1 = E1[0]; 
   map2_r1 = E2[0];
   map2_r2 = E2[1];
   map3_r2 = E3[0];
   map4_r2 = E4[0];
   map4_r3 = E4[1];
   map5_r3 = E5[0];
   map6_r3 = E6[0];
 
   // read the arguments
   if (!dbus_message_iter_init(msg, &args))
      printf("CORE: DATA-ENGINE: Message has no arguments!\n"); 
   else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args)) 
      printf("CORE: DATA-ENGINE: Argument is not string!\n"); 
   else 
      dbus_message_iter_get_basic(&args, &param);

   printf("CORE: DATA-ENGINE: Method called with %s\n", param);

   // create a reply from the message
   reply = dbus_message_new_method_return(msg);

   // add the arguments to the reply
   dbus_message_iter_init_append(reply, &args);
	// attach maps values
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map1_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map3_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map5_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map6_val)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }
   // attach errors values
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map1_r1)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_r1)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_r2)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map3_r2)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_r2)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_r3)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map5_r3)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map6_r3)) { 
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }

   // send the reply && flush the connection
   if (!dbus_connection_send(conn, reply, &serial)) {
      printf("CORE: DATA-ENGINE: Out Of Memory!\n"); 
      exit(EXIT_FAILURE);
   }
   dbus_connection_flush(conn);

   // free the reply
   dbus_message_unref(reply);
}

/* handle signals form clients on the system bus and updates netwrok parameters */
void handle_client_signals(DBusMessage *msg)
{
   DBusMessageIter args;
   char *sigvalue;
   double data;
   int map_id;

      // check if the message is a signal from the correct interface and with the correct name
         
         // read the parameters
	   if (!dbus_message_iter_init(msg, &args))
		  printf("CORE: DATA-ENGINE: Message has no arguments!\n"); 
	   else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args)) 
		  printf("CORE: DATA-ENGINE: Argument is not string!\n"); 
	   else
		  dbus_message_iter_get_basic(&args, &sigvalue);

	   if (!dbus_message_iter_next(&args))
		  printf("CORE: DATA-ENGINE: Message has too few arguments!\n"); 
	   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
		  printf("CORE: DATA-ENGINE: Argument is not double!\n"); 
	   else
		  dbus_message_iter_get_basic(&args, &data);


	    if (!dbus_message_iter_next(&args))
		    printf("CORE: DATA-ENGINE: Message has too few arguments!\n");
	    else if (DBUS_TYPE_INT32 != dbus_message_iter_get_arg_type(&args))
		    printf("CORE: DATA-ENGINE: Argument is not int!\n");
	    else 
		  dbus_message_iter_get_basic(&args, &map_id);



	printf("CORE: DATA-ENGINE: Got Signal %s with value %lf for map %d \n", sigvalue, data, map_id);

    // filter depending on the type of signal

    // sensor is connected to map
    if(strcmp(sigvalue, SIGNAL1)==0){
            // validate sensor interface
            map_idx = map_id;
            sensor_connected[map_idx] = 1;
            // invalidate user connection
            user_connected[map_idx] = 0;
    }

    // user data is connected to the map
    if(strcmp(sigvalue, SIGNAL3)==0){
            // validate user connection
            map_idx = map_id;
            user_connected[map_idx] = 1;
            // invalidate sensor connection
            sensor_connected[map_idx] = 0;
    }

    // input data rate changed
    if(strcmp(sigvalue, SIGNAL2) == 0){
        // check if we modify the sensor or the user data rate
        if(user_connected[map_idx]==1 && sensor_connected[map_idx]==0){
            update_rate_user[map_idx] = data;
            int rc;
            // start timer for data update rate
            switch(map_idx){
            case 1:
            {
                if((rc=create_rate_timer(&timer_user_m1, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            case 2:
            {
                if((rc=create_rate_timer(&timer_user_m2, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            case 3:
            {
                if((rc=create_rate_timer(&timer_user_m3, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            case 4:
            {
                if((rc=create_rate_timer(&timer_user_m4, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            case 5:
            {
                if((rc=create_rate_timer(&timer_user_m5, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            case 6:
            {
                if((rc=create_rate_timer(&timer_user_m6, SYNC_DATA*update_rate_user[map_idx], SYNC_DATA*update_rate_user[map_idx]))==-1){
                    printf("Error setting timer for the user data update in map %d \n", map_idx);
                }
            }
            default:
                break;
            }
        }
        else{
            // connect sensor to the map
            update_rate_sensor[map_idx] = data;
            // start timer for data update rate

        }
    }

    // user data value changed
    if(strcmp(sigvalue, SIGNAL4) == 0){
        user_data[map_idx] = data;
    }

    for(int i=1;i<=MAPS_NUM;i++){
    // check for user connected
       if(user_connected[i]==1 && sensor_connected[i] == 0){
           // connect value to the network
           switch(i)
           {// here check the map index

           case 1:
           {
               M1.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           case 2:
           {
               M2.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           case 3:
           {
               M3.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           case 4:
           {
               M4.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           case 5:
           {
               M5.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           case 6:
           {
               M6.data.cells[0][0].val[0] = user_data[i];

           }
               break;
           default:
               break;

           }
       }
    }
}

/* the main loop that handles requests from clients */
void listen_to_data_clients() 
{
   DBusMessage* msg;
   DBusMessage* reply;
   DBusMessageIter args;
   int ret;
   char* param;

   printf("CORE: DATA-ENGINE: Listening for method calls & signals\n");

   // loop, testing for new messages
   while (1) {
      // non blocking read of the next available message
      dbus_connection_read_write(conn, 0);
      msg = dbus_connection_pop_message(conn);

      // loop again if we haven't got a message
      if (NULL == msg) { 
         sleep(1); 
         continue; 
      }
      
      // check this is a method call for the right interface & method
      if (dbus_message_is_method_call(msg, SERVER_METHOD_INTERFACE, METHOD1)) 
         			handle_client_methods(msg);

      if (dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL1) ||
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL2) || 
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL3) ||
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL4))

				 	handle_client_signals(msg);

      // free the message
      dbus_message_unref(msg);
   }
}

/* initialize the data engine thread properties and sets up executing code */
void* data_engine_functionality(void *data)
{
	int ret;
	ret = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (ret != 0) {
        printf("CORE: DATA-ENGINE: Thread pthread_setcancelstate failed\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    if (ret != 0) {
        printf("CORE: DATA-ENGINE: Thread pthread_setcanceltype failed\n");
        exit(EXIT_FAILURE);
    }
	  init_system_bus_connection();
	  listen_to_data_clients();
}

/* start the data engine code */
void start_data_transfer_engine()
{
	int ret;
	if((ret = pthread_create(&data_engine_thread,
						     NULL,
							 data_engine_functionality,
							 NULL))!=0){
		printf("CORE: DATA-ENGINE: Cannot start data transfer engine!\n");
		exit(EXIT_FAILURE);
	}

}

/* cancel the data engine thread */
void cancel_data_transfer_engine()
{
	printf("CORE: DATA-ENGINE: Cancelling the data transfer engine thread .. \n");
	pthread_cancel(data_engine_thread);
}

/*
  signal handler for the timers when capturing the SIGRTMIN signal.
  the function takes a pointer to a timer_t variable that will be filled with the timer ID created by timer_create().  .
  this pointer is also saved in the sival_ptr variable right before calling timer_create().
  in this function notice that we always use the SIGRTMIN signal, so expiration of any timer causes this signal to be raised.
*/
void rate_timer_handler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    // chech which timer has expored so that the value in the map will be updated
    if ( *tidp == timer_user_m1)
    {
        // handle m1 user data rate
        M1.data.cells[0][0].val[0] = user_data[1];
    }
    else if ( *tidp == timer_user_m2 )
    {
        // handle m2 user data rate
        M2.data.cells[0][0].val[0] = user_data[2];
    }
    else if ( *tidp == timer_user_m3 )
    {
        // handle m3 user data rate
        M3.data.cells[0][0].val[0] = user_data[3];
    }
    else if ( *tidp == timer_user_m4 )
    {
        // handle m4 user data rate
        M4.data.cells[0][0].val[0] = user_data[4];
    }
    else if ( *tidp == timer_user_m5 )
    {
        // handle m5 user data rate
        M5.data.cells[0][0].val[0] = user_data[5];
    }
    else if ( *tidp == timer_user_m6 )
    {
        // handle m6 user data rate
        M6.data.cells[0][0].val[0] = user_data[6];
    }
    else if ( *tidp == timer_sensor_m1 )
    {
        // read the sensor
        sensor_data[1] = rand();
        // handle m1 sensor data rate
        M1.data.cells[0][0].val[0] = sensor_data[1];
    }
    else if ( *tidp == timer_sensor_m2 )
    {
        // read the sensor
        sensor_data[2] = rand();
        // handle m2 sensor data rate
        M2.data.cells[0][0].val[0] = sensor_data[2];
    }
    else if ( *tidp == timer_sensor_m3 )
    {
        // read the sensor
        sensor_data[3] = rand();
        // handle m3 sensor data rate
        M3.data.cells[0][0].val[0] = sensor_data[3];
    }
    else if ( *tidp == timer_sensor_m4 )
    {
        // read the sensor
        sensor_data[4] = rand();
        // handle m4 sensor data rate
        M4.data.cells[0][0].val[0] = sensor_data[4];
    }
    else if ( *tidp == timer_sensor_m5 )
    {
        // read the sensor
        sensor_data[5] = rand();
        // handle m5 sensor data rate
        M5.data.cells[0][0].val[0] = sensor_data[5];
    }
    else if ( *tidp == timer_sensor_m6 )
    {
        // read the sensor
        sensor_data[6] = rand();
        // handle m6 sensor data rate
        M6.data.cells[0][0].val[0] = sensor_data[6];
    }
}

/* timing interface for updating the maps value when we have user/sensor
   connection activated. Create timers for both user and sensor interfaces
   on a per-map and per-rate basis.
*/
int create_rate_timer(timer_t *timer_id, int expire_val, int interval )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sig_no = SIGRTMIN;

    /* set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = rate_timer_handler;
    /* initialize the sigaction with an empty mask */
    sigemptyset(&sa.sa_mask);
    if (sigaction(sig_no, &sa, NULL) == -1)
    {
        fprintf(stderr, "Failed to setup signal handling !\n");
        fprintf(stderr, "The timer functionality for data update rate failed !\n");
        return (-1);
    }

    /* set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sig_no;
    te.sigev_value.sival_ptr = timer_id;
    /* create the timer */
    timer_create(CLOCK_REALTIME, &te, timer_id);
    /* setup timer parameters */
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = interval * 1000000; // upgrade to ms resolution
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expire_val * 1000000;  // upgrade to ms resolution
    /* arm timer */
    timer_settime(*timer_id, 0, &its, NULL);
    return(0);
}

#if 0

//Timers funcitonality demo

#include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <signal.h>
       #include <time.h>

timer_t firstTimerID, secondTimerID;

void
timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    if ( *tidp == firstTimerID )
        printf("first\n");
    else if ( *tidp == secondTimerID )
        printf("second\n");
}

int
makeTimer(timer_t *timerID, int expireMS, int intervalMS )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sigNo = SIGRTMIN;


    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sigNo, &sa, NULL) == -1)
    {
        printf("Failed to setup signal handling \n");
        return(-1);
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = intervalMS * 1000000;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expireMS * 1000000;
    timer_settime(*timerID, 0, &its, NULL);

    return(0);
}

int main(int argc, char* argv[]){

    int rc;
    rc = makeTimer(&firstTimerID, 40, 40);
    rc = makeTimer(&secondTimerID, 120, 120);

    while(1);

return 0;
}


#endif
