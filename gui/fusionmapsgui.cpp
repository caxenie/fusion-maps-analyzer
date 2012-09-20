/**
 * Distributed cognitive systems design demo.
 * Simple recurrent network that converges to a stable state
 * in which each of the defined relationships are satisfied.
 * Main functionality implementation.
 */
#include "fusionmapsgui.h"
#include "ui_fusionmapsgui.h"

// the pid of the net process binary
Q_PID net_pid = 0;
short one_time_init = 0;
int timer_display = 0;

FusionMapsGui::FusionMapsGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FusionMapsGui)
{
    ui->setupUi(this);
    data_engine = new DataEngine();
    dbus_timer = new QTimer(this);
    connect(dbus_timer, SIGNAL(timeout()), this, SLOT(send_data_request()));
    // maps visualization init
    double init_val = 0.0f;
    QwtInterval zInterval;
    QwtScaleWidget *color_interval;
    // map1
    repr_m1 = new QwtPlotSpectrogram();
    repr_m1->setRenderThreadCount(0); // system specific thread count
    repr_m1->setColorMap(new ColorMap());
    repr_m1->setData( new RasterData(init_val));
    repr_m1->attach(ui->graphicsView_m1);
    zInterval = repr_m1->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m1->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m1->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m1->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m1->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m1->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m1->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m1->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m1->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider1->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider1->setValue( 0.0 );

    // map2
    repr_m2 = new QwtPlotSpectrogram();
    repr_m2->setRenderThreadCount(0); // system specific thread count
    repr_m2->setColorMap(new ColorMap());
    repr_m2->setData( new RasterData(init_val));
    repr_m2->attach(ui->graphicsView_m2);
    zInterval = repr_m2->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m2->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m2->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m2->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m2->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m2->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m2->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m2->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m2->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider2->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider2->setValue( 0.0 );
    // map3
    repr_m3 = new QwtPlotSpectrogram();
    repr_m3->setRenderThreadCount(0); // system specific thread count
    repr_m3->setColorMap(new ColorMap());
    repr_m3->setData( new RasterData(init_val));
    repr_m3->attach(ui->graphicsView_m3);
    zInterval = repr_m3->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m3->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m3->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m3->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m3->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m3->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m3->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m3->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m3->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider3->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider3->setValue( 0.0 );
    // map 4
    repr_m4 = new QwtPlotSpectrogram();
    repr_m4->setRenderThreadCount(0); // system specific thread count
    repr_m4->setColorMap(new ColorMap());
    repr_m4->setData( new RasterData(init_val));
    repr_m4->attach(ui->graphicsView_m4);
    zInterval = repr_m4->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m4->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m4->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m4->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m4->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m4->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m4->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m4->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m4->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider4->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider4->setValue( 0.0 );
    // map5
    repr_m5 = new QwtPlotSpectrogram();
    repr_m5->setRenderThreadCount(0); // system specific thread count
    repr_m5->setColorMap(new ColorMap());
    repr_m5->setData( new RasterData(init_val));
    repr_m5->attach(ui->graphicsView_m5);
    zInterval = repr_m5->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m5->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m5->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m5->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m5->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m5->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m5->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m5->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m5->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider5->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider5->setValue( 0.0 );
    // map6
    repr_m6 = new QwtPlotSpectrogram();
    repr_m6->setRenderThreadCount(0); // system specific thread count
    repr_m6->setColorMap(new ColorMap());
    repr_m6->setData( new RasterData(init_val));
    repr_m6->attach(ui->graphicsView_m6);
    zInterval = repr_m6->data()->interval(Qt::ZAxis);
    color_interval = ui->graphicsView_m6->axisWidget(QwtPlot::yRight);
    color_interval->setColorBarEnabled(true);
    color_interval->setColorBarWidth(20);
    color_interval->setColorMap(zInterval, new ColorMap());
    ui->graphicsView_m6->setAxisScale(QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue());
    ui->graphicsView_m6->enableAxis(QwtPlot::yRight);
    ui->graphicsView_m6->plotLayout()->setAlignCanvasToScales(true);
    ui->graphicsView_m6->setAxisScale(QwtPlot::xBottom, -BOUND, BOUND);
    ui->graphicsView_m6->setAxisMaxMinor(QwtPlot::xBottom, 0);
    ui->graphicsView_m6->setAxisScale(QwtPlot::yLeft, -BOUND, BOUND);
    ui->graphicsView_m6->setAxisMaxMinor(QwtPlot::yLeft, 0);
    ui->user_data_slider6->setRange(-1.0, 1.0, 0.0001, 5);
    ui->user_data_slider6->setValue( 0.0 );
    // error visualization init
    double per_sec;
    double freq;
    double nb_per;
    QwtPlotGrid *grid;
    int i;
    // map 1 error
    err_m1_r1 = new error_plot_data;
    err_m1_r1->duration = 1;
    err_m1_r1->period = 10;
    per_sec = err_m1_r1->period/1000.0;
    freq = 1/per_sec;
    err_m1_r1->nb_points = int(err_m1_r1->duration * freq + 1);
    err_m1_r1->real_index = 0;
    err_m1_r1->idx = 0;
    err_m1_r1->datax = new double[err_m1_r1->nb_points];
    err_m1_r1->datay = new double[err_m1_r1->nb_points];
    err_m1_r1->time = new double[2];
    err_m1_r1->val = new double[2];

    nb_per = err_m1_r1->nb_points - 1;
    err_m1_r1->datax[0] = 0;

    for(i=1;i<err_m1_r1->nb_points;i++){
       err_m1_r1->datax[i] = err_m1_r1->datax[0] + err_m1_r1->duration * i/nb_per;
       err_m1_r1->datay[i] = 0.0;
    }
    err_m1_r1->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m1_r1->data_curve->attach(ui->error_r1_plot1);
    err_m1_r1->data_curve->setRawSamples(err_m1_r1->datax, err_m1_r1->datay, err_m1_r1->idx);
    ui->error_r1_plot1->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r1_plot1->setAxisScale(QwtPlot::xBottom, err_m1_r1->datax[0], err_m1_r1->datax[err_m1_r1->nb_points - 1]);
    ui->error_r1_plot1->enableAxis(QwtPlot::xBottom, true);
    ui->error_r1_plot1->setAutoReplot(true);
    grid->attach(ui->error_r1_plot1);

    // map 2 errors
    // error to R1
       err_m2_r1 = new error_plot_data;
    err_m2_r1->duration = 1;
    err_m2_r1->period = 10;
    per_sec = err_m2_r1->period/1000.0;
    freq = 1/per_sec;
    err_m2_r1->nb_points = int(err_m2_r1->duration * freq + 1);
    err_m2_r1->real_index = 0;
    err_m2_r1->idx = 0;
    err_m2_r1->datax = new double[err_m2_r1->nb_points];
    err_m2_r1->datay = new double[err_m2_r1->nb_points];
    err_m2_r1->time = new double[2];
    err_m2_r1->val = new double[2];

    nb_per = err_m2_r1->nb_points - 1;
    err_m2_r1->datax[0] = 0;

    for(i=1;i<err_m2_r1->nb_points;i++){
       err_m2_r1->datax[i] = err_m2_r1->datax[0] + err_m2_r1->duration * i/nb_per;
       err_m2_r1->datay[i] = 0.0;
    }
    err_m2_r1->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m2_r1->data_curve->attach(ui->error_r1_plot2);
    err_m2_r1->data_curve->setRawSamples(err_m2_r1->datax, err_m2_r1->datay, err_m2_r1->idx);
    ui->error_r1_plot2->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r1_plot2->setAxisScale(QwtPlot::xBottom, err_m2_r1->datax[0], err_m2_r1->datax[err_m2_r1->nb_points - 1]);
    ui->error_r1_plot2->enableAxis(QwtPlot::xBottom, true);
    ui->error_r1_plot2->setAutoReplot(true);
    grid->attach(ui->error_r1_plot2);

    // error to R2
    err_m2_r2 = new error_plot_data;
    err_m2_r2->duration = 1;
    err_m2_r2->period = 10;
    per_sec = err_m2_r2->period/1000.0;
    freq = 1/per_sec;
    err_m2_r2->nb_points = int(err_m2_r2->duration * freq + 1);
    err_m2_r2->real_index = 0;
    err_m2_r2->idx = 0;
    err_m2_r2->datax = new double[err_m2_r2->nb_points];
    err_m2_r2->datay = new double[err_m2_r2->nb_points];
    err_m2_r2->time = new double[2];
    err_m2_r2->val = new double[2];

    nb_per = err_m2_r2->nb_points - 1;
    err_m2_r2->datax[0] = 0;

    for(i=1;i<err_m2_r2->nb_points;i++){
       err_m2_r2->datax[i] = err_m2_r2->datax[0] + err_m2_r2->duration * i/nb_per;
       err_m2_r2->datay[i] = 0.0;
    }
    err_m2_r2->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m2_r2->data_curve->attach(ui->error_r2_plot2);
    err_m2_r2->data_curve->setRawSamples(err_m2_r2->datax, err_m2_r2->datay, err_m2_r2->idx);
    ui->error_r2_plot2->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r2_plot2->setAxisScale(QwtPlot::xBottom, err_m2_r2->datax[0], err_m2_r2->datax[err_m2_r2->nb_points - 1]);
    ui->error_r2_plot2->enableAxis(QwtPlot::xBottom, true);
    ui->error_r2_plot2->setAutoReplot(true);
    grid->attach(ui->error_r2_plot2);

    // map 3 error to R2

    err_m3_r2 = new error_plot_data;
    err_m3_r2->duration = 1;
    err_m3_r2->period = 10;
    per_sec = err_m3_r2->period/1000.0;
    freq = 1/per_sec;
    err_m3_r2->nb_points = int(err_m3_r2->duration * freq + 1);
    err_m3_r2->real_index = 0;
    err_m3_r2->idx = 0;
    err_m3_r2->datax = new double[err_m3_r2->nb_points];
    err_m3_r2->datay = new double[err_m3_r2->nb_points];
    err_m3_r2->time = new double[2];
    err_m3_r2->val = new double[2];

    nb_per = err_m3_r2->nb_points - 1;
    err_m3_r2->datax[0] = 0;

    for(i=1;i<err_m3_r2->nb_points;i++){
       err_m3_r2->datax[i] = err_m3_r2->datax[0] + err_m3_r2->duration * i/nb_per;
       err_m3_r2->datay[i] = 0.0;
    }
    err_m3_r2->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m3_r2->data_curve->attach(ui->error_r2_plot3);
    err_m3_r2->data_curve->setRawSamples(err_m3_r2->datax, err_m3_r2->datay, err_m3_r2->idx);
    ui->error_r2_plot3->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r2_plot3->setAxisScale(QwtPlot::xBottom, err_m3_r2->datax[0], err_m3_r2->datax[err_m3_r2->nb_points - 1]);
    ui->error_r2_plot3->enableAxis(QwtPlot::xBottom, true);
    ui->error_r2_plot3->setAutoReplot(true);
    grid->attach(ui->error_r2_plot3);

    // map 4 errors

    // error to R2
    err_m4_r2 = new error_plot_data;
    err_m4_r2->duration = 1;
    err_m4_r2->period = 10;
    per_sec = err_m4_r2->period/1000.0;
    freq = 1/per_sec;
    err_m4_r2->nb_points = int(err_m4_r2->duration * freq + 1);
    err_m4_r2->real_index = 0;
    err_m4_r2->idx = 0;
    err_m4_r2->datax = new double[err_m4_r2->nb_points];
    err_m4_r2->datay = new double[err_m4_r2->nb_points];
    err_m4_r2->time = new double[2];
    err_m4_r2->val = new double[2];

    nb_per = err_m4_r2->nb_points - 1;
    err_m4_r2->datax[0] = 0;

    for(i=1;i<err_m4_r2->nb_points;i++){
       err_m4_r2->datax[i] = err_m4_r2->datax[0] + err_m4_r2->duration * i/nb_per;
       err_m4_r2->datay[i] = 0.0;
    }
    err_m4_r2->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m4_r2->data_curve->attach(ui->error_r2_plot4);
    err_m4_r2->data_curve->setRawSamples(err_m4_r2->datax, err_m4_r2->datay, err_m4_r2->idx);
    ui->error_r2_plot4->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r2_plot4->setAxisScale(QwtPlot::xBottom, err_m4_r2->datax[0], err_m4_r2->datax[err_m4_r2->nb_points - 1]);
    ui->error_r2_plot4->enableAxis(QwtPlot::xBottom, true);
    ui->error_r2_plot4->setAutoReplot(true);
    grid->attach(ui->error_r2_plot4);

    // error to R3
    err_m4_r3 = new error_plot_data;
    err_m4_r3->duration = 1;
    err_m4_r3->period = 10;
    per_sec = err_m4_r3->period/1000.0;
    freq = 1/per_sec;
    err_m4_r3->nb_points = int(err_m4_r3->duration * freq + 1);
    err_m4_r3->real_index = 0;
    err_m4_r3->idx = 0;
    err_m4_r3->datax = new double[err_m4_r3->nb_points];
    err_m4_r3->datay = new double[err_m4_r3->nb_points];
    err_m4_r3->time = new double[2];
    err_m4_r3->val = new double[2];

    nb_per = err_m4_r3->nb_points - 1;
    err_m4_r3->datax[0] = 0;

    for(i=1;i<err_m4_r3->nb_points;i++){
       err_m4_r3->datax[i] = err_m4_r3->datax[0] + err_m4_r3->duration * i/nb_per;
       err_m4_r3->datay[i] = 0.0;
    }
    err_m4_r3->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m4_r3->data_curve->attach(ui->error_r3_plot4);
    err_m4_r3->data_curve->setRawSamples(err_m4_r3->datax, err_m4_r3->datay, err_m4_r3->idx);
    ui->error_r3_plot4->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r3_plot4->setAxisScale(QwtPlot::xBottom, err_m4_r3->datax[0], err_m4_r3->datax[err_m4_r3->nb_points - 1]);
    ui->error_r3_plot4->enableAxis(QwtPlot::xBottom, true);
    ui->error_r3_plot4->setAutoReplot(true);
    grid->attach(ui->error_r3_plot4);

    // map 5 error to R3
    err_m5_r3 = new error_plot_data;
    err_m5_r3->duration = 1;
    err_m5_r3->period = 10;
    per_sec = err_m5_r3->period/1000.0;
    freq = 1/per_sec;
    err_m5_r3->nb_points = int(err_m5_r3->duration * freq + 1);
    err_m5_r3->real_index = 0;
    err_m5_r3->idx = 0;
    err_m5_r3->datax = new double[err_m5_r3->nb_points];
    err_m5_r3->datay = new double[err_m5_r3->nb_points];
    err_m5_r3->time = new double[2];
    err_m5_r3->val = new double[2];

    nb_per = err_m5_r3->nb_points - 1;
    err_m5_r3->datax[0] = 0;

    for(i=1;i<err_m5_r3->nb_points;i++){
       err_m5_r3->datax[i] = err_m5_r3->datax[0] + err_m5_r3->duration * i/nb_per;
       err_m5_r3->datay[i] = 0.0;
    }
    err_m5_r3->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m5_r3->data_curve->attach(ui->error_r3_plot5);
    err_m5_r3->data_curve->setRawSamples(err_m5_r3->datax, err_m5_r3->datay, err_m5_r3->idx);
    ui->error_r3_plot5->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r3_plot5->setAxisScale(QwtPlot::xBottom, err_m5_r3->datax[0], err_m5_r3->datax[err_m5_r3->nb_points - 1]);
    ui->error_r3_plot5->enableAxis(QwtPlot::xBottom, true);
    ui->error_r3_plot5->setAutoReplot(true);
    grid->attach(ui->error_r3_plot5);

    // map 6 error to R3
    err_m6_r3 = new error_plot_data;
    err_m6_r3->duration = 1;
    err_m6_r3->period = 10;
    per_sec = err_m6_r3->period/1000.0;
    freq = 1/per_sec;
    err_m6_r3->nb_points = int(err_m6_r3->duration * freq + 1);
    err_m6_r3->real_index = 0;
    err_m6_r3->idx = 0;
    err_m6_r3->datax = new double[err_m6_r3->nb_points];
    err_m6_r3->datay = new double[err_m6_r3->nb_points];
    err_m6_r3->time = new double[2];
    err_m6_r3->val = new double[2];

    nb_per = err_m6_r3->nb_points - 1;
    err_m6_r3->datax[0] = 0;

    for(i=1;i<err_m6_r3->nb_points;i++){
       err_m6_r3->datax[i] = err_m6_r3->datax[0] + err_m6_r3->duration * i/nb_per;
       err_m6_r3->datay[i] = 0.0;
    }
    err_m6_r3->data_curve = new QwtPlotCurve("error");
    // add a grid
    grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::DotLine));

    err_m6_r3->data_curve->attach(ui->error_r3_plot6);
    err_m6_r3->data_curve->setRawSamples(err_m6_r3->datax, err_m6_r3->datay, err_m6_r3->idx);
    ui->error_r3_plot6->setAxisScale(QwtPlot::yLeft, -10*BOUND, 10*BOUND);
    ui->error_r3_plot6->setAxisScale(QwtPlot::xBottom, err_m6_r3->datax[0], err_m6_r3->datax[err_m6_r3->nb_points - 1]);
    ui->error_r3_plot6->enableAxis(QwtPlot::xBottom, true);
    ui->error_r3_plot6->setAutoReplot(true);
    grid->attach(ui->error_r3_plot6);
}



