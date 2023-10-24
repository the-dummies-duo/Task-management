#include "manager.h"

manager::manager()
{

}
QJsonObject manager::readdatajson(){
    const QString jsonpath_q = "./data/data.json";
    QDir d("./data");
    if (!d.exists()){
        d.mkdir(".");
    }
    QFile jsonfile(jsonpath_q);
    if (!jsonfile.open(QIODevice::ReadWrite)){
        qWarning("Couldn't open json file at ./data/data.json");
    }
    QByteArray data = jsonfile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}
void manager::writejson(const QJsonObject& j){
    QFile x("./data/data.json");
    x.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    QJsonDocument temp_doc = QJsonDocument();
    temp_doc.setObject(j);
    QByteArray writedata = temp_doc.toJson();
    x.write(writedata);
    x.close();
}
