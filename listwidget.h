#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "includes.h"

class listwidget : public QListWidget
{
    Q_OBJECT
public:
    void loadwidgets(QJsonObject& jsonlist);
    static listwidget& getInstance();
    static void handleclick(QListWidgetItem* item);
private:
    bool connected;
    explicit listwidget(QWidget *parent = nullptr);
    QVector<QListWidgetItem*> items;
signals:

};

#endif // LISTWIDGET_H