void FusionMapsGui::update_visuals()
{
    int i;
    double map_updates[MAPS_NUM];

    for(i = 0;i<MAPS_NUM; i++){
        map_updates[i] = this->data_engine->map_data[i];
    }

    // map1
    this->repr_m1->setData( new RasterData(map_updates[0]));
    ui->graphicsView_m1->replot();
    // map2
    this->repr_m2->setData( new RasterData(map_updates[1]));
    ui->graphicsView_m2->replot();
    // map3
    this->repr_m3->setData( new RasterData(map_updates[2]));
    ui->graphicsView_m3->replot();
    // map4
    this->repr_m4->setData( new RasterData(map_updates[3]));
    ui->graphicsView_m4->replot();
    // map5
    this->repr_m5->setData( new RasterData(map_updates[4]));
    ui->graphicsView_m5->replot();
    // map6
    this->repr_m6->setData( new RasterData(map_updates[5]));
    ui->graphicsView_m6->replot();
    // maps labels
    QString s;
    s.sprintf("%.4f", this->data_engine->map_data[0]);
    ui->map_val1->setText("Value of the map: " + s);
    s.sprintf("%.4f", this->data_engine->map_data[1]);
    ui->map_val2->setText("Value of the map: " + s);
    s.sprintf("%.4f", this->data_engine->map_data[2]);
    ui->map_val3->setText("Value of the map: " + s);
    s.sprintf("%.4f", this->data_engine->map_data[3]);
    ui->map_val4->setText("Value of the map: " + s);
    s.sprintf("%.4f", this->data_engine->map_data[4]);
    ui->map_val5->setText("Value of the map: " + s);
    s.sprintf("%.4f", this->data_engine->map_data[5]);
    ui->map_val6->setText("Value of the map: " + s);

    // errors visuals update

    // map 1 error to R1
    this->err_m1_r1->val[0] = timer_display * this->err_m1_r1->period / 1000.0;
    this->err_m1_r1->val[1] = this->data_engine->map_err[0];
    timer_display++;

    // readjust scale to see proper values according to the received err value
    if(this->err_m1_r1->val[1] > BOUND || this->err_m1_r1->val[1] < -BOUND)
    {
       // ui->error_r1_plot1->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
    }
    if(this->err_m1_r1->idx == this->err_m1_r1->nb_points - 1){
        this->err_m1_r1->datay[this->err_m1_r1->nb_points - 1] = this->err_m1_r1->val[1];
        this->err_m1_r1->datax[0] = err_m1_r1->datax[err_m1_r1->nb_points - 1];
        for(i=1;i<this->err_m1_r1->nb_points;i++){
            this->err_m1_r1->datax[i] = this->err_m1_r1->datax[0] + this->err_m1_r1->duration * i / double(this->err_m1_r1->nb_points  - 1);
        }
        ui->error_r1_plot1->setAxisScale(QwtPlot::xBottom, this->err_m1_r1->datax[0], this->err_m1_r1->datax[this->err_m1_r1->nb_points-1]);
        this->err_m1_r1->idx = 0;
    }
    this->err_m1_r1->datay[this->err_m1_r1->idx] = this->err_m1_r1->val[1];
    this->err_m1_r1->idx++;
    this->err_m1_r1->real_index++;
    this->err_m1_r1->data_curve->setRawSamples(this->err_m1_r1->datax, this->err_m1_r1->datay, this->err_m1_r1->idx);

     // map 2 to R1
    this->err_m2_r1->val[0] = timer_display * this->err_m2_r1->period / 1000.0;
    this->err_m2_r1->val[1] = this->data_engine->map_err[1];
    timer_display++;

    // readjust scale to see proper values according to the received err value
    if(this->err_m2_r1->val[1] > BOUND || this->err_m2_r1->val[1] < -BOUND)
    {
       // ui->error_r1_plot2->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
    }
    if(this->err_m2_r1->idx == this->err_m2_r1->nb_points - 1){
        this->err_m2_r1->datay[this->err_m2_r1->nb_points - 1] = this->err_m2_r1->val[1];
        this->err_m2_r1->datax[0] = err_m2_r1->datax[err_m2_r1->nb_points - 1];
        for(i=1;i<this->err_m2_r1->nb_points;i++){
            this->err_m2_r1->datax[i] = this->err_m2_r1->datax[0] + this->err_m2_r1->duration * i / double(this->err_m2_r1->nb_points  - 1);
        }
        ui->error_r1_plot2->setAxisScale(QwtPlot::xBottom, this->err_m2_r1->datax[0], this->err_m2_r1->datax[this->err_m2_r1->nb_points-1]);
        this->err_m2_r1->idx = 0;
    }
    this->err_m2_r1->datay[this->err_m2_r1->idx] = this->err_m2_r1->val[1];
    this->err_m2_r1->idx++;
    this->err_m2_r1->real_index++;
    this->err_m2_r1->data_curve->setRawSamples(this->err_m2_r1->datax, this->err_m2_r1->datay, this->err_m2_r1->idx);

    // map 2 to R2

    this->err_m2_r2->val[0] = timer_display * this->err_m2_r2->period / 1000.0;
    this->err_m2_r2->val[1] = this->data_engine->map_err[2];
    timer_display++;

    // readjust scale to see proper values according to the received err value
    if(this->err_m2_r2->val[1] > BOUND || this->err_m2_r2->val[1] < -BOUND)
    {
       // ui->error_r2_plot2->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
    }
    if(this->err_m2_r2->idx == this->err_m2_r2->nb_points - 1){
        this->err_m2_r2->datay[this->err_m2_r2->nb_points - 1] = this->err_m2_r2->val[1];
        this->err_m2_r2->datax[0] = err_m2_r2->datax[err_m2_r2->nb_points - 1];
        for(i=1;i<this->err_m2_r2->nb_points;i++){
             this->err_m2_r2->datax[i] = this->err_m2_r2->datax[0] + this->err_m2_r2->duration * i / double(this->err_m2_r2->nb_points  - 1);
         }
        ui->error_r2_plot2->setAxisScale(QwtPlot::xBottom, this->err_m2_r2->datax[0], this->err_m2_r2->datax[this->err_m2_r2->nb_points-1]);
        this->err_m2_r2->idx = 0;
    }
    this->err_m2_r2->datay[this->err_m2_r2->idx] = this->err_m2_r2->val[1];
    this->err_m2_r2->idx++;
    this->err_m2_r2->real_index++;
    this->err_m2_r2->data_curve->setRawSamples(this->err_m2_r2->datax, this->err_m2_r2->datay, this->err_m2_r2->idx);

      // map 3 to R2
    this->err_m3_r2->val[0] = timer_display * this->err_m3_r2->period / 1000.0;
    this->err_m3_r2->val[1] = this->data_engine->map_err[3];
    timer_display++;

    // readjust scale to see proper values according to the received err value
    if(this->err_m3_r2->val[1] > BOUND || this->err_m3_r2->val[1] < -BOUND)
    {
        //ui->error_r2_plot3->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
    }
    if(this->err_m3_r2->idx == this->err_m3_r2->nb_points - 1){
        this->err_m3_r2->datay[this->err_m3_r2->nb_points - 1] = this->err_m3_r2->val[1];
        this->err_m3_r2->datax[0] = err_m3_r2->datax[err_m3_r2->nb_points - 1];
        for(i=1;i<this->err_m3_r2->nb_points;i++){
            this->err_m3_r2->datax[i] = this->err_m3_r2->datax[0] + this->err_m3_r2->duration * i / double(this->err_m3_r2->nb_points  - 1);
        }
        ui->error_r2_plot3->setAxisScale(QwtPlot::xBottom, this->err_m3_r2->datax[0], this->err_m3_r2->datax[this->err_m3_r2->nb_points-1]);
        this->err_m3_r2->idx = 0;
    }
    this->err_m3_r2->datay[this->err_m3_r2->idx] = this->err_m3_r2->val[1];
    this->err_m3_r2->idx++;
    this->err_m3_r2->real_index++;
    this->err_m3_r2->data_curve->setRawSamples(this->err_m3_r2->datax, this->err_m3_r2->datay, this->err_m3_r2->idx);

    // map 4 to R2
   this->err_m4_r2->val[0] = timer_display * this->err_m4_r2->period / 1000.0;
   this->err_m4_r2->val[1] = this->data_engine->map_err[4];
   timer_display++;

   // readjust scale to see proper values according to the received err value
   if(this->err_m4_r2->val[1] > BOUND || this->err_m4_r2->val[1] < -BOUND)
   {
       //ui->error_r2_plot4->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
   }
   if(this->err_m4_r2->idx == this->err_m4_r2->nb_points - 1){
       this->err_m4_r2->datay[this->err_m4_r2->nb_points - 1] = this->err_m4_r2->val[1];
       this->err_m4_r2->datax[0] = err_m4_r2->datax[err_m4_r2->nb_points - 1];
       for(i=1;i<this->err_m4_r2->nb_points;i++){
           this->err_m4_r2->datax[i] = this->err_m4_r2->datax[0] + this->err_m4_r2->duration * i / double(this->err_m4_r2->nb_points  - 1);
       }
       ui->error_r2_plot4->setAxisScale(QwtPlot::xBottom, this->err_m4_r2->datax[0], this->err_m4_r2->datax[this->err_m4_r2->nb_points-1]);
       this->err_m4_r2->idx = 0;
   }
   this->err_m4_r2->datay[this->err_m4_r2->idx] = this->err_m4_r2->val[1];
   this->err_m4_r2->idx++;
   this->err_m4_r2->real_index++;
   this->err_m4_r2->data_curve->setRawSamples(this->err_m4_r2->datax, this->err_m4_r2->datay, this->err_m4_r2->idx);

   // map 4 to R3

   this->err_m4_r3->val[0] = timer_display * this->err_m4_r3->period / 1000.0;
   this->err_m4_r3->val[1] = this->data_engine->map_err[5];
   timer_display++;

   // readjust scale to see proper values according to the received err value
   if(this->err_m4_r3->val[1] > BOUND || this->err_m4_r3->val[1] < -BOUND)
   {
       //ui->error_r3_plot4->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
   }
   if(this->err_m4_r3->idx == this->err_m4_r3->nb_points - 1){
       this->err_m4_r3->datay[this->err_m4_r3->nb_points - 1] = this->err_m4_r3->val[1];
       this->err_m4_r3->datax[0] = err_m4_r3->datax[err_m4_r3->nb_points - 1];
       for(i=1;i<this->err_m4_r3->nb_points;i++){
           this->err_m4_r3->datax[i] = this->err_m4_r3->datax[0] + this->err_m4_r3->duration * i / double(this->err_m4_r3->nb_points  - 1);
       }
       ui->error_r3_plot4->setAxisScale(QwtPlot::xBottom, this->err_m4_r3->datax[0], this->err_m4_r3->datax[this->err_m4_r3->nb_points-1]);
       this->err_m4_r3->idx = 0;
   }
   this->err_m4_r3->datay[this->err_m4_r3->idx] = this->err_m4_r3->val[1];
   this->err_m4_r3->idx++;
   this->err_m4_r3->real_index++;
   this->err_m4_r3->data_curve->setRawSamples(this->err_m4_r3->datax, this->err_m4_r3->datay, this->err_m4_r3->idx);

   // map 5 to R3
  this->err_m5_r3->val[0] = timer_display * this->err_m5_r3->period / 1000.0;
  this->err_m5_r3->val[1] = this->data_engine->map_err[6];
  timer_display++;

  // readjust scale to see proper values according to the received err value
  if(this->err_m5_r3->val[1] > BOUND || this->err_m5_r3->val[1] < -BOUND)
  {
      //ui->error_r3_plot5->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
  }
  if(this->err_m5_r3->idx == this->err_m5_r3->nb_points - 1){
      this->err_m5_r3->datay[this->err_m5_r3->nb_points - 1] = this->err_m5_r3->val[1];
      this->err_m5_r3->datax[0] = err_m5_r3->datax[err_m5_r3->nb_points - 1];
      for(i=1;i<this->err_m5_r3->nb_points;i++){
          this->err_m5_r3->datax[i] = this->err_m5_r3->datax[0] + this->err_m5_r3->duration * i / double(this->err_m5_r3->nb_points  - 1);
      }
      ui->error_r3_plot5->setAxisScale(QwtPlot::xBottom, this->err_m5_r3->datax[0], this->err_m5_r3->datax[this->err_m5_r3->nb_points-1]);
      this->err_m5_r3->idx = 0;
  }
  this->err_m5_r3->datay[this->err_m5_r3->idx] = this->err_m5_r3->val[1];
  this->err_m5_r3->idx++;
  this->err_m5_r3->real_index++;
  this->err_m5_r3->data_curve->setRawSamples(this->err_m5_r3->datax, this->err_m5_r3->datay, this->err_m5_r3->idx);

  // map 6 to R3

  this->err_m6_r3->val[0] = timer_display * this->err_m6_r3->period / 1000.0;
  this->err_m6_r3->val[1] = this->data_engine->map_err[7];
  timer_display++;

  // readjust scale to see proper values according to the received err value
  if(this->err_m6_r3->val[1] > BOUND || this->err_m6_r3->val[1] < -BOUND)
  {
      //ui->error_r3_plot6->setAxisScale(QwtPlot::yLeft, -5*BOUND, 5*BOUND);
  }
  if(this->err_m6_r3->idx == this->err_m6_r3->nb_points - 1){
      this->err_m6_r3->datay[this->err_m6_r3->nb_points - 1] = this->err_m6_r3->val[1];
      this->err_m6_r3->datax[0] = err_m6_r3->datax[err_m6_r3->nb_points - 1];
      for(i=1;i<this->err_m6_r3->nb_points;i++){
          this->err_m6_r3->datax[i] = this->err_m6_r3->datax[0] + this->err_m6_r3->duration * i / double(this->err_m6_r3->nb_points  - 1);
      }
      ui->error_r3_plot6->setAxisScale(QwtPlot::xBottom, this->err_m6_r3->datax[0], this->err_m6_r3->datax[this->err_m6_r3->nb_points-1]);
      this->err_m6_r3->idx = 0;
  }
  this->err_m6_r3->datay[this->err_m6_r3->idx] = this->err_m6_r3->val[1];
  this->err_m6_r3->idx++;
  this->err_m6_r3->real_index++;
  this->err_m6_r3->data_curve->setRawSamples(this->err_m6_r3->datax, this->err_m6_r3->datay, this->err_m6_r3->idx);

    // errors labels
    s.sprintf("%.4f", this->data_engine->map_err[0]);
    ui->err_r1_val1->setText("Error value with respect to R1:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[1]);
    ui->err_r1_val2->setText("Error value with respect to R1:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[2]);
    ui->err_r2_val2->setText("Error value with respect to R2:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[3]);
    ui->err_r2_val3->setText("Error value with respect to R2:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[4]);
    ui->err_r2_val4->setText("Error value with respect to R2:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[5]);
    ui->err_r3_val4->setText("Error value with respect to R3:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[6]);
    ui->err_r3_val5->setText("Error value with respect to R3:  " + s);
    s.sprintf("%.4f", this->data_engine->map_err[7]);
    ui->err_r3_val6->setText("Error value with respect to R3:  " + s);

    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents, DATA_REQ_FREQ);

}

void FusionMapsGui::send_data_request()
{
    if(net_pid!=0 && this->data_engine->running == 1){
      this->data_engine->send_method_call(REFRESH_METHOD_CALL);
    }
    update_visuals();
}

FusionMapsGui::~FusionMapsGui()
{
    delete ui;
}

void FusionMapsGui::on_actionStart_triggered()
{
    //connect error() to slot processError() to get error, if occurs.
    QObject::connect( &process, SIGNAL(error(QProcess::ProcessError)),
                      this, SLOT(error_processor(QProcess::ProcessError)));

    char *net_path_buf = (char*) calloc(150 , sizeof(char));

    net_path_buf = getcwd(net_path_buf, 150);
    net_path_buf = strcat(net_path_buf,NET_BINARY);

    //pass the name of executable that you want to launch
    process.start(net_path_buf);

    // get the PID of the spawned process
    net_pid = process.pid();

    // free allocated path and pointer
    if(net_path_buf)
        free(net_path_buf);

    // start the evil machinery only if we have started the network
    if(net_pid!=0){
        if(one_time_init==0){
            /* data acquisition from the net process only first time */
            this->data_engine->init_bus_interface();
            /* reset flag */
            one_time_init = 1;
        }
        /* start timer to get data from the net process */
        this->dbus_timer->start(DATA_REQ_FREQ);
    }
}

void FusionMapsGui::on_actionPause_triggered()
{
    if(net_pid!=getpid() && net_pid!=0)
    {
        this->data_engine->running = 0;
        this->dbus_timer->stop();
        kill(net_pid, SIGSTOP);
    }
}

void FusionMapsGui::on_actionResume_triggered()
{
    kill(net_pid, SIGCONT);
    /* start timer to get data from the net process */
    this->dbus_timer->start(DATA_REQ_FREQ);
    this->data_engine->running =1;

}

void FusionMapsGui::on_actionRestart_triggered()
{
    this->data_engine->running = 0;
    kill(net_pid, SIGUSR1);
    /* start timer to get data from the net process */
    this->dbus_timer->start(DATA_REQ_FREQ);
    this->data_engine->running =1;
}

void FusionMapsGui::on_actionStop_triggered()
{
    if(net_pid!=0){
        this->data_engine->running =0;
        this->dbus_timer->stop();
        this->data_engine->close_bus_interface();
        kill(net_pid, SIGTERM);
        net_pid = 0;
    }
}

void FusionMapsGui::on_actionQuit_triggered()
{
    if(net_pid!=0){
        this->data_engine->running =0;
        kill(net_pid, SIGTERM);
    }
    QCoreApplication::exit();
}

void FusionMapsGui::on_actionInstructions_triggered()
{
    const char* inst_str =
            " ========================================================\n"
            " Interacting Maps for Sensory Fusion - Visualization tool\n"
            " ========================================================\n"
            " This tool is responsible to start the fusion_maps binary "
            " running the main loop of the maps network. The network "
            " is looping and tries to reach a stable state. "
            " The stable(relaxed) state is defined as a state in which "
            " the values in each map satisfy the relationships in which "
            " a map is involved. This points to a relaxation technique "
            " based on gradient descent in which the net topology is not "
            " important instead the relationships and mutual influence "
            " between the maps is determining the network dynamics. \n"
            "\n The visualized is an external process that is able to: \n"
            "\n"
            " -> Start a new instance of the converging network: \n"
            "\n"
            " ---> spawns the new process that will run detached from the visualizer\n"
            "\n"
            " ---> saves the PID in order to control the execution states \n"
            "\n"
            " -> Pause a started instance and it's context is saved: \n"
            "\n"
            " ---> the context of the running network process is saved \n"
            "\n"
            " -> Resume a paused instance and it's context is restored: \n"
            "\n"
            " ---> the context of the paused network process is restored \n"
            "\n"
            " ---> the network loops from the point it was paused \n"
            "\n"
            " -> Stop a running instance and it's context is dumped: \n"
            "\n"
            " ---> the context of the running network process is dumped \n"
            "\n"
            " -> Restart a running instance and it's context is re-initialized: \n"
            "\n"
            " ---> the context of the running network is flushed and re-initialized \n"
            "\n"
            " -> Quit a started instance of the visualizer\n"
            "\n"
            "\n The visualizer is able to: \n"
            "\n"
            "--> Visualize the current value in a map (1-D) / map cell (multi-D) \n"
            "\n"
            "--> Visualize the errors with respect to the relationships in the network \n"
            "\n"
            "--> Connect to the maps input artificial user data or live sensory data \n";

    QMessageBox::information(0,INFO_HEADER_MSG,inst_str);

}

void FusionMapsGui::on_actionAbout_triggered()
{
    const char* about_str =
            " ====================================================================================================\n"
            " Synthesis of Distributed Cognitive Systems: Interacting Cortical Maps for Environmental Interpretation \n"
            " ====================================================================================================\n"
            "\n"
            " Environmental interaction is a significant aspect in the life of every physical entity, which allows the updating of its internal state and acquiring new behaviors. Such interaction is performed by repeated iterations of a perception-cognition-action cycle, in which the entity acquires and memorizes relevant information from the noisily and partially observable environment, to develop a set of applicable behaviors. This recently started research project is in the area of mobile robotics; and more specifically in explicit methods applicable for acquiring and maintaining such environmental representations. State-of-the-art implementations build upon probabilistic reasoning algorithms, which typically aim at optimal solutions with the cost of high processing requirements.\n"
            "\n"
            " In this project we are developing an alternative, neuro-biologically inspired method for real-time interpretation of sensory stimuli in mobile robotic systems: a distributed networked system with inter-merged information storage and processing that allows efficient parallel reasoning. This networked architecture will be comprised of interconnected heterogeneous software units, each encoding a different feature about the state of the environment that is represented by a local map. Such extracted pieces of environmental knowledge interact by mutual influence to ensure overall system coherence. \n"
            "\n"
            " Our main research investigates self-constructing and adapting internal relations between these maps (structural plasticity) to observed real-world relations (motor action / observed consequence). We investigate optimized network distributions on available computing resources, without an explicit a priori network topology provided by a systems designer. This new architecture reflects distributed information processing as is known to occur in brains and ensures a fast, robust and scalable computational architecture appropriate for real-time real-world robotic applications.\n"
            " \n Reference:\n"
            " \n http://www.lsr.ei.tum.de/research/research-areas/systemic-neuroscience-and-biomedical-engineering/synthesis-of-distributed-cognitive-systems-interacting-cortical-maps-for-environmental-interpretation/ \n"
            " \n Cristian Axenie - http://www.lsr.ei.tum.de/staff/detail/axenie/84/ \n";

    QMessageBox::information(0,INFO_HEADER_MSG,about_str);
}

//get errors while interacting with the network core process
void FusionMapsGui::error_processor(QProcess::ProcessError err)
{
    switch(err)
    {
    case QProcess::FailedToStart:
        QMessageBox::information(0,INFO_HEADER_MSG,"FailedToStart");
        break;
    case QProcess::UnknownError:
        QMessageBox::information(0,INFO_HEADER_MSG,"UnknownError");
        break;
    default:
        break;
    }
}


// controls signals setup

// map 1
void FusionMapsGui::on_user_data_slider1_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 1);
    }
}

void FusionMapsGui::on_user_connect_button_m1_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m1->isChecked()==true)
            this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 1);
      else
              this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 1);
    }
}

