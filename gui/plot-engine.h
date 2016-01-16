/**
* Distributed cognitive systems design demo - data analyzer GUI.
* Simple recurrent network that converges to a stable state
* in which each of the defined relationships are satisfied.
* Plot engine functionality.
*/
#ifndef PLOTENGINE_H
#define PLOTENGINE_H

#include <qwt_color_map.h>
#include <qwt_matrix_raster_data.h>

#define MAP_DIM 1
#define BOUND  1

typedef struct{
  int duration;
  int period;
  int nb_points;
  int idx;
  int real_index;
  double *datax;
  double *datay;
  double *time;
  double *val;
  QwtPlotCurve *data_curve;
}error_plot_data;

class RasterData: public QwtMatrixRasterData
{
public:
    RasterData(double val)
    {
        double matrix[MAP_DIM];
        for(uint i = 0;i<MAP_DIM;i++){
            matrix[i] = val;
        }

        QVector<double> values;
        for ( uint i = 0; i < sizeof( matrix ) / sizeof( double ); i++ )
            values += matrix[i];

        const int numColumns = 1;
        setValueMatrix( values, numColumns );

        setInterval( Qt::XAxis,
            QwtInterval( -BOUND, BOUND, QwtInterval::ExcludeMaximum ) );
        setInterval( Qt::YAxis,
            QwtInterval( -BOUND, BOUND, QwtInterval::ExcludeMaximum ) );
        setInterval( Qt::ZAxis, QwtInterval( -BOUND, BOUND ) );
    }
};

class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::darkBlue, Qt::darkRed )
    {
        addColorStop( 0.2, Qt::blue );
        addColorStop( 0.4, Qt::cyan );
        addColorStop( 0.6, Qt::yellow );
        addColorStop( 0.8, Qt::red );
    }
};


#endif // PLOTENGINE_H
