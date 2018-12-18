#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMap>
#include <QList>
#include "UdpReceiver.h"
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QtDebug>
#include <QtAlgorithms>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include "datasourceobject.h"
#include "connect.h"


UdpReceiver::UdpReceiver(QObject *parent)
    : QObject(parent)
{
}


//this function inits the datasources from JSON
QMap<int, QObject*> UdpReceiver::initDataSources(){

    //Object list for one Object per Datasource
    QMap<int, QObject*>  m_DataSourceMap;

    QString jsonFileValue; //value of jasonfile, extracted as QString

    //Some file opening logics here, including existence and reading test
    QFile datasourcesjson(QStringLiteral("datasources.json"));

    //open document in read mode
    datasourcesjson.open((QIODevice::ReadOnly));


    //read whole data from json file in a Qstring
    if(!datasourcesjson.isReadable()){
        qWarning("datasources.json not readable.\n\n\n");
        return m_DataSourceMap;
    }
    else
    {
        jsonFileValue = datasourcesjson.readAll();
        datasourcesjson.close();

        QJsonDocument m_DataSourceDocument = QJsonDocument::fromJson(jsonFileValue.toUtf8());

        QJsonObject m_DataSourceObject = m_DataSourceDocument.object();

        m_DataSourceArray = m_DataSourceObject.value(QString("datasources")).toArray();

        //create for each Datasource a Instance of DataSourceObject


        for (const auto obj : m_DataSourceArray){
            m_DataSourceMap.insert(obj.toObject().value("id").toInt(),new DataSourceObject(obj.toObject().value("id").toInt(),
                                                                                           obj.toObject().value("name").toString(),
                                                                                           obj.toObject().value("displayname").toString()));
        }



        return m_DataSourceMap;

    }

}


//this function starts the receiver and opens a socket
void UdpReceiver::startUdpReceiver(){
    m_QUdpSocket = new QUdpSocket(this);
    m_QUdpSocket->bind(45454, QUdpSocket::ShareAddress);

    connect(m_QUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}



void UdpReceiver::stopUdpReceiver(){
    m_QUdpSocket->close();
    delete  m_QUdpSocket;
}


void UdpReceiver::processPendingDatagrams(){
    QByteArray m_datagram;

    while(m_QUdpSocket->hasPendingDatagrams()) {
        m_datagram.resize(int(m_QUdpSocket->pendingDatagramSize()));
        m_QUdpSocket->readDatagram(m_datagram.data(), m_datagram.size());

        QDataStream in(&m_datagram, QIODevice::ReadOnly);
        QString m_rawData = m_datagram.data();

        if(m_rawData.isEmpty()){
            m_rawData = "0,0";
        }

        QStringList m_list = m_rawData.split( "," );
        int messageID = m_list[0].toInt();
        float value = m_list[1].toFloat();

        QJsonObject JsonObj = findValueFromJsonArray(m_DataSourceArray,"id",messageID);
        QString messageName = JsonObj.value("displayname").toString().split("\"")[0];
        qWarning() << value;
        qWarning() << messageName;
        qWarning() << messageID;



    }
}



QJsonObject UdpReceiver::findValueFromJsonArray(QJsonArray arr, QString key, int val) {
    for (const auto obj : arr) {
        if (obj.toObject().value(key) == val)
            return obj.toObject();
    }
    return QJsonObject();
}