void FusionMapsGui::on_sensor_connect_button_m1_clicked()
{
  if(net_pid!=0){
      if(ui->sensor_connect_button_m1->isChecked()==true)
            this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 1);
      else
              this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 1);
    }
}

void FusionMapsGui::on_data_update_rate1_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 1);
    }
}

// map 2
void FusionMapsGui::on_user_connect_button_m2_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m2->isChecked()==true)
            this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 2);
      else
            this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 2);
    }
}

void FusionMapsGui::on_sensor_connect_button_m2_clicked()
{
  if(net_pid!=0){
      if(ui->sensor_connect_button_m2->isChecked()==true)
            this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 2);
      else
              this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 2);
    }
}

void FusionMapsGui::on_user_data_slider2_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 2);
    }
}

void FusionMapsGui::on_data_update_rate2_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 2);
    }
}

// map 3
void FusionMapsGui::on_user_connect_button_m3_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m3->isChecked()==true)
            this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 3);
      else
              this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 3);
    }
}

void FusionMapsGui::on_sensor_connect_button_m3_clicked()
{
  if(net_pid!=0){
      if(ui->sensor_connect_button_m3->isChecked()==true)
            this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 3);
      else
              this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 3);
    }
}

void FusionMapsGui::on_user_data_slider3_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 3);
    }
}

