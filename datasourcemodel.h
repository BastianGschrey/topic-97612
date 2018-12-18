#ifndef datasourcemodel_H
#define datasourcemodel_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVariantMap>
#include "datasourceobject.h"


class datasourcemodel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum datasourceRoles {
        idRole = Qt::UserRole,
        nameRole,
        displaynameRole,
        valueRole,
        allRole
    };

    datasourcemodel(QObject *parent = nullptr);

    void addDataSourceObject(const DataSourceObject &DataSourceObject);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;



    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    //Q_INVOKABLE DataSourceObject* get(int row) const;

    Q_INVOKABLE QVariantMap get(int row) const;

    //Qt::ItemFlags flags(const QModelIndex &index) const

signals:


protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<DataSourceObject> m_DataSourceObjects;




};

#endif // datasourcemodel_H
