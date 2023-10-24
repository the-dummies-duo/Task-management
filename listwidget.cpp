#include "listwidget.h"
#include "mainwindow.h"

#include "includes.h"
#include "manager.h"
#include "newtask.h"

listwidget::listwidget(QWidget *parent)
    : QListWidget{parent}
{
    setViewMode(QListWidget::ListMode);
    QScrollArea *area = MainWindow::GetMainWindow()->findChild<QScrollArea*>("task_list");
    area->setWidget(this);

}
void listwidget::loadwidgets(QJsonObject& jsonlist){
    for (int i=0;i < items.size(); i++){
        delete items[i];
    }
    items.clear();
    QJsonArray templist = jsonlist["tasks"].toArray();
    //json* mainlist = new json(jsonlist);
    /*std::sort(templist.begin(),templist.end(), [](const auto a, const auto b) {
        return a.toObject()["title"].toString() > b.toObject()["title"].toString();
    });*/
    for (const auto& json_item_ : templist){
        QJsonObject json_item = json_item_.toObject();
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(0,30));
        item->setFont(QFont("Helvetica Neue",10));
        items.push_back(item);
        time_t reminder_time = json_item["reminder_date"].toInt();
        char reminder_text[40] = "No reminder date set";
        if (json_item["reminder_date"] != 0){
            struct tm *date;
            date = localtime(&reminder_time);
            strftime( reminder_text,40, "%Y/%m/%d %H:%M", date );

        }
        else{
            reminder_time = 0;
        }
        QString title = json_item["title"].toString();
        QString description = json_item["description"].toString();
        QString id = json_item["id"].toString();
        QString spaces = "";
        for (int i=0;i < 50-title.size();i++){
            spaces += " ";
        }
        item->setData(Qt::DisplayRole,QVariant(title+spaces+QString::fromStdString(reminder_text)));
        item->setData(Qt::ToolTipRole,QVariant(description));
        QJsonArray tasks = jsonlist["tasks"].toArray();
        int index = std::find(tasks.begin(),tasks.end(),json_item) - tasks.begin();



        //item->setData(Qt::UserRole,QVariant(reinterpret_cast<uintptr_t>(reinterpret_cast<json*>(mainlist))));
        item->setData(Qt::UserRole+2,QVariant(id));
        item->setData(Qt::UserRole+1,QVariant(index));
        addItem(item);
    }
    if (!connected){
        connect(this,&QListWidget::itemDoubleClicked,this,listwidget::handleclick);
        connected = true;
    }
}
listwidget& listwidget::getInstance(){
    static listwidget instance;
    return instance;
}
void listwidget::handleclick(QListWidgetItem* item){/*
TODO: Try to make this work
    json originaljson = (*reinterpret_cast<json*>(item->data(Qt::UserRole).data()))
    if (originaljson){

    }*/
    int index = *(int*)item->data(Qt::UserRole+1).data();
    QString id = (*(QString*)item->data(Qt::UserRole+2).data());

    QFile jsonfile("./data/data.json");
    if (!jsonfile.open(QIODevice::ReadWrite)){
        qWarning("Couldn't open json file at ./data/data.json");
    }
    QJsonObject j = manager::readdatajson();
    QJsonArray tasks = j["tasks"].toArray();
    QJsonObject task = std::find_if(tasks.begin(),tasks.end(),[&id](QJsonValueRef a_){
                           QJsonObject a = a_.toObject();
                           return a["id"] == id;
    })->toObject();
    qDebug() << task;
    newTask edit(false,&task);
    edit.exec();
}