void FusionMapsGui::on_data_update_rate3_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 3);
    }
}

// map 4
void FusionMapsGui::on_user_connect_button_m4_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m4->isChecked()==true)
             this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 4);
      else
              this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 4);
    }
}

void FusionMapsGui::on_sensor_connect_button_m4_clicked()
{
  if(net_pid!=0){
      if(ui->sensor_connect_button_m4->isChecked()==true)
             this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 4);
      else
              this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 4);
    }
}

void FusionMapsGui::on_user_data_slider4_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 4);
    }
}

void FusionMapsGui::on_data_update_rate4_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 4);
    }
}


// map 5
void FusionMapsGui::on_user_connect_button_m5_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m5->isChecked()==true)
            this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 5);
      else
              this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 5);
    }
}

void FusionMapsGui::on_sensor_connect_button_m5_clicked()
{
  if(net_pid!=0){
      if(ui->sensor_connect_button_m5->isChecked()==true)
                this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 5);
      else
              this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 5);
    }
}

void FusionMapsGui::on_user_data_slider5_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 5);
    }
}

void FusionMapsGui::on_data_update_rate5_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 5);
    }
}



// map 6
void FusionMapsGui::on_user_connect_button_m6_clicked()
{
  if(net_pid!=0){
      if(ui->user_connect_button_m6->isChecked()==true)
            this->data_engine->send_signal(1.0f, USER_CONNECT_SIGNAL, 6);
      else
              this->data_engine->send_signal(0.0f, USER_CONNECT_SIGNAL, 6);
    }
}

void FusionMapsGui::on_sensor_connect_button_m6_clicked()
{
  if(net_pid!=0){
    if(ui->sensor_connect_button_m6->isChecked()==true)
            this->data_engine->send_signal(1.0f, SENSOR_CONNECT_SIGNAL, 6);
    else
            this->data_engine->send_signal(0.0f, SENSOR_CONNECT_SIGNAL, 6);
    }  
}

void FusionMapsGui::on_user_data_slider6_valueChanged(double value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, USER_DATA_CHANGED_SIGNAL, 6);
    }
}

void FusionMapsGui::on_data_update_rate6_valueChanged(int value)
{
  if(net_pid!=0){
    this->data_engine->send_signal(value, SENSOR_RATE_CHANGED_SIGNAL, 6);
    }
}

