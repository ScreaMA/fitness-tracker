

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
    void setCityName(QString cityName);
    QString getCityName();
    QString getDate();
    QString getFengLi();
    QString getWenDu();
    QString getTianQiType();
    QString getCurrentWendu();
    QString getGanMaoInfo();
    QString getAllInfo();
    bool isGetDataSuccessd();
    void refresh();
    QMap<QString, QMap<QString, QString> > getDataMap(bool *ok=nullptr);    //获取昨天以及未来5天的天气预测
    void print_Debug_allinfoMap();

signals:
    void getDataFinisedSignal();
    void getDataSuccessedSignal();
    void getDataFailedSignal();

public slots:
    void replyFinished(QNetworkReply *reply);

private:
    void queryWeather();//查询

private:
    QString cityName;
    QNetworkAccessManager *manager;  //请求句柄
    QString allinfo;       //所有信息
    QString date;
    QString fengli;       //风力
    QString wendu;        //温度
    QString currentwendu;//当前温度
    QString weather_type;  //天气类型
    QString ganmao;//对于感冒提示
    bool isGetData=false;//是否成功获取数据
    QMap<QString,QMap<QString,QString>> dataMap;
};

#endif // WEATHER_H
