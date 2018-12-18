#ifndef UdpReceiver_H
#define UdpReceiver_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonArray>
#include "datasourceobject.h"



class UdpReceiver : public QObject
{

    Q_OBJECT

public:

    //Constructor and destructor
    UdpReceiver(QObject *parent = nullptr);
    UdpReceiver(const UdpReceiver&);
    ~UdpReceiver()=default;


    //declarations
    QJsonArray m_DataSourceArray;
    //QList<QObject*> m_DataSourceList;

    //functions

    void startUdpReceiver();
    void stopUdpReceiver();
    QMap<int, QObject*> initDataSources();




private:
    //declarations
    QUdpSocket *m_QUdpSocket = nullptr;

    //functions
    QJsonObject findValueFromJsonArray(QJsonArray, QString, int);


private slots:
    void processPendingDatagrams();


};

Q_DECLARE_METATYPE(UdpReceiver)


#endif // UdpReceiver_H
