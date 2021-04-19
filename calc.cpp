#include <iostream>
using namespace std;
#include <algorithm>
#include <qdebug.h>
double hrcalc(int array[100])
{
    int peak[20]={0},hrpeak=0;
    for (int i=2;i<100;i++)
    {
        if (i>=3&&(array[i]<array[i-3])&&(array[i]<array[i-2])&&(array[i]<array[i-1])&&(array[i]<array[i+1])&&(array[i]<array[i+2])&&(array[i]<array[i+3]))
        {
            hrpeak+=1;
            peak[hrpeak]=i;
        }
    }
    qDebug()<<"hrpeak:"<<hrpeak;
    double sum=0;
    for (int i=0;i<hrpeak;i++)
    {
        sum += peak[i+1]-peak[i];
    }
    sum = sum/(hrpeak-1);
    return 1000/sum;
}
double average(int *x, int len)

{

double sum = 0;

for (int i = 2; i < len; i++) // 求总和

sum += x[i];

return sum/len-2; // 返回平均值

}
int maxElement(int array[100])
{
    int high=0;
    for (int i=2;i<100;i++)
    {
        if (array[i]>high) high=array[i];
    }
    return high;
}
int minElement(int array[100])
{
    int low=999999;
    for (int i=2;i<100;i++)
    {
        if (array[i]<low) low=array[i];
    }
    return low;
}
double SpO2RCalc(int red[100])
{
    red[0]=red[2];
    red[1]=red[2];
    int maxRedValue = maxElement(red);
    int minRedValue = minElement(red);
    qDebug()<<"MAXMIN"<<maxRedValue<<minRedValue;
    double redAverage = average(red,100);
    double redAc = (maxRedValue - minRedValue );
    double Rred = redAc/redAverage;
    qDebug()<<"ac aver R"<<redAc<<redAverage<<Rred;
    return Rred;
}
double SpO2Calc(int red[100],int ir[100])
{
    double Rred = SpO2RCalc(red);
    double Rir = SpO2RCalc(ir);
    double R = Rir/Rred;
    return (-45.060*R*R + 30.354 *R + 94.845);

}
