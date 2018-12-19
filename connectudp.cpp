#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDataStream>
#include <connectudp.h>
#include "datasourceobject.h"

ConnectUdp::ConnectUdp(QObject *parent)
    : QObject(parent)
{
    //this Map contains all datasources as Object! Definition in datasourceobject.h!
    this->initDataSources();

    //Create ConnectUdpion to QML Application
    engine = dynamic_cast<QQmlApplicationEngine*>(parent);
    if (engine == Q_NULLPTR) return;

    //make m_DataSourceModel in QML available
    engine->rootContext()->setContextProperty("dataSourceModel", &m_DataSourceModel);

    //starts now to listen to incoming UDP packages
    this->startUdpReceiver();
}


//this function inits the datasources from JSON
void ConnectUdp::initDataSources(){

    //Object Map Red-Black-Tree for one Object per Datasource with fast lookup
    //QMap<int, QObject*>  DataSourceMap;



    QString jsonFileValue; //value of jasonfile, extracted as QString

    //Some file opening logics here, including existence and reading test
    QFile datasourcesjson(QStringLiteral("datasources.json"));

    //open document in read mode
    datasourcesjson.open((QIODevice::ReadOnly));


    //read whole data from json file in a Qstring
    if(!datasourcesjson.isReadable()){
        qWarning("datasources.json not readable.\n\n\n");
        return;
    }
    else
    {
        jsonFileValue = datasourcesjson.readAll();
        datasourcesjson.close();

        QJsonDocument m_DataSourceDocument = QJsonDocument::fromJson(jsonFileValue.toUtf8());

        QJsonObject m_DataSourceObject = m_DataSourceDocument.object();

        m_DataSourceArray = m_DataSourceObject.value(QString("datasources")).toArray();

        //create for each Datasource a Instance of DataSourceObject

        //DataSourceObject *datasource = new DataSourceObject;
        //datasource->setid(88);
        //datasource->setdisplayname("rpm");
        //datasource->setname("rpm");
        //m_DataSourceModel.addDataSourceObject(datasource);

        for (const auto obj : m_DataSourceArray){

            DataSourceObject *m_datasource = new DataSourceObject;
            m_datasource->setid(obj.toObject().value("id").toInt());
            m_datasource->setname(obj.toObject().value("name").toString());
            m_datasource->setdisplayname(obj.toObject().value("displayname").toString());
            m_datasource->setvalue(0);
            m_DataSourceModel.addDataSourceObject(m_datasource);
;



           //m_DataSourceModel.addDataSourceObject(DataSourceObject(obj.toObject().value("id").toInt(),
           //                                                       obj.toObject().value("name").toString(),
           //                                                       obj.toObject().value("displayname").toString(),
           //                                                       0));


        }

        return;

    }

}


//this function starts the receiver and opens a socket
void ConnectUdp::startUdpReceiver(){
    m_QUdpSocket = new QUdpSocket(this);
    m_QUdpSocket->bind(45454, QUdpSocket::ShareAddress);

    connect(m_QUdpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}


//this function stops the receiver and opens a socket
void ConnectUdp::stopUdpReceiver(){
    m_QUdpSocket->close();
    delete  m_QUdpSocket;
}


void ConnectUdp::processPendingDatagrams(){
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
        double value = m_list[1].toDouble();

        QJsonObject JsonObj = findValueFromJsonArray(m_DataSourceArray,"id",messageID);
        QString messageName = JsonObj.value("displayname").toString().split("\"")[0];

        //poc of seeking index

        QModelIndex childIndex = m_DataSourceModel.match(m_DataSourceModel.index(0,0),Qt::UserRole,QVariant::fromValue(messageID),1,Qt::MatchRecursive)[0];

        //qWarning() << childIndex;

        //qWarning() << m_DataSourceModel.setData(childIndex,QVariant(value), Qt::EditRole);

        m_DataSourceModel.setData(childIndex,QVariant(value),Qt::UserRole+3);

        QVariant v1 = m_DataSourceModel.data(childIndex, Qt::UserRole);
        QVariant v2 = m_DataSourceModel.data(childIndex, Qt::UserRole+2);
        QVariant v3 = m_DataSourceModel.data(childIndex, Qt::UserRole+3);

        //qWarning() << v1.toInt() << v2.toString() << v3.toDouble();





    }
}

QJsonObject ConnectUdp::findValueFromJsonArray(QJsonArray arr, QString key, int val) {
    for (const auto obj : arr) {
        if (obj.toObject().value(key) == val)
            return obj.toObject();
    }
    return QJsonObject();
}
