/**
* Distributed cognitive systems design demo - data analyzer GUI.
* Simple recurrent network that converges to a stable state
* in which each of the defined relationships are satisfied.
* Data engine functionality implementation.
*/
#include "data-engine.h"

DataEngine::DataEngine(QObject *parent) :
    QObject(parent)
{
    // initialise the error value
    dbus_error_init(&err);

    // connect to the DBUS system bus, and check for errors
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
    if (dbus_error_is_set(&err)) {
        log_message( "GUI: DATA-ENGINE: Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (NULL == conn) {
        log_message("GUI: DATA-ENGINE: Cannot create connection to system bus!: %s\n", "ctor");
        exit(EXIT_FAILURE);
    }
    running = 1;
    /* init dat aand err variables */
    for(int i=0;i<MAPS_NUM;i++){
        map_data[i] = 0.0f;
    }
    for(int i=0;i<ERR_NUM;i++){
        map_err[i] = 0.0f;
    }
}

void DataEngine::init_bus_interface()
{
    int ret;
    // register our name on the bus, and check for errors
    ret = dbus_bus_request_name(conn, CLIENT_BUS_NAME, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
    if (dbus_error_is_set(&err)) {
        log_message( "GUI: DATA-ENGINE: Name Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
        log_message("GUI: DATA-ENGINE: Cannot set primary owner for name!: %s\n", "init");
        exit(EXIT_FAILURE);
    }
}

void DataEngine::close_bus_interface()
{
    dbus_connection_unref(conn);
}

void DataEngine::send_method_call(const char *param)
{
    DBusMessage* msg;
    DBusMessageIter args;
    DBusPendingCall* pending;
    double map_val;

    log_message("GUI: DATA-ENGINE: Calling remote method with %s\n", param);

    // create a new method call and check for errors
    msg = dbus_message_new_method_call( SERVER_BUS_NAME , // target for the method call
                                        BUS_METHODS_OBJECT, // object to call on
                                        SERVER_METHOD_INTERFACE, // interface to call on
                                        param); // method name
    if (NULL == msg) {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message Null!: %s \n", "send_method_call");
        exit(EXIT_FAILURE);
    }

    // append arguments
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Out Of Memory!: %s\n", "send_method_call");
        exit(EXIT_FAILURE);
    }

    // send message and get a handle for a reply
    if (!dbus_connection_send_with_reply (conn, msg, &pending, DBUS_TIMEOUT_USE_DEFAULT)) {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Out Of Memory!: %s\n", "send_method_call");
        exit(EXIT_FAILURE);
    }
    if (NULL == pending) {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Pending Call Null: %s\n", "send_method_call");
        exit(EXIT_FAILURE);
    }
    dbus_connection_flush(conn);

    log_message("GUI: DATA-ENGINE: METHOD CALLS: Request Sent: %s\n", "send_method_call");

    // free message
    dbus_message_unref(msg);

    // block until we recieve a reply
   dbus_pending_call_block(pending);

    // get the reply message
   msg = dbus_pending_call_steal_reply(pending);
    if (NULL == msg) {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Reply Null: %s\n", "send_method_call");
        exit(EXIT_FAILURE);
    }
    // free the pending message handle
    dbus_pending_call_unref(pending);

    log_message("GUI: DATA-ENGINE: METHOD CALLS: Got Reply: %s\n", "send_method_call");

    // read the parameters in the reply - values of the maps and errors
    // MAPS values
    if (!dbus_message_iter_init(msg, &args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has no arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_method_call");
    }
    else
    {
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[0] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 1 value : %lf\n", this->map_data[0]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE  METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_method_call");
    }
    else
    {
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[1] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 2 value : %lf\n", this->map_data[1]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else
    {
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[2] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 3 value : %lf\n",this->map_data[2]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args))
    {
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[3] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 4 value : %lf\n", this->map_data[3]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
     }
    else
    {
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[4] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 5 value : %lf\n", this->map_data[4]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_data[5] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 6 value : %lf\n", this->map_data[5]);

    // ERRORS values
    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[0] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 1 error R1 : %lf\n", this->map_err[0]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[1] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 2 error R1 : %lf\n", this->map_err[1]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[2] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 2 error R2 : %lf\n", this->map_err[2]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[3] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 3 error R2 : %lf\n", this->map_err[3]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[4] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 4 error R2 : %lf\n", this->map_err[4]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[5] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 4 error R3 : %lf\n", this->map_err[5]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[6] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 5 error R3 : %lf\n", this->map_err[6]);

    if (!dbus_message_iter_next(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Message has too few arguments!: %s\n", "send_method_call");
    }
    else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)){
        log_message( "GUI: DATA-ENGINE: METHOD CALLS: Argument is not double!: %s\n", "send_signal");
    }
    else{
        dbus_message_iter_get_basic(&args, &map_val);
    }
    this->map_err[7] = map_val;
    log_message("GUI: DATA-ENGINE: METHOD CALLS: Map 6 error R3 : %lf\n", this->map_err[7]);

    // free reply and close connection
    dbus_message_unref(msg);
}

void DataEngine::send_signal(double value, const char *sigvalue, int map_id)
{
    DBusMessage* msg;
    DBusMessageIter args;

    dbus_uint32_t serial = 0;

    log_message("GUI: DATA-ENGINE: SIGNALS: Sending signal %s with value %lf\n", sigvalue, value);

    // create a signal & check for errors
    msg = dbus_message_new_signal(BUS_SIGNALS_OBJECT, // object name of the signal
                                  SERVER_SIGNAL_INTERFACE, // interface name of the signal
                                  sigvalue); // name of the signal
    if (NULL == msg)
    {
        log_message( "GUI: DATA-ENGINE: SIGNALS: Message Null: %s\n", "send_signal");
        exit(EXIT_FAILURE);
    }

    // append arguments onto signal
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)) {
        log_message( "GUI: DATA-ENGINE: SIGNALS: Out Of Memory!: %s\n", "send_signal");
        exit(EXIT_FAILURE);
    }

    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &value)) {
        log_message( "GUI: DATA-ENGINE: SIGNALS: Out Of Memory!: %s\n", "send_signal");
        exit(EXIT_FAILURE);
    }

    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_INT32, &map_id)) {
        log_message( "GUI: DATA-ENGINE: SIGNALS: Out Of Memory!: %s\n", "send_signal");
        exit(EXIT_FAILURE);
    }

    // send the message and flush the connection
    if (!dbus_connection_send(conn, msg, &serial)) {
        log_message( "GUI: DATA-ENGINE: SIGNALS: Out Of Memory!: %s\n", "send_signal");
        exit(EXIT_FAILURE);
    }
    dbus_connection_flush(conn);

    log_message("GUI: DATA-ENGINE: SIGNALS: Signal Sent: %s\n", "send_signal");

    // free the message and close the connection
    dbus_message_unref(msg);
}
