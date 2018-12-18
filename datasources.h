#ifndef DATASOURCES_H
#define DATASOURCES_H

#include <QObject>

class Datasources
{
    Q_GADGET

public:
    Datasources();
    Datasources(const QString &name, const int &id);

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(int id);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString mName;
    int mId;


};

#endif // DATASOURCES_H
