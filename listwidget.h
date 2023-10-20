#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <nlohmann/json.hpp>

using json=nlohmann::json;

class listwidget : public QListWidget
{
    Q_OBJECT
public:
    void loadwidgets(const json& jsonlist);
    static listwidget& getInstance();
private:
    explicit listwidget(QWidget *parent = nullptr);
signals:

};

#endif // LISTWIDGET_H
