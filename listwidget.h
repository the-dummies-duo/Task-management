#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <nlohmann/json.hpp>
#include <QVector>

using json=nlohmann::json;

class listwidget : public QListWidget
{
    Q_OBJECT
public:
    void loadwidgets(json& jsonlist);
    static listwidget& getInstance();
    static void handleclick(QListWidgetItem* item);
private:
    bool connected;
    explicit listwidget(QWidget *parent = nullptr);
    QVector<QListWidgetItem*> items;
signals:

};

#endif // LISTWIDGET_H
