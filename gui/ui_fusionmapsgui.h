/********************************************************************************
** Form generated from reading UI file 'fusionmapsgui.ui'
**
** Created: Thu Sep 20 19:51:31 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUSIONMAPSGUI_H
#define UI_FUSIONMAPSGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "qwt_plot.h"
#include "qwt_slider.h"

QT_BEGIN_NAMESPACE

class Ui_FusionMapsGui
{
public:
    QAction *actionStart;
    QAction *actionPause;
    QAction *actionResume;
    QAction *actionRestart;
    QAction *actionStop;
    QAction *actionQuit;
    QAction *actionInstructions;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_map2;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_3;
    QCheckBox *user_connect_button_m2;
    QLabel *data_label2;
    QwtPlot *graphicsView_m2;
    QLabel *err_r1_val2;
    QLabel *err_r2_val2;
    QLabel *data_update_rate2_label;
    QwtPlot *error_r1_plot2;
    QLabel *map_val2;
    QCheckBox *sensor_connect_button_m2;
    QLabel *rate_label2;
    QLabel *user_data_val2;
    QLabel *data_src_label2;
    QwtPlot *error_r2_plot2;
    QSlider *data_update_rate2;
    QwtSlider *user_data_slider2;
    QGroupBox *groupBox_map3;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_5;
    QwtPlot *graphicsView_m3;
    QwtSlider *user_data_slider3;
    QLabel *user_data_val3;
    QLabel *data_label3;
    QLabel *data_update_rate3_label;
    QLabel *rate_label3;
    QLabel *map_val3;
    QLabel *data_src_label3;
    QCheckBox *user_connect_button_m3;
    QCheckBox *sensor_connect_button_m3;
    QwtPlot *error_r2_plot3;
    QLabel *err_r2_val3;
    QSlider *data_update_rate3;
    QGroupBox *groupBox_map1;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout;
    QCheckBox *sensor_connect_button_m1;
    QLabel *rate_label1;
    QLabel *data_src_label1;
    QLabel *map_val1;
    QLabel *err_r1_val1;
    QwtSlider *user_data_slider1;
    QSlider *data_update_rate1;
    QLabel *data_update_rate1_label;
    QCheckBox *user_connect_button_m1;
    QwtPlot *error_r1_plot1;
    QwtPlot *graphicsView_m1;
    QLabel *user_data_val1;
    QLabel *data_label1;
    QGroupBox *groupBox_map6;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_6;
    QwtPlot *graphicsView_m6;
    QLabel *user_data_val6;
    QLabel *rate_label6;
    QCheckBox *sensor_connect_button_m6;
    QLabel *data_label6;
    QLabel *data_update_rate6_label;
    QLabel *data_src_label6;
    QLabel *map_val6;
    QCheckBox *user_connect_button_m6;
    QLabel *err_r3_val6;
    QwtPlot *error_r3_plot6;
    QSlider *data_update_rate6;
    QwtSlider *user_data_slider6;
    QGroupBox *groupBox_map5;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_4;
    QwtPlot *graphicsView_m5;
    QwtSlider *user_data_slider5;
    QLabel *user_data_val5;
    QLabel *data_label5;
    QLabel *data_update_rate5_label;
    QLabel *rate_label5;
    QLabel *map_val5;
    QLabel *data_src_label5;
    QCheckBox *user_connect_button_m5;
    QCheckBox *sensor_connect_button_m5;
    QwtPlot *error_r3_plot5;
    QLabel *err_r3_val5;
    QSlider *data_update_rate5;
    QGroupBox *groupBox_map4;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_2;
    QwtPlot *graphicsView_m4;
    QwtSlider *user_data_slider4;
    QLabel *user_data_val4;
    QLabel *data_label4;
    QLabel *data_update_rate4_label;
    QLabel *rate_label4;
    QLabel *data_src_label4;
    QLabel *map_val4;
    QCheckBox *user_connect_button_m4;
    QCheckBox *sensor_connect_button_m4;
    QwtPlot *error_r2_plot4;
    QLabel *err_r2_val4;
    QLabel *err_r3_val4;
    QSlider *data_update_rate4;
    QwtPlot *error_r3_plot4;
    QMenuBar *menuBar;
    QMenu *menuSimulation;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FusionMapsGui)
    {
        if (FusionMapsGui->objectName().isEmpty())
            FusionMapsGui->setObjectName(QString::fromUtf8("FusionMapsGui"));
        FusionMapsGui->setEnabled(true);
        FusionMapsGui->resize(1648, 1228);
        actionStart = new QAction(FusionMapsGui);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionPause = new QAction(FusionMapsGui);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionResume = new QAction(FusionMapsGui);
        actionResume->setObjectName(QString::fromUtf8("actionResume"));
        actionRestart = new QAction(FusionMapsGui);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
        actionStop = new QAction(FusionMapsGui);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionQuit = new QAction(FusionMapsGui);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionInstructions = new QAction(FusionMapsGui);
        actionInstructions->setObjectName(QString::fromUtf8("actionInstructions"));
        actionAbout = new QAction(FusionMapsGui);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(FusionMapsGui);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_7 = new QGridLayout(centralWidget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_map2 = new QGroupBox(centralWidget);
        groupBox_map2->setObjectName(QString::fromUtf8("groupBox_map2"));
        groupBox_map2->setAutoFillBackground(false);
        gridLayout_9 = new QGridLayout(groupBox_map2);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        user_connect_button_m2 = new QCheckBox(groupBox_map2);
        user_connect_button_m2->setObjectName(QString::fromUtf8("user_connect_button_m2"));

        gridLayout_3->addWidget(user_connect_button_m2, 3, 1, 1, 1);

        data_label2 = new QLabel(groupBox_map2);
        data_label2->setObjectName(QString::fromUtf8("data_label2"));

        gridLayout_3->addWidget(data_label2, 1, 2, 1, 1);

        graphicsView_m2 = new QwtPlot(groupBox_map2);
        graphicsView_m2->setObjectName(QString::fromUtf8("graphicsView_m2"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView_m2->sizePolicy().hasHeightForWidth());
        graphicsView_m2->setSizePolicy(sizePolicy);
        graphicsView_m2->setMaximumSize(QSize(214, 16777215));

        gridLayout_3->addWidget(graphicsView_m2, 0, 0, 3, 1);

        err_r1_val2 = new QLabel(groupBox_map2);
        err_r1_val2->setObjectName(QString::fromUtf8("err_r1_val2"));

        gridLayout_3->addWidget(err_r1_val2, 5, 0, 1, 1);

        err_r2_val2 = new QLabel(groupBox_map2);
        err_r2_val2->setObjectName(QString::fromUtf8("err_r2_val2"));

        gridLayout_3->addWidget(err_r2_val2, 5, 1, 1, 5);

        data_update_rate2_label = new QLabel(groupBox_map2);
        data_update_rate2_label->setObjectName(QString::fromUtf8("data_update_rate2_label"));

        gridLayout_3->addWidget(data_update_rate2_label, 1, 5, 1, 2);

        error_r1_plot2 = new QwtPlot(groupBox_map2);
        error_r1_plot2->setObjectName(QString::fromUtf8("error_r1_plot2"));
        sizePolicy.setHeightForWidth(error_r1_plot2->sizePolicy().hasHeightForWidth());
        error_r1_plot2->setSizePolicy(sizePolicy);
        error_r1_plot2->setMinimumSize(QSize(214, 0));
        error_r1_plot2->setMaximumSize(QSize(214, 16777215));

        gridLayout_3->addWidget(error_r1_plot2, 4, 0, 1, 1);

        map_val2 = new QLabel(groupBox_map2);
        map_val2->setObjectName(QString::fromUtf8("map_val2"));

        gridLayout_3->addWidget(map_val2, 3, 0, 1, 1);

        sensor_connect_button_m2 = new QCheckBox(groupBox_map2);
        sensor_connect_button_m2->setObjectName(QString::fromUtf8("sensor_connect_button_m2"));

        gridLayout_3->addWidget(sensor_connect_button_m2, 3, 5, 1, 1);

        rate_label2 = new QLabel(groupBox_map2);
        rate_label2->setObjectName(QString::fromUtf8("rate_label2"));

        gridLayout_3->addWidget(rate_label2, 1, 7, 1, 1);

        user_data_val2 = new QLabel(groupBox_map2);
        user_data_val2->setObjectName(QString::fromUtf8("user_data_val2"));

        gridLayout_3->addWidget(user_data_val2, 1, 1, 1, 1);

        data_src_label2 = new QLabel(groupBox_map2);
        data_src_label2->setObjectName(QString::fromUtf8("data_src_label2"));

        gridLayout_3->addWidget(data_src_label2, 2, 1, 1, 2);

        error_r2_plot2 = new QwtPlot(groupBox_map2);
        error_r2_plot2->setObjectName(QString::fromUtf8("error_r2_plot2"));
        sizePolicy.setHeightForWidth(error_r2_plot2->sizePolicy().hasHeightForWidth());
        error_r2_plot2->setSizePolicy(sizePolicy);
        error_r2_plot2->setMinimumSize(QSize(247, 0));
        error_r2_plot2->setMaximumSize(QSize(247, 16777215));

        gridLayout_3->addWidget(error_r2_plot2, 4, 1, 1, 6);

        data_update_rate2 = new QSlider(groupBox_map2);
        data_update_rate2->setObjectName(QString::fromUtf8("data_update_rate2"));
        data_update_rate2->setEnabled(false);
        data_update_rate2->setMinimum(1);
        data_update_rate2->setMaximum(3);
        data_update_rate2->setValue(1);
        data_update_rate2->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(data_update_rate2, 0, 4, 1, 1);

        user_data_slider2 = new QwtSlider(groupBox_map2);
        user_data_slider2->setObjectName(QString::fromUtf8("user_data_slider2"));
        user_data_slider2->setEnabled(false);
        user_data_slider2->setOrientation(Qt::Vertical);
        user_data_slider2->setScalePosition(QwtSlider::RightScale);
        user_data_slider2->setHandleSize(QSize(20, 16));

        gridLayout_3->addWidget(user_data_slider2, 0, 2, 1, 1);


        gridLayout_9->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map2, 0, 1, 1, 2);

        groupBox_map3 = new QGroupBox(centralWidget);
        groupBox_map3->setObjectName(QString::fromUtf8("groupBox_map3"));
        groupBox_map3->setAutoFillBackground(false);
        gridLayout_10 = new QGridLayout(groupBox_map3);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        graphicsView_m3 = new QwtPlot(groupBox_map3);
        graphicsView_m3->setObjectName(QString::fromUtf8("graphicsView_m3"));
        sizePolicy.setHeightForWidth(graphicsView_m3->sizePolicy().hasHeightForWidth());
        graphicsView_m3->setSizePolicy(sizePolicy);
        graphicsView_m3->setMaximumSize(QSize(256, 16777215));

        gridLayout_5->addWidget(graphicsView_m3, 0, 0, 2, 1);

        user_data_slider3 = new QwtSlider(groupBox_map3);
        user_data_slider3->setObjectName(QString::fromUtf8("user_data_slider3"));
        user_data_slider3->setEnabled(false);
        user_data_slider3->setOrientation(Qt::Vertical);
        user_data_slider3->setScalePosition(QwtSlider::RightScale);
        user_data_slider3->setHandleSize(QSize(20, 16));

        gridLayout_5->addWidget(user_data_slider3, 0, 1, 1, 2);

        user_data_val3 = new QLabel(groupBox_map3);
        user_data_val3->setObjectName(QString::fromUtf8("user_data_val3"));

        gridLayout_5->addWidget(user_data_val3, 1, 1, 1, 1);

        data_label3 = new QLabel(groupBox_map3);
        data_label3->setObjectName(QString::fromUtf8("data_label3"));

        gridLayout_5->addWidget(data_label3, 1, 2, 1, 2);

        data_update_rate3_label = new QLabel(groupBox_map3);
        data_update_rate3_label->setObjectName(QString::fromUtf8("data_update_rate3_label"));

        gridLayout_5->addWidget(data_update_rate3_label, 1, 4, 1, 2);

        rate_label3 = new QLabel(groupBox_map3);
        rate_label3->setObjectName(QString::fromUtf8("rate_label3"));

        gridLayout_5->addWidget(rate_label3, 1, 6, 1, 1);

        map_val3 = new QLabel(groupBox_map3);
        map_val3->setObjectName(QString::fromUtf8("map_val3"));

        gridLayout_5->addWidget(map_val3, 2, 0, 2, 1);

        data_src_label3 = new QLabel(groupBox_map3);
        data_src_label3->setObjectName(QString::fromUtf8("data_src_label3"));

        gridLayout_5->addWidget(data_src_label3, 2, 1, 1, 2);

        user_connect_button_m3 = new QCheckBox(groupBox_map3);
        user_connect_button_m3->setObjectName(QString::fromUtf8("user_connect_button_m3"));

        gridLayout_5->addWidget(user_connect_button_m3, 3, 1, 1, 1);

        sensor_connect_button_m3 = new QCheckBox(groupBox_map3);
        sensor_connect_button_m3->setObjectName(QString::fromUtf8("sensor_connect_button_m3"));

        gridLayout_5->addWidget(sensor_connect_button_m3, 3, 3, 1, 2);

        error_r2_plot3 = new QwtPlot(groupBox_map3);
        error_r2_plot3->setObjectName(QString::fromUtf8("error_r2_plot3"));
        sizePolicy.setHeightForWidth(error_r2_plot3->sizePolicy().hasHeightForWidth());
        error_r2_plot3->setSizePolicy(sizePolicy);
        error_r2_plot3->setMaximumSize(QSize(256, 16777215));

        gridLayout_5->addWidget(error_r2_plot3, 4, 0, 1, 1);

        err_r2_val3 = new QLabel(groupBox_map3);
        err_r2_val3->setObjectName(QString::fromUtf8("err_r2_val3"));

        gridLayout_5->addWidget(err_r2_val3, 5, 0, 1, 1);

        data_update_rate3 = new QSlider(groupBox_map3);
        data_update_rate3->setObjectName(QString::fromUtf8("data_update_rate3"));
        data_update_rate3->setEnabled(false);
        data_update_rate3->setMinimum(1);
        data_update_rate3->setMaximum(3);
        data_update_rate3->setValue(1);
        data_update_rate3->setOrientation(Qt::Vertical);

        gridLayout_5->addWidget(data_update_rate3, 0, 4, 1, 1);


        gridLayout_10->addLayout(gridLayout_5, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map3, 0, 3, 2, 1);

        groupBox_map1 = new QGroupBox(centralWidget);
        groupBox_map1->setObjectName(QString::fromUtf8("groupBox_map1"));
        groupBox_map1->setAutoFillBackground(false);
        groupBox_map1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayout_8 = new QGridLayout(groupBox_map1);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sensor_connect_button_m1 = new QCheckBox(groupBox_map1);
        sensor_connect_button_m1->setObjectName(QString::fromUtf8("sensor_connect_button_m1"));

        gridLayout->addWidget(sensor_connect_button_m1, 4, 3, 1, 2);

        rate_label1 = new QLabel(groupBox_map1);
        rate_label1->setObjectName(QString::fromUtf8("rate_label1"));

        gridLayout->addWidget(rate_label1, 1, 6, 1, 1);

        data_src_label1 = new QLabel(groupBox_map1);
        data_src_label1->setObjectName(QString::fromUtf8("data_src_label1"));

        gridLayout->addWidget(data_src_label1, 2, 1, 2, 2);

        map_val1 = new QLabel(groupBox_map1);
        map_val1->setObjectName(QString::fromUtf8("map_val1"));

        gridLayout->addWidget(map_val1, 3, 0, 2, 1);

        err_r1_val1 = new QLabel(groupBox_map1);
        err_r1_val1->setObjectName(QString::fromUtf8("err_r1_val1"));

        gridLayout->addWidget(err_r1_val1, 6, 0, 1, 1);

        user_data_slider1 = new QwtSlider(groupBox_map1);
        user_data_slider1->setObjectName(QString::fromUtf8("user_data_slider1"));
        user_data_slider1->setEnabled(false);
        user_data_slider1->setOrientation(Qt::Vertical);
        user_data_slider1->setScalePosition(QwtSlider::RightScale);
        user_data_slider1->setHandleSize(QSize(20, 16));

        gridLayout->addWidget(user_data_slider1, 0, 1, 1, 2);

        data_update_rate1 = new QSlider(groupBox_map1);
        data_update_rate1->setObjectName(QString::fromUtf8("data_update_rate1"));
        data_update_rate1->setEnabled(false);
        data_update_rate1->setMinimum(1);
        data_update_rate1->setMaximum(3);
        data_update_rate1->setValue(1);
        data_update_rate1->setOrientation(Qt::Vertical);

        gridLayout->addWidget(data_update_rate1, 0, 4, 1, 1);

        data_update_rate1_label = new QLabel(groupBox_map1);
        data_update_rate1_label->setObjectName(QString::fromUtf8("data_update_rate1_label"));

        gridLayout->addWidget(data_update_rate1_label, 1, 4, 1, 2);

        user_connect_button_m1 = new QCheckBox(groupBox_map1);
        user_connect_button_m1->setObjectName(QString::fromUtf8("user_connect_button_m1"));

        gridLayout->addWidget(user_connect_button_m1, 4, 1, 1, 1);

        error_r1_plot1 = new QwtPlot(groupBox_map1);
        error_r1_plot1->setObjectName(QString::fromUtf8("error_r1_plot1"));
        sizePolicy.setHeightForWidth(error_r1_plot1->sizePolicy().hasHeightForWidth());
        error_r1_plot1->setSizePolicy(sizePolicy);
        error_r1_plot1->setMaximumSize(QSize(259, 16777215));

        gridLayout->addWidget(error_r1_plot1, 5, 0, 1, 1);

        graphicsView_m1 = new QwtPlot(groupBox_map1);
        graphicsView_m1->setObjectName(QString::fromUtf8("graphicsView_m1"));
        sizePolicy.setHeightForWidth(graphicsView_m1->sizePolicy().hasHeightForWidth());
        graphicsView_m1->setSizePolicy(sizePolicy);
        graphicsView_m1->setMaximumSize(QSize(259, 16777215));

        gridLayout->addWidget(graphicsView_m1, 0, 0, 3, 1);

        user_data_val1 = new QLabel(groupBox_map1);
        user_data_val1->setObjectName(QString::fromUtf8("user_data_val1"));

        gridLayout->addWidget(user_data_val1, 1, 1, 1, 1);

        data_label1 = new QLabel(groupBox_map1);
        data_label1->setObjectName(QString::fromUtf8("data_label1"));

        gridLayout->addWidget(data_label1, 1, 2, 1, 2);


        gridLayout_8->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map1, 0, 0, 2, 1);

        groupBox_map6 = new QGroupBox(centralWidget);
        groupBox_map6->setObjectName(QString::fromUtf8("groupBox_map6"));
        groupBox_map6->setAutoFillBackground(false);
        gridLayout_11 = new QGridLayout(groupBox_map6);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        graphicsView_m6 = new QwtPlot(groupBox_map6);
        graphicsView_m6->setObjectName(QString::fromUtf8("graphicsView_m6"));
        sizePolicy.setHeightForWidth(graphicsView_m6->sizePolicy().hasHeightForWidth());
        graphicsView_m6->setSizePolicy(sizePolicy);
        graphicsView_m6->setMaximumSize(QSize(234, 16777215));

        gridLayout_6->addWidget(graphicsView_m6, 0, 0, 3, 1);

        user_data_val6 = new QLabel(groupBox_map6);
        user_data_val6->setObjectName(QString::fromUtf8("user_data_val6"));

        gridLayout_6->addWidget(user_data_val6, 1, 1, 1, 1);

        rate_label6 = new QLabel(groupBox_map6);
        rate_label6->setObjectName(QString::fromUtf8("rate_label6"));

        gridLayout_6->addWidget(rate_label6, 1, 7, 1, 1);

        sensor_connect_button_m6 = new QCheckBox(groupBox_map6);
        sensor_connect_button_m6->setObjectName(QString::fromUtf8("sensor_connect_button_m6"));

        gridLayout_6->addWidget(sensor_connect_button_m6, 4, 4, 1, 2);

        data_label6 = new QLabel(groupBox_map6);
        data_label6->setObjectName(QString::fromUtf8("data_label6"));

        gridLayout_6->addWidget(data_label6, 1, 3, 1, 1);

        data_update_rate6_label = new QLabel(groupBox_map6);
        data_update_rate6_label->setObjectName(QString::fromUtf8("data_update_rate6_label"));

        gridLayout_6->addWidget(data_update_rate6_label, 1, 5, 1, 2);

        data_src_label6 = new QLabel(groupBox_map6);
        data_src_label6->setObjectName(QString::fromUtf8("data_src_label6"));

        gridLayout_6->addWidget(data_src_label6, 2, 1, 2, 2);

        map_val6 = new QLabel(groupBox_map6);
        map_val6->setObjectName(QString::fromUtf8("map_val6"));

        gridLayout_6->addWidget(map_val6, 3, 0, 2, 1);

        user_connect_button_m6 = new QCheckBox(groupBox_map6);
        user_connect_button_m6->setObjectName(QString::fromUtf8("user_connect_button_m6"));

        gridLayout_6->addWidget(user_connect_button_m6, 4, 1, 1, 1);

        err_r3_val6 = new QLabel(groupBox_map6);
        err_r3_val6->setObjectName(QString::fromUtf8("err_r3_val6"));

        gridLayout_6->addWidget(err_r3_val6, 6, 0, 1, 1);

        error_r3_plot6 = new QwtPlot(groupBox_map6);
        error_r3_plot6->setObjectName(QString::fromUtf8("error_r3_plot6"));
        sizePolicy.setHeightForWidth(error_r3_plot6->sizePolicy().hasHeightForWidth());
        error_r3_plot6->setSizePolicy(sizePolicy);
        error_r3_plot6->setMaximumSize(QSize(234, 16777215));

        gridLayout_6->addWidget(error_r3_plot6, 5, 0, 1, 1);

        data_update_rate6 = new QSlider(groupBox_map6);
        data_update_rate6->setObjectName(QString::fromUtf8("data_update_rate6"));
        data_update_rate6->setEnabled(false);
        data_update_rate6->setMinimum(1);
        data_update_rate6->setMaximum(3);
        data_update_rate6->setValue(1);
        data_update_rate6->setOrientation(Qt::Vertical);

        gridLayout_6->addWidget(data_update_rate6, 0, 5, 1, 1);

        user_data_slider6 = new QwtSlider(groupBox_map6);
        user_data_slider6->setObjectName(QString::fromUtf8("user_data_slider6"));
        user_data_slider6->setEnabled(false);
        user_data_slider6->setOrientation(Qt::Vertical);
        user_data_slider6->setScalePosition(QwtSlider::RightScale);
        user_data_slider6->setHandleSize(QSize(20, 16));

        gridLayout_6->addWidget(user_data_slider6, 0, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_6, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map6, 2, 3, 1, 1);

        groupBox_map5 = new QGroupBox(centralWidget);
        groupBox_map5->setObjectName(QString::fromUtf8("groupBox_map5"));
        groupBox_map5->setAutoFillBackground(false);
        gridLayout_12 = new QGridLayout(groupBox_map5);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        graphicsView_m5 = new QwtPlot(groupBox_map5);
        graphicsView_m5->setObjectName(QString::fromUtf8("graphicsView_m5"));
        sizePolicy.setHeightForWidth(graphicsView_m5->sizePolicy().hasHeightForWidth());
        graphicsView_m5->setSizePolicy(sizePolicy);
        graphicsView_m5->setMaximumSize(QSize(256, 16777215));

        gridLayout_4->addWidget(graphicsView_m5, 0, 0, 2, 1);

        user_data_slider5 = new QwtSlider(groupBox_map5);
        user_data_slider5->setObjectName(QString::fromUtf8("user_data_slider5"));
        user_data_slider5->setEnabled(false);
        user_data_slider5->setOrientation(Qt::Vertical);
        user_data_slider5->setScalePosition(QwtSlider::RightScale);
        user_data_slider5->setHandleSize(QSize(20, 16));

        gridLayout_4->addWidget(user_data_slider5, 0, 1, 1, 2);

        user_data_val5 = new QLabel(groupBox_map5);
        user_data_val5->setObjectName(QString::fromUtf8("user_data_val5"));

        gridLayout_4->addWidget(user_data_val5, 1, 1, 1, 1);

        data_label5 = new QLabel(groupBox_map5);
        data_label5->setObjectName(QString::fromUtf8("data_label5"));

        gridLayout_4->addWidget(data_label5, 1, 2, 1, 2);

        data_update_rate5_label = new QLabel(groupBox_map5);
        data_update_rate5_label->setObjectName(QString::fromUtf8("data_update_rate5_label"));

        gridLayout_4->addWidget(data_update_rate5_label, 1, 4, 1, 2);

        rate_label5 = new QLabel(groupBox_map5);
        rate_label5->setObjectName(QString::fromUtf8("rate_label5"));

        gridLayout_4->addWidget(rate_label5, 1, 6, 1, 1);

        map_val5 = new QLabel(groupBox_map5);
        map_val5->setObjectName(QString::fromUtf8("map_val5"));

        gridLayout_4->addWidget(map_val5, 2, 0, 2, 1);

        data_src_label5 = new QLabel(groupBox_map5);
        data_src_label5->setObjectName(QString::fromUtf8("data_src_label5"));

        gridLayout_4->addWidget(data_src_label5, 2, 1, 1, 2);

        user_connect_button_m5 = new QCheckBox(groupBox_map5);
        user_connect_button_m5->setObjectName(QString::fromUtf8("user_connect_button_m5"));

        gridLayout_4->addWidget(user_connect_button_m5, 3, 1, 1, 1);

        sensor_connect_button_m5 = new QCheckBox(groupBox_map5);
        sensor_connect_button_m5->setObjectName(QString::fromUtf8("sensor_connect_button_m5"));

        gridLayout_4->addWidget(sensor_connect_button_m5, 3, 3, 1, 2);

        error_r3_plot5 = new QwtPlot(groupBox_map5);
        error_r3_plot5->setObjectName(QString::fromUtf8("error_r3_plot5"));
        sizePolicy.setHeightForWidth(error_r3_plot5->sizePolicy().hasHeightForWidth());
        error_r3_plot5->setSizePolicy(sizePolicy);
        error_r3_plot5->setMaximumSize(QSize(256, 16777215));

        gridLayout_4->addWidget(error_r3_plot5, 4, 0, 1, 1);

        err_r3_val5 = new QLabel(groupBox_map5);
        err_r3_val5->setObjectName(QString::fromUtf8("err_r3_val5"));

        gridLayout_4->addWidget(err_r3_val5, 5, 0, 1, 1);

        data_update_rate5 = new QSlider(groupBox_map5);
        data_update_rate5->setObjectName(QString::fromUtf8("data_update_rate5"));
        data_update_rate5->setEnabled(false);
        data_update_rate5->setMinimum(1);
        data_update_rate5->setMaximum(3);
        data_update_rate5->setValue(1);
        data_update_rate5->setOrientation(Qt::Vertical);

        gridLayout_4->addWidget(data_update_rate5, 0, 4, 1, 1);


        gridLayout_12->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map5, 1, 2, 2, 1);

        groupBox_map4 = new QGroupBox(centralWidget);
        groupBox_map4->setObjectName(QString::fromUtf8("groupBox_map4"));
        groupBox_map4->setAutoFillBackground(false);
        gridLayout_13 = new QGridLayout(groupBox_map4);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        graphicsView_m4 = new QwtPlot(groupBox_map4);
        graphicsView_m4->setObjectName(QString::fromUtf8("graphicsView_m4"));
        sizePolicy.setHeightForWidth(graphicsView_m4->sizePolicy().hasHeightForWidth());
        graphicsView_m4->setSizePolicy(sizePolicy);
        graphicsView_m4->setMaximumSize(QSize(227, 16777215));

        gridLayout_2->addWidget(graphicsView_m4, 0, 0, 3, 1);

        user_data_slider4 = new QwtSlider(groupBox_map4);
        user_data_slider4->setObjectName(QString::fromUtf8("user_data_slider4"));
        user_data_slider4->setEnabled(false);
        user_data_slider4->setOrientation(Qt::Vertical);
        user_data_slider4->setScalePosition(QwtSlider::RightScale);
        user_data_slider4->setHandleSize(QSize(20, 16));

        gridLayout_2->addWidget(user_data_slider4, 0, 1, 1, 2);

        user_data_val4 = new QLabel(groupBox_map4);
        user_data_val4->setObjectName(QString::fromUtf8("user_data_val4"));

        gridLayout_2->addWidget(user_data_val4, 1, 1, 1, 1);

        data_label4 = new QLabel(groupBox_map4);
        data_label4->setObjectName(QString::fromUtf8("data_label4"));

        gridLayout_2->addWidget(data_label4, 1, 2, 1, 1);

        data_update_rate4_label = new QLabel(groupBox_map4);
        data_update_rate4_label->setObjectName(QString::fromUtf8("data_update_rate4_label"));

        gridLayout_2->addWidget(data_update_rate4_label, 1, 3, 1, 2);

        rate_label4 = new QLabel(groupBox_map4);
        rate_label4->setObjectName(QString::fromUtf8("rate_label4"));

        gridLayout_2->addWidget(rate_label4, 1, 5, 1, 1);

        data_src_label4 = new QLabel(groupBox_map4);
        data_src_label4->setObjectName(QString::fromUtf8("data_src_label4"));

        gridLayout_2->addWidget(data_src_label4, 2, 1, 2, 2);

        map_val4 = new QLabel(groupBox_map4);
        map_val4->setObjectName(QString::fromUtf8("map_val4"));

        gridLayout_2->addWidget(map_val4, 3, 0, 2, 1);

        user_connect_button_m4 = new QCheckBox(groupBox_map4);
        user_connect_button_m4->setObjectName(QString::fromUtf8("user_connect_button_m4"));

        gridLayout_2->addWidget(user_connect_button_m4, 4, 1, 1, 1);

        sensor_connect_button_m4 = new QCheckBox(groupBox_map4);
        sensor_connect_button_m4->setObjectName(QString::fromUtf8("sensor_connect_button_m4"));

        gridLayout_2->addWidget(sensor_connect_button_m4, 4, 3, 1, 1);

        error_r2_plot4 = new QwtPlot(groupBox_map4);
        error_r2_plot4->setObjectName(QString::fromUtf8("error_r2_plot4"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(error_r2_plot4->sizePolicy().hasHeightForWidth());
        error_r2_plot4->setSizePolicy(sizePolicy1);
        error_r2_plot4->setMaximumSize(QSize(227, 16777215));

        gridLayout_2->addWidget(error_r2_plot4, 5, 0, 1, 1);

        err_r2_val4 = new QLabel(groupBox_map4);
        err_r2_val4->setObjectName(QString::fromUtf8("err_r2_val4"));

        gridLayout_2->addWidget(err_r2_val4, 6, 0, 1, 1);

        err_r3_val4 = new QLabel(groupBox_map4);
        err_r3_val4->setObjectName(QString::fromUtf8("err_r3_val4"));

        gridLayout_2->addWidget(err_r3_val4, 6, 1, 1, 3);

        data_update_rate4 = new QSlider(groupBox_map4);
        data_update_rate4->setObjectName(QString::fromUtf8("data_update_rate4"));
        data_update_rate4->setEnabled(false);
        data_update_rate4->setMinimum(1);
        data_update_rate4->setMaximum(3);
        data_update_rate4->setValue(1);
        data_update_rate4->setSliderPosition(1);
        data_update_rate4->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(data_update_rate4, 0, 3, 1, 1);

        error_r3_plot4 = new QwtPlot(groupBox_map4);
        error_r3_plot4->setObjectName(QString::fromUtf8("error_r3_plot4"));
        sizePolicy.setHeightForWidth(error_r3_plot4->sizePolicy().hasHeightForWidth());
        error_r3_plot4->setSizePolicy(sizePolicy);
        error_r3_plot4->setMaximumSize(QSize(247, 16777215));

        gridLayout_2->addWidget(error_r3_plot4, 5, 1, 1, 5);


        gridLayout_13->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_map4, 2, 0, 1, 2);

        FusionMapsGui->setCentralWidget(centralWidget);
        groupBox_map2->raise();
        groupBox_map6->raise();
        groupBox_map3->raise();
        groupBox_map4->raise();
        groupBox_map1->raise();
        groupBox_map5->raise();
        menuBar = new QMenuBar(FusionMapsGui);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1648, 22));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QString::fromUtf8("menuSimulation"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        FusionMapsGui->setMenuBar(menuBar);
        statusBar = new QStatusBar(FusionMapsGui);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FusionMapsGui->setStatusBar(statusBar);

        menuBar->addAction(menuSimulation->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSimulation->addAction(actionStart);
        menuSimulation->addAction(actionPause);
        menuSimulation->addAction(actionResume);
        menuSimulation->addAction(actionRestart);
        menuSimulation->addAction(actionStop);
        menuSimulation->addSeparator();
        menuSimulation->addAction(actionQuit);
        menuHelp->addAction(actionInstructions);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(FusionMapsGui);
        QObject::connect(user_connect_button_m1, SIGNAL(toggled(bool)), sensor_connect_button_m1, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m1, SIGNAL(toggled(bool)), user_connect_button_m1, SLOT(setDisabled(bool)));
        QObject::connect(user_data_slider1, SIGNAL(valueChanged(double)), data_label1, SLOT(setNum(double)));
        QObject::connect(user_connect_button_m1, SIGNAL(toggled(bool)), user_data_slider1, SLOT(setEnabled(bool)));
        QObject::connect(sensor_connect_button_m1, SIGNAL(toggled(bool)), user_data_slider1, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m1, SIGNAL(toggled(bool)), data_update_rate1, SLOT(setEnabled(bool)));
        QObject::connect(data_update_rate1, SIGNAL(valueChanged(int)), rate_label1, SLOT(setNum(int)));
        QObject::connect(user_connect_button_m1, SIGNAL(toggled(bool)), data_update_rate1, SLOT(setEnabled(bool)));
        QObject::connect(user_data_slider3, SIGNAL(valueChanged(double)), data_label3, SLOT(setNum(double)));
        QObject::connect(sensor_connect_button_m3, SIGNAL(toggled(bool)), data_update_rate3, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m3, SIGNAL(toggled(bool)), sensor_connect_button_m3, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m3, SIGNAL(toggled(bool)), user_connect_button_m3, SLOT(setDisabled(bool)));
        QObject::connect(user_connect_button_m3, SIGNAL(toggled(bool)), user_data_slider3, SLOT(setEnabled(bool)));
        QObject::connect(sensor_connect_button_m3, SIGNAL(toggled(bool)), user_data_slider3, SLOT(setDisabled(bool)));
        QObject::connect(data_update_rate3, SIGNAL(valueChanged(int)), rate_label3, SLOT(setNum(int)));
        QObject::connect(user_connect_button_m3, SIGNAL(toggled(bool)), data_update_rate3, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m6, SIGNAL(toggled(bool)), sensor_connect_button_m6, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m6, SIGNAL(toggled(bool)), user_connect_button_m6, SLOT(setDisabled(bool)));
        QObject::connect(user_data_slider6, SIGNAL(valueChanged(double)), data_label6, SLOT(setNum(double)));
        QObject::connect(user_connect_button_m6, SIGNAL(toggled(bool)), user_data_slider6, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m6, SIGNAL(toggled(bool)), data_update_rate6, SLOT(setEnabled(bool)));
        QObject::connect(sensor_connect_button_m6, SIGNAL(toggled(bool)), data_update_rate6, SLOT(setEnabled(bool)));
        QObject::connect(data_update_rate6, SIGNAL(valueChanged(int)), rate_label6, SLOT(setNum(int)));
        QObject::connect(user_connect_button_m5, SIGNAL(toggled(bool)), sensor_connect_button_m5, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m5, SIGNAL(toggled(bool)), user_connect_button_m5, SLOT(setDisabled(bool)));
        QObject::connect(user_data_slider5, SIGNAL(valueChanged(double)), data_label5, SLOT(setNum(double)));
        QObject::connect(user_connect_button_m5, SIGNAL(toggled(bool)), user_data_slider5, SLOT(setEnabled(bool)));
        QObject::connect(sensor_connect_button_m5, SIGNAL(toggled(bool)), user_data_slider5, SLOT(setDisabled(bool)));
        QObject::connect(data_update_rate5, SIGNAL(valueChanged(int)), rate_label5, SLOT(setNum(int)));
        QObject::connect(sensor_connect_button_m5, SIGNAL(toggled(bool)), data_update_rate5, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m5, SIGNAL(toggled(bool)), data_update_rate5, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m4, SIGNAL(toggled(bool)), sensor_connect_button_m4, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m4, SIGNAL(toggled(bool)), user_connect_button_m4, SLOT(setDisabled(bool)));
        QObject::connect(user_data_slider4, SIGNAL(valueChanged(double)), data_label4, SLOT(setNum(double)));
        QObject::connect(sensor_connect_button_m4, SIGNAL(toggled(bool)), user_data_slider4, SLOT(setDisabled(bool)));
        QObject::connect(user_connect_button_m4, SIGNAL(toggled(bool)), user_data_slider4, SLOT(setEnabled(bool)));
        QObject::connect(data_update_rate4, SIGNAL(valueChanged(int)), rate_label4, SLOT(setNum(int)));
        QObject::connect(sensor_connect_button_m4, SIGNAL(toggled(bool)), data_update_rate4, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m4, SIGNAL(toggled(bool)), data_update_rate4, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m2, SIGNAL(toggled(bool)), sensor_connect_button_m2, SLOT(setDisabled(bool)));
        QObject::connect(sensor_connect_button_m2, SIGNAL(toggled(bool)), user_connect_button_m2, SLOT(setDisabled(bool)));
        QObject::connect(user_data_slider2, SIGNAL(valueChanged(double)), data_label2, SLOT(setNum(double)));
        QObject::connect(user_connect_button_m2, SIGNAL(toggled(bool)), user_data_slider2, SLOT(setEnabled(bool)));
        QObject::connect(sensor_connect_button_m2, SIGNAL(toggled(bool)), user_data_slider2, SLOT(setDisabled(bool)));
        QObject::connect(data_update_rate2, SIGNAL(valueChanged(int)), rate_label2, SLOT(setNum(int)));
        QObject::connect(sensor_connect_button_m2, SIGNAL(toggled(bool)), data_update_rate2, SLOT(setEnabled(bool)));
        QObject::connect(user_connect_button_m2, SIGNAL(toggled(bool)), data_update_rate2, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(FusionMapsGui);
    } // setupUi

    void retranslateUi(QMainWindow *FusionMapsGui)
    {
        FusionMapsGui->setWindowTitle(QApplication::translate("FusionMapsGui", "Interacting Maps for Sensor Fusion - Visualization Tool", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("FusionMapsGui", "Start", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("FusionMapsGui", "Pause", 0, QApplication::UnicodeUTF8));
        actionResume->setText(QApplication::translate("FusionMapsGui", "Resume", 0, QApplication::UnicodeUTF8));
        actionRestart->setText(QApplication::translate("FusionMapsGui", "Restart", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("FusionMapsGui", "Stop", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("FusionMapsGui", "Quit", 0, QApplication::UnicodeUTF8));
        actionInstructions->setText(QApplication::translate("FusionMapsGui", "Instructions", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("FusionMapsGui", "About", 0, QApplication::UnicodeUTF8));
        groupBox_map2->setTitle(QApplication::translate("FusionMapsGui", "Map2", 0, QApplication::UnicodeUTF8));
        user_connect_button_m2->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        data_label2->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        err_r1_val2->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R1: ", 0, QApplication::UnicodeUTF8));
        err_r2_val2->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R2: ", 0, QApplication::UnicodeUTF8));
        data_update_rate2_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        map_val2->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m2->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        rate_label2->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        user_data_val2->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        data_src_label2->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        groupBox_map3->setTitle(QApplication::translate("FusionMapsGui", "Map3", 0, QApplication::UnicodeUTF8));
        user_data_val3->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        data_label3->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        data_update_rate3_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        rate_label3->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        map_val3->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        data_src_label3->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        user_connect_button_m3->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m3->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        err_r2_val3->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R2: ", 0, QApplication::UnicodeUTF8));
        groupBox_map1->setTitle(QApplication::translate("FusionMapsGui", "Map1", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m1->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        rate_label1->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        data_src_label1->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        map_val1->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        err_r1_val1->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R1: ", 0, QApplication::UnicodeUTF8));
        data_update_rate1_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        user_connect_button_m1->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        user_data_val1->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        data_label1->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        groupBox_map6->setTitle(QApplication::translate("FusionMapsGui", "Map6", 0, QApplication::UnicodeUTF8));
        user_data_val6->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        rate_label6->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m6->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        data_label6->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        data_update_rate6_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        data_src_label6->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        map_val6->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        user_connect_button_m6->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        err_r3_val6->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R3: ", 0, QApplication::UnicodeUTF8));
        groupBox_map5->setTitle(QApplication::translate("FusionMapsGui", "Map5", 0, QApplication::UnicodeUTF8));
        user_data_val5->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        data_label5->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        data_update_rate5_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        rate_label5->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        map_val5->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        data_src_label5->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        user_connect_button_m5->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m5->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        err_r3_val5->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R3: ", 0, QApplication::UnicodeUTF8));
        groupBox_map4->setTitle(QApplication::translate("FusionMapsGui", "Map4", 0, QApplication::UnicodeUTF8));
        user_data_val4->setText(QApplication::translate("FusionMapsGui", "User data:", 0, QApplication::UnicodeUTF8));
        data_label4->setText(QApplication::translate("FusionMapsGui", "0.0", 0, QApplication::UnicodeUTF8));
        data_update_rate4_label->setText(QApplication::translate("FusionMapsGui", "Data update rate:", 0, QApplication::UnicodeUTF8));
        rate_label4->setText(QApplication::translate("FusionMapsGui", "1", 0, QApplication::UnicodeUTF8));
        data_src_label4->setText(QApplication::translate("FusionMapsGui", "Data source:", 0, QApplication::UnicodeUTF8));
        map_val4->setText(QApplication::translate("FusionMapsGui", "Value of the map: ", 0, QApplication::UnicodeUTF8));
        user_connect_button_m4->setText(QApplication::translate("FusionMapsGui", "User", 0, QApplication::UnicodeUTF8));
        sensor_connect_button_m4->setText(QApplication::translate("FusionMapsGui", "Sensor", 0, QApplication::UnicodeUTF8));
        err_r2_val4->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R2: ", 0, QApplication::UnicodeUTF8));
        err_r3_val4->setText(QApplication::translate("FusionMapsGui", "Error value with respect to R3: ", 0, QApplication::UnicodeUTF8));
        menuSimulation->setTitle(QApplication::translate("FusionMapsGui", "Simulation", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("FusionMapsGui", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FusionMapsGui: public Ui_FusionMapsGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUSIONMAPSGUI_H
