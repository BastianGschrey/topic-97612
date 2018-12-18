﻿#include "datasourcemodel.h"
#include <QDebug>

datasourcemodel::datasourcemodel(QObject *parent)
    : QAbstractListModel (parent)
{
}

void datasourcemodel::addDataSourceObject(const DataSourceObject &DataSourceObject){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_DataSourceObjects << DataSourceObject;
    endInsertRows();
}

int datasourcemodel::rowCount(const QModelIndex & parent) const{
    Q_UNUSED(parent);
    return m_DataSourceObjects.count();
}

QVariant datasourcemodel::data(const QModelIndex & index, int role) const{
    if(index.row() < 0 || index.row() >= m_DataSourceObjects.count())
        return  QVariant();

    const DataSourceObject &dataSourceObject = m_DataSourceObjects[index.row()];
    if (role == idRole)
        return dataSourceObject.id();
    else if (role == nameRole)
        return dataSourceObject.name();
    else if (role == displaynameRole)
        return dataSourceObject.displayname();
    else if (role == valueRole){
        qDebug() << dataSourceObject.value();
        return dataSourceObject.value();
    }
    //else if (role == allRole)
    //    return get(index.row());
    return QVariant();
}

bool datasourcemodel::setData(const QModelIndex &index, const QVariant &value, int role){

    DataSourceObject &dataSourceObject = m_DataSourceObjects[index.row()];
    if(role == idRole){
        dataSourceObject.setid(value.toInt());
        emit dataChanged(index,index);
        return true;
    }
    else if(role == nameRole){
        dataSourceObject.setname(value.toString());
        emit dataChanged(index,index);
        return true;
    }
    else if(role == displaynameRole){
        dataSourceObject.setdisplayname(value.toString());
        emit dataChanged(index,index);
        return true;
    }
    else if(role == valueRole){
        dataSourceObject.setvalue(value.toDouble());
        emit dataChanged(index,index);
        return true;
    }

    return false;

}







QVariantMap datasourcemodel::get(int row) const
{
    QHash<int, QByteArray> names = roleNames();
    QHashIterator<int, QByteArray> i(names);
    QVariantMap res;
    QModelIndex idx = index(row, 0);
    while(i.hasNext()) {
        i.next();
        if(i.key() != allRole){
            QVariant data = idx.data(i.key());
            res[i.value()] = data;
        }

    }
return res;
}


QHash<int, QByteArray> datasourcemodel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[nameRole] = "name";
    roles[displaynameRole] = "displayname";
    roles[valueRole] = "value";
    roles[allRole] = "all";
    return roles;
}