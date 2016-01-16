/**
 * Distributed cognitive systems design demo - data analyzer GUI.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
 * Main definitions.
 */
#ifndef FUSIONMAPSGUI_H
#define FUSIONMAPSGUI_H

#include <qmainwindow.h>
#include <qprocess.h>
#include <qmessagebox.h>
#include <signal.h>
#include <unistd.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <math.h>
#include <QGraphicsPixmapItem>
#include <time.h>
#include <qtimer.h>
#include <string.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qpaintengine.h>
#include <qwt_plot_grid.h>
#include "plot-engine.h"
#include "data-engine.h"

// converging net binary
#define NET_BINARY       "/fusion_maps_core"
#define INFO_HEADER_MSG  "Network Visualization Tool"
#define LOW_IN      -1.0f
#define HI_IN       1.0f
#define INCREMENT   0.0001f
#define TOLERANCE   0.0001f
#define fequalzero(a) (fabs(a) < TOLERANCE)

namespace Ui {
class FusionMapsGui;
}

class FusionMapsGui : public QMainWindow
{
    Q_OBJECT
    
public:

    QProcess process;
    DataEngine *data_engine;
    QTimer *dbus_timer;

    // maps representation helper - Spectrogram --> extend easier to multi - dimensional
    QwtPlotSpectrogram *repr_m1;
    QwtPlotSpectrogram *repr_m2;
    QwtPlotSpectrogram *repr_m3;
    QwtPlotSpectrogram *repr_m4;
    QwtPlotSpectrogram *repr_m5;
    QwtPlotSpectrogram *repr_m6;

    // errors representation helpers - incremntal plot
    error_plot_data *err_m1_r1;
    error_plot_data *err_m2_r1;
    error_plot_data *err_m2_r2;
    error_plot_data *err_m3_r2;
    error_plot_data *err_m4_r2;
    error_plot_data *err_m4_r3;
    error_plot_data *err_m5_r3;
    error_plot_data *err_m6_r3;


      explicit FusionMapsGui(QWidget *parent = 0);

    ~FusionMapsGui();

private slots:
    void on_actionStart_triggered();

    void on_actionPause_triggered();

    void on_actionResume_triggered();

    void on_actionRestart_triggered();

    void on_actionStop_triggered();

    void on_actionQuit_triggered();

    void on_actionInstructions_triggered();

    void on_actionAbout_triggered();

    void error_processor(QProcess::ProcessError err);

    void on_user_data_slider1_valueChanged(double value);

    void on_user_connect_button_m1_clicked();

    void on_sensor_connect_button_m1_clicked();

    void on_data_update_rate1_valueChanged(int value);

    void on_user_connect_button_m2_clicked();

    void on_sensor_connect_button_m2_clicked();

    void on_user_data_slider2_valueChanged(double value);

    void on_data_update_rate2_valueChanged(int value);

    void on_user_connect_button_m3_clicked();

    void on_sensor_connect_button_m3_clicked();

    void on_user_data_slider3_valueChanged(double value);

    void on_data_update_rate3_valueChanged(int value);

    void on_user_connect_button_m4_clicked();

    void on_sensor_connect_button_m4_clicked();

    void on_user_data_slider4_valueChanged(double value);

    void on_data_update_rate4_valueChanged(int value);

    void on_user_connect_button_m5_clicked();

    void on_sensor_connect_button_m5_clicked();

    void on_user_data_slider5_valueChanged(double value);

    void on_data_update_rate5_valueChanged(int value);

    void on_user_connect_button_m6_clicked();

    void on_sensor_connect_button_m6_clicked();

    void on_user_data_slider6_valueChanged(double value);

    void on_data_update_rate6_valueChanged(int value);

    void update_visuals();

public slots:
    void send_data_request();

private:
    Ui::FusionMapsGui *ui;
};
#endif // FUSIONMAPSGUI_H
