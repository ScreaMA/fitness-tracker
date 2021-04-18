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
using namespace QtCharts;
using namespace std;
#undef slots
#include "/usr/include/python3.5m/Python.h"
#define slots Q_SLOTS
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->startButton,SIGNAL(clicked()), this,SLOT(startPlot()));
    connect(ui->stopButton,SIGNAL(clicked()), this,SLOT(stopPlot()));

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
     double hrpeak=0;
     splineSeries1->setName("MAX30102");
     for (int i=2;i<100;i++)
     {
         points[i]=QPointF(5*i,(ared[i]));
         *splineSeries1 << points[i];
         if (i>=3&&(ared[i]<ared[i-3])&&(ared[i]<ared[i-2])&&(ared[i]<ared[i-1])&&(ared[i]<ared[i+1])&&(ared[i]<ared[i+2])&&(ared[i]<ared[i+3]))
             hrpeak+=1;
         points[i]=QPointF(5*i,(air[i]));
         *splineSeries2 << points[i];
     }
     ui->lineEdit_2->setText(QString::number(hrpeak/1.5/5.2*60,10,2));
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
