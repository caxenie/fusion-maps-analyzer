#ifndef DATAENGINE_H
#define DATAENGINE_H

#include <dbus/dbus.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <qobject.h>

#define SERVER_BUS_NAME 			"org.fusionmaps.network"
#define CLIENT_BUS_NAME 			"org.fusionmaps.visualizer"
#define SERVER_SIGNAL_INTERFACE     "org.fusionmaps.signals"
#define SERVER_METHOD_INTERFACE     "org.fusionmaps.methods"
#define BUS_METHODS_OBJECT 			"/org/fusionmaps/methods/object"
#define BUS_SIGNALS_OBJECT 			"/org/fusionmaps/signals/object"

#define REFRESH_METHOD_CALL         "update_values"
#define SENSOR_CONNECT_SIGNAL       "sensor_data_connected"
#define SENSOR_RATE_CHANGED_SIGNAL  "update_sensor_rate_changed"
#define USER_CONNECT_SIGNAL         "user_data_connected"
#define USER_DATA_CHANGED_SIGNAL    "update_user_data_changed"

#define MAPS_NUM    6
#define ERR_NUM     8

#define DATA_REQ_FREQ    1000   //ms

#define VERBOSE 0

#define log_message(format,args...) \
            do{ \
                if(VERBOSE) \
                    fprintf(stdout,format,args); \
              } while(0);

class DataEngine : public QObject
{
    Q_OBJECT
public:

    DBusConnection* conn;
    DBusError err;
    short running; // running state of the net process
    double map_data[MAPS_NUM]; //  map data - TODO Fix this hardcoded values according to net structure
    double map_err[ERR_NUM];  //  map errors

    explicit DataEngine(QObject *parent = 0);
    /* initialize the connection to the system bus */
    void init_bus_interface();
    /* close the connection to the system bus */
    void close_bus_interface();
    /* connect to the DBUS bus and send a broadcast signal */
    void send_signal(double value, const char* sigvalue, int map_id);
    /* call a method on a remote object */
    void send_method_call(const char* param);
signals:
    
public slots:

};

#endif // DATAENGINE_H
