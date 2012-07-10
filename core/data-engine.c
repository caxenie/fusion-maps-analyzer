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
       update_rate[i] = 0;
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
    if(strcmp(sigvalue, SIGNAL1)==0){
            // validate sensor interface
            map_idx = map_id;
            sensor_connected[map_idx] = 1;
            // invalidate user connection
            user_connected[map_idx] = 0;
    }

    if(strcmp(sigvalue, SIGNAL2) == 0){
        // connect sensor to the map
        update_rate[map_idx] = data;
        sensor_data[map_idx] = rand(); // TODO add sensors interface
    }

    if(strcmp(sigvalue, SIGNAL3)==0){
            // validate user connection
            map_idx = map_id;
            user_connected[map_idx] = 1;
            // invalidate sensor connection
            sensor_connected[map_idx] = 0;
    }

    if(strcmp(sigvalue, SIGNAL4) == 0){
        user_data[map_idx] = data;
    }

    // check if we connect a sensor or the user interface to the maps in the network
    // as normally the net stays in the relaxed state until something new value is injected
    // we can check if external input is provided in a synchronous manner checking every time
    // after the net has relaxed

    // check for sensor or user connected
    for(int i=1;i<=MAPS_NUM;i++){
        if(sensor_connected[i]==1 && user_connected[i] == 0){
            // connect the sensor value to the apropriate map
            switch(i)
            {// here check the map index

            case 1:
            {
                 M1.data.cells[0][0].val[0] = sensor_data[i];
            }
                break;
            case 2:
            {
                M2.data.cells[0][0].val[0] = sensor_data[i];

            }
                break;
            case 3:
            {
                M3.data.cells[0][0].val[0] = sensor_data[i];

            }
                break;
            case 4:
            {
                M4.data.cells[0][0].val[0] = sensor_data[i];

            }
                break;
            case 5:
            {
                M5.data.cells[0][0].val[0] = sensor_data[i];

            }
                break;
            case 6:
            {
                M6.data.cells[0][0].val[0] = sensor_data[i];

            }
                break;
            default:
                break;

            }
        }

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
