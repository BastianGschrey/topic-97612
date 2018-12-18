#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonArray>
#include <QQmlApplicationEngine>
#include "datasourceobject.h"
#include "datasourcemodel.h"

class Connect : public QObject
{
    Q_OBJECT

public:

    //constructors and destructors
    explicit Connect(QObject *parent = nullptr);
    ~Connect()=default;

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

#endif // CONNECT_H
