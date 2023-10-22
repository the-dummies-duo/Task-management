#include "listwidget.h"
#include "mainwindow.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <QListWidget>
#include <QScrollArea>
#include <QSize>
#include <QFont>
#include <qvariant.h>
#include <cstdint>
#include <typeinfo>

listwidget::listwidget(QWidget *parent)
    : QListWidget{parent}
{
    setViewMode(QListWidget::ListMode);
    QScrollArea *area = MainWindow::GetMainWindow()->findChild<QScrollArea*>("task_list");
    area->setWidget(this);

}
void listwidget::loadwidgets(json& jsonlist){
    for (int i=0;i < items.size(); i++){
        delete items[i];
    }
    items.clear();
    json templist(jsonlist["tasks"]);
    //json* mainlist = new json(jsonlist);
    std::sort(templist.begin(),templist.end(), [](const json& a, const json& b) {
        return a["title"] > b["title"];
    });
    for (const auto& json_item : templist){
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(0,30));
        item->setFont(QFont("Helvetica Neue",10));
        items.push_back(item);
        time_t reminder_time = json_item["reminder_date"];
        char reminder_text[40] = "No reminder date set";
        if (json_item["reminder_date"] != 0){
            struct tm *date;
            time(&reminder_time);
            date = localtime(&reminder_time);
            strftime( reminder_text,40, "%Y/%m/%d %H:%M", date );

        }
        else{
            reminder_time = 0;
        }
        std::string title = json_item["title"];
        std::string description = json_item["description"];
        std::string id = json_item["id"];
        std::string spaces = "";
        for (int i=0;i < 50-title.size();i++){
            spaces += " ";
        }
        item->setData(Qt::DisplayRole,QVariant((QString::fromStdString(title+spaces)+QString::fromStdString(reminder_text))));
        item->setData(Qt::ToolTipRole,QVariant(QString::fromStdString(description)));
        int index = std::find(jsonlist["tasks"].begin(),jsonlist["tasks"].end(),json_item) - jsonlist["tasks"].begin();
        std::cout << jsonlist["tasks"][index] << std::endl;
        std::cout << jsonlist["tasks"] << std::endl;
        std::cout << templist << std::endl;
        //item->setData(Qt::UserRole,QVariant(reinterpret_cast<uintptr_t>(reinterpret_cast<json*>(mainlist))));
        item->setData(Qt::UserRole+2,QVariant(QString::fromStdString(id)));
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
        std::cout << originaljson << std::endl;
    }*/
    int index = *(int*)item->data(Qt::UserRole+1).data();
    std::string id = (*(QString*)item->data(Qt::UserRole+2).data()).toStdString();
    std::cout << index << std::endl;
    std::ifstream f("./data/data.json");
    json j;
    f >> j;
    f.close();
    json tasks = j["tasks"];
    json task = *std::find_if(tasks.begin(),tasks.end(),[&id](json& a){
        a["id"] = id;
    });

}
