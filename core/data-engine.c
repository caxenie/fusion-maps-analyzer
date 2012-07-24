/* Data transfer engine between the core network and the
 * visualizer using the DBud system bus.
 * Data engine implementation.
 */

#include "data-engine.h"
#include "core.h"

/* mutex to access the network data safely when requested by analyzer */
static pthread_mutex_t net_data_mutex = PTHREAD_MUTEX_INITIALIZER;

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
                       NULL);
    dbus_bus_add_match(conn,
                       "type='method_call',interface='org.fusionmaps.methods'",
                       NULL);
    // activate filters by flushing the connection
    dbus_connection_flush(conn);

    // init the global user / sensor interaction vars
    for(int i = 0;i<=MAPS_NUM;i++){
        sensor_connected[i] = 0;
        user_connected[i] = 0;
        sensor_data[i] = 0.0f;
        user_data[i] = 0.0f;
        update_rate_user[i] = 1.0;
        update_rate_sensor[i] = 1.0;
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
    pthread_mutex_lock(&net_data_mutex);
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
    pthread_mutex_unlock(&net_data_mutex);

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
    int rc;

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
        sensor_connected[map_id] = 1;
        // invalidate the user interface
        user_connected[map_id] = 0;
        // check if the button is checked or released
        if(data==1.0){
            // the button was activated and so, start the timer
            if((rc=create_rate_timer(&sensor_timer[map_id], SYNC_DATA*US_TO_MS, SYNC_DATA/US_TO_MS, ONE_SHOT))==-1){
                printf("Error setting timer for the user data update in map %d \n", map_id);
            }
        }
        if(data==0.0){
            // sensor is disconnected so, disarm and delete all the associated timers
            cancel_rate_timer(&sensor_timer[map_id]);
            sensor_timer[map_id] = NULL;
        }
    }

    // user data is connected to the map
    if(strcmp(sigvalue, SIGNAL3)==0){
        // validate user connection
        user_connected[map_id] = 1;
        // invalidate the sensor connection
        sensor_connected[map_id] = 0;
        // check if the button is checked or released
        if(data==1.0){
            // start timer for data update rate if the button was pressed
            if((rc=create_rate_timer(&user_timer[map_id], SYNC_DATA/US_TO_MS, SYNC_DATA/US_TO_MS, PERIODIC))==-1){
                printf("Error setting timer for the user data update in map %d \n", map_id);
            }
        }
        // if button was released disconnect from map and stop timers
        if(data==0.0){
            cancel_rate_timer(&user_timer[map_id]);
            user_timer[map_id] = NULL;
        }
    }

    // input data rate changed
    if(strcmp(sigvalue, SIGNAL2) == 0){

        // check if we modify the use or the sensor data rate

        if(user_connected[map_id]==1){
            update_rate_user[map_id] = data;
            // invalidate sensor connection
            sensor_connected[map_id] = 0;
            // start timer for data update rate
            if((rc=create_rate_timer(&user_timer[map_id], SYNC_DATA*(int)update_rate_user[map_id]/US_TO_MS, SYNC_DATA*(int)update_rate_user[map_id]/US_TO_MS, ONE_SHOT))==-1){
                printf("Error setting timer for the user data update in map %d \n", map_id);
            }
        }

        if(sensor_connected[map_id] == 1){
            // connect sensor to the map
            update_rate_sensor[map_id] = data;
            // invalidate user connection
            user_connected[map_id] = 0;
            // start timer for data update rate
            if((rc=create_rate_timer(&sensor_timer[map_id], SYNC_DATA*(int)update_rate_sensor[map_id]/US_TO_MS, SYNC_DATA*(int)update_rate_sensor[map_id]/US_TO_MS, ONE_SHOT))==-1){
                printf("Error setting timer for the user data update in map %d \n", map_id);
            }
        }
    }

    // user data value changed
    if(strcmp(sigvalue, SIGNAL4) == 0){
        user_data[map_id] = data;
        // start timer for data update rate
        if((rc=create_rate_timer(&user_timer[map_id], SYNC_DATA*(int)update_rate_user[map_id]/US_TO_MS, SYNC_DATA*(int)update_rate_user[map_id]/US_TO_MS, PERIODIC))==-1){
            printf("Error setting timer for the user data update in map %d \n", map_id);
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
            usleep(1);
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
    if ( *tidp == user_timer[1])
    {
        // handle m1 user data rate
        M1.data.cells[0][0].val[0] = user_data[1];
    }
    else if ( *tidp == user_timer[2] )
    {
        // handle m2 user data rate
        M2.data.cells[0][0].val[0] = user_data[2];
    }
    else if ( *tidp == user_timer[3] )
    {
        // handle m3 user data rate
        M3.data.cells[0][0].val[0] = user_data[3];
    }
    else if ( *tidp == user_timer[4] )
    {
        // handle m4 user data rate
        M4.data.cells[0][0].val[0] = user_data[4];
    }
    else if ( *tidp == user_timer[5] )
    {
        // handle m5 user data rate
        M5.data.cells[0][0].val[0] = user_data[5];
    }
    else if ( *tidp == user_timer[6] )
    {
        // handle m6 user data rate
        M6.data.cells[0][0].val[0] = user_data[6];
    }
    else if ( *tidp == sensor_timer[1] )
    {
        // read the sensor
        sensor_data[1] += 0.0123;
        // handle m1 sensor data rate
        M1.data.cells[0][0].val[0] = sensor_data[1];
    }
    else if ( *tidp == sensor_timer[2] )
    {
        // read the sensor
        sensor_data[2] += 0.2313;
        // handle m2 sensor data rate
        M2.data.cells[0][0].val[0] = sensor_data[2];
    }
    else if ( *tidp == sensor_timer[3] )
    {
        // read the sensor
        sensor_data[3] += 0.2131;
        // handle m3 sensor data rate
        M3.data.cells[0][0].val[0] = sensor_data[3];
    }
    else if ( *tidp == sensor_timer[4] )
    {
        // read the sensor
        sensor_data[4] += 0.0023;
        // handle m4 sensor data rate
        M4.data.cells[0][0].val[0] = sensor_data[4];
    }
    else if ( *tidp == sensor_timer[5] )
    {
        // read the sensor
        sensor_data[5] += 0.7868;
        // handle m5 sensor data rate
        M5.data.cells[0][0].val[0] = sensor_data[5];
    }
    else if ( *tidp == sensor_timer[6] )
    {
        // read the sensor
        sensor_data[6] += 0.911;
        // handle m6 sensor data rate
        M6.data.cells[0][0].val[0] = sensor_data[6];
    }
}

/* timing interface for updating the maps value when we have user/sensor
   connection activated. Create timers for both user and sensor interfaces
   on a per-map and per-rate basis.
*/
int create_rate_timer(timer_t *timer_id, int expire_val, int interval, int mode )
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
    if(mode==PERIODIC){
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = interval * 1000000; // upgrade to ms resolution
        its.it_value.tv_sec = 0;
        its.it_value.tv_nsec = expire_val * 1000000;  // upgrade to ms resolution
    }
    if(mode==ONE_SHOT){
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;
        its.it_value.tv_sec = 0;
        its.it_value.tv_nsec = expire_val * 1000000;
    }
    /* arm timer */
    timer_settime(*timer_id, 0, &its, NULL);
    return(0);
}

/* disarms a rate timer created apriori for the user / sensor data update rate */
int cancel_rate_timer(timer_t *timer_id)
{
    struct itimerspec  its;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    if(timer_id!=NULL){
        timer_settime(&timer_id, 0, &its, NULL);
        timer_delete(&timer_id);
        timer_id = NULL;
    }
}
