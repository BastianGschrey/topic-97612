#include "datasources.h"
#include <QJsonObject>
/*
 * This class loads the available datasources from datasources.json
 * Done: can read / write json files
 * ToDo:
 * Create an Object per Datasource or create internal list of datasources(faster!)
 *
 *
 * Bastian Gschrey
 * */
Datasources::Datasources()
{


}

void Datasources::read(const QJsonObject &json){
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();
    if (json.contains("id") && json["id"].isDouble())
        mId = json["id"].toInt();
}

void Datasources::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["id"] = mId;

}
