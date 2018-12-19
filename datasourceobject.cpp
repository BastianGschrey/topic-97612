#include "datasourceobject.h"



DataSourceObject::DataSourceObject()
{

}

DataSourceObject::DataSourceObject(const int &id, const QString &name, const QString &displayname, const double &value, QObject *parent)
    :QObject(parent), m_id(id), m_name(name), m_displayname(displayname), m_value(value)
{

}


int DataSourceObject::id() const
{
    return m_id;
}

void DataSourceObject::setid(const int &id)
{
    if (id != m_id) {
        m_id = id;
        //emit idChanged();
    }
}


QString DataSourceObject::name() const
{
    return m_name;
}

void DataSourceObject::setname(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        //emit nameChanged();
    }
}


QString DataSourceObject::displayname() const
{
    return m_displayname;
}

void DataSourceObject::setdisplayname(const QString &displayname)
{
    if (displayname != m_displayname) {
        m_displayname = displayname;
        //emit displaynameChanged();
    }
}


double DataSourceObject::value() const
{
    return m_value;
}

void DataSourceObject::setvalue(const double &value)
{
    //if(value != m_value) {
        m_value = value;
        emit valueChanged();
        //}
}








