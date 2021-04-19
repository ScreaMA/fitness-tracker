#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weather.h"
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QList>
#include <iostream>
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Weather *weather;
    QSplineSeries *redSeries;
    QSplineSeries *irSeries;
    QChart *redChart;
    QChartView *redchartView;
    QTimer *redTimer;
    QTimer *irTimer;
    QList<uint32_t> redData;
    QList<uint32_t> irData;
    int maxsize;
    int maxX,maxY;
    void redReceived(uint32_t value);
    void irReceived(uint32_t value);

private slots:
    void startPlot();
    void startRead();
    void startIR();
    void stopPlot();
    void weatherUpdate();
    void mediaPlay();

};

#endif // MAINWINDOW_H
