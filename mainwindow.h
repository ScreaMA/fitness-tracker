#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weather.h"

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

private slots:
    void startPlot();
    void stopPlot();
    void weatherUpdate();
    void mediaPlay();
};

#endif // MAINWINDOW_H
