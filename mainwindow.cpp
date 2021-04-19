#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QThread>
#include <QList>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include <QPixmap>
#include <QChartView>
#include <QChart>
#include <QtCharts>
#include <QSplineSeries>
#include "weather.h"
#include <qdebug.h>
#include "calc.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QFile>
using namespace QtCharts;
using namespace std;
#undef slots
#include "/usr/include/python3.5m/Python.h"
#define slots Q_SLOTS
QMediaPlayer* player;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    weather=new Weather(QStringLiteral("无锡"));
    player = new QMediaPlayer(this);
    player->setVideoOutput(ui->widget);
    connect(ui->startButton,SIGNAL(clicked()), this,SLOT(startPlot()));
    connect(ui->stopButton,SIGNAL(clicked()), this,SLOT(stopPlot()));
    //connect(ui->tabWidget,SIGNAL(tabBarClicked(2)),this,SLOT(mediaPlay()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(mediaPlay()));
    connect(weather,SIGNAL(getDataSuccessedSignal()),this,SLOT(weatherUpdate()));


}
void MainWindow::weatherUpdate()
{
    ui->lineEdit_5->setText(weather->getWenDu());

}
void MainWindow::mediaPlay()
{

    //playlist = new QMediaPlaylist;
    //playlist->addMedia(QUrl("/***/test1.mp4"));
    player->setMedia(QUrl::fromLocalFile("/home/pi/1617283214156.mp4"));
    ui->widget->show();
    player->play();


}
void MainWindow::startPlot()
{
    ui->label_4->setText("loading...");
    Py_Initialize();
    if ( !Py_IsInitialized() )
        {
            QMessageBox::information(this, "INit","failed",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            return;
        }
    PyObject* pModule = PyImport_ImportModule("MAX30102");
    if (!pModule) {
                cout<< "Cant open python file!\n" << endl;
                QMessageBox::information(this, "No","failed",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                return;
            }
    PyObject* pFunc = NULL;  //py文件中的函数
    PyObject* pClass = NULL;
    PyObject* pInstance = NULL;
    PyObject* pDict = PyModule_GetDict(pModule);
    if (pDict == NULL)
        {
            cout << "Can't find the dictionary!" << endl;
            return;
        }

     pClass = PyDict_GetItemString(pDict, "MAX30102");
        if(pClass == NULL)
        {
            cout << "Can't find MAX30102 class!" << endl;
            return;
        }
     pInstance = PyObject_CallObject(pClass,nullptr);
     if (pInstance == NULL)
         {
             cout << "Can't find the instance" << endl;
             return;
         }
     pFunc = PyObject_GetAttrString(pClass,"read_sequential");
     if (pFunc == NULL)
         {
             cout << "Can't find the function" << endl;
             return;
         }
     Py_DECREF(pFunc);
     Py_DECREF(pClass);
     Py_DECREF(pModule);
     Py_DECREF(pDict);
     //PyObject* pArgs;
     //pArgs = PyTuple_New(1);
     //PyTuple_SetItem(pArgs,0,Py_BuildValue("i",100));
     PyObject* pReturn=PyObject_CallMethod(pInstance,"read_sequential",nullptr);
     if (!pReturn)
     {
         QMessageBox::information(this, "No","NORETURN",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
         return;
     }
     //PyObject* Arglist = PyTuple_New(2);
     //PyObject *PyList = PyList_New(100);
     //PyTuple_SetItem(Arglist,0,PyList);
     //PyTuple_SetItem(Arglist,1,PyList);
     int ared[100]={0};
     int air[100]={0};
     if (PyList_Check(pReturn))
     {
         cout << PyList_GET_SIZE(pReturn);
         cout << endl << "following data";
         PyObject* red = PyList_GetItem(pReturn,0);
         PyObject* ir = PyList_GetItem(pReturn,1);
         //if (PyList_Check(red)&&PyList_Check(ir))
         //{
             for (int i=0;i<100;i++)
             {
                 int result;
                 PyObject *Item = PyList_GetItem(red, i);
                 PyArg_Parse(Item, "i", &result);
                 cout << result;
                 ared[i]=result;
                 Py_DECREF(Item);
             }
             for (int i=0;i<100;i++)
             {
                 int result;
                 PyObject *Item = PyList_GetItem(ir, i);
                 PyArg_Parse(Item, "i", &result);
                 cout << result;
                 air[i]=result;
                 Py_DECREF(Item);
             }

         //}
         Py_DECREF(red);
         Py_DECREF(ir);

     }
     Py_DECREF(pInstance);
     Py_DECREF(pReturn);
     QPointF points[100]={};
     QSplineSeries *splineSeries1 = new QSplineSeries();
     QSplineSeries *splineSeries2 = new QSplineSeries();
     splineSeries1->setName("MAX30102");
     for (int i=2;i<100;i++)
     {
         points[i]=QPointF(10*i,(ared[i]));
         *splineSeries1 << points[i];
         points[i]=QPointF(10*i,(air[i]));
         *splineSeries2 << points[i];
     }
     double hr = hrcalc(ared);
     ui->lineEdit_2->setText(QString::number(hr,10,2));
     double SpO2 = SpO2Calc(ared,air);
     ui->lineEdit_3->setText(QString::number(SpO2,10,2));
     QChart *chart = new QChart();
     chart->addSeries(splineSeries1);
     chart->addSeries(splineSeries2);
     chart->legend()->hide();
     chart->setTitle("HeartBeat and SpO2");
     chart->createDefaultAxes();
     ui->graphicsView->setChart(chart);
     ui->graphicsView->setRenderHint(QPainter::Antialiasing);

     ui->label_4->setText("finished");
     //ui->label_4->setPixmap(pixmap);
}

void MainWindow::stopPlot()
{
    Py_Finalize();
}


MainWindow::~MainWindow()
{
    delete ui;

}
