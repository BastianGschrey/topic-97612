#ifndef DATASOURCEOBJECT_H
#define DATASOURCEOBJECT_H

#include <QObject>



class DataSourceObject

{

    Q_PROPERTY(double value READ value WRITE setvalue NOTIFY valueChanged)

public:

    //Constructors and destructors

    DataSourceObject(const int &id, const QString &name, const QString &displayname, const double &value);



    int id() const;

    void setid(const int &id);

    QString name() const;

    void setname(const QString &name);

    QString displayname() const;

    void setdisplayname(const QString &displayname);

    double value() const;

    void setvalue(const double &value);

signals:
    void valueChanged();


private:

    int m_id;
    QString m_name;
    QString m_displayname;
    double m_value;

};



#endif // DATASOURCEOBJECT_H
