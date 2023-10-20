#include "listwidget.h"

#include <iostream>
#include <algorithm>

listwidget::listwidget(QWidget *parent)
    : QListWidget{parent}
{
    setViewMode(QListWidget::ListMode);
}
void listwidget::loadwidgets(const json& jsonlist){
    json templist(jsonlist);
    std::sort(templist.begin(),templist.end(), [](const json& a, const json& b) {
        return a["title"] > b["title"];
    });
    std::cout << templist << std::endl;
}
listwidget& listwidget::getInstance(){
    static listwidget instance;
    return instance;
}
