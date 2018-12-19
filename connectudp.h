#ifndef CONNECTUDP_H
#define CONNECTUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonArray>
#include <QQmlApplicationEngine>
#include "datasourceobject.h"
#include "datasourcemodel.h"

class ConnectUdp : public QObject
{
    Q_OBJECT

public:

    //constructors and destructors
    explicit ConnectUdp(QObject *parent = nullptr);
    ~ConnectUdp()=default;

    //declarations
    QJsonArray m_DataSourceArray;

    //functions
    void startUdpReceiver();
    void stopUdpReceiver();
    //QMap<int, QObject*> initDataSources();
    void initDataSources();

public slots:


private:
    //declarations
    QUdpSocket *m_QUdpSocket = nullptr;
    QQmlApplicationEngine *engine  = nullptr;

    //functions
    QJsonObject findValueFromJsonArray(QJsonArray, QString, int);

public:
    datasourcemodel m_DataSourceModel;

    //DataSourceObject *valueobject = nullptr;

private slots:
    void processPendingDatagrams();

};

#endif // ConnectUdp_H
