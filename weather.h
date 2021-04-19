

#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QMultiMap>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = nullptr);
    explicit Weather(QString cityName = "");

public:
    void setCityName(QString cityName); //设置城市名
    QString getCityName();              //获取城市名
    QString getDate();                  //获取当前日期
    QString getFengLi();                //获取风向风力
    QString getWenDu();                 //获取温度范围
    QString getTianQiType();            //获取天气类型
    QString getCurrentWendu();          //获取当前温度
    QString getGanMaoInfo();            //获取感冒提示
    QString getAllInfo();               //获取原始的所有字段
    bool isGetDataSuccessd();           //是否成功获取数据
    void refresh();                     //刷新
    QMap<QString, QMap<QString, QString> > getDataMap(bool *ok=nullptr);    //获取昨天以及未来5天的天气预测
    void print_Debug_allinfoMap();      //调试打印所有信息

signals:
    void getDataFinisedSignal();//获取数据结束的信号
    void getDataSuccessedSignal();//获取数据成功的信号
    void getDataFailedSignal();//获取数据失败的信号

public slots:
    void replyFinished(QNetworkReply *reply);//刷新的槽

private:
    void queryWeather();//查询

private:
    QString cityName;
    QNetworkAccessManager *manager;  //请求句柄
    QString allinfo;       //所有信息
    //以下皆是当天，未来几天的数据框通过获取日期的数据列表
    QString date;//当前日期
    QString fengli;       //风力
    QString wendu;        //温度
    QString currentwendu;//当前温度
    QString weather_type;  //天气类型
    QString ganmao;//对于感冒提示
    bool isGetData=false;//是否成功获取数据
    QMap<QString,QMap<QString,QString>> dataMap;
};

#endif // WEATHER_H
