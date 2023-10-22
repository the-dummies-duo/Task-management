#ifndef NEWTASK_H
#define NEWTASK_H

#include <QDialog>

#include "debug.h"
#include <nlohmann/json.hpp>
using json=nlohmann::json;

namespace Ui {
class newTask;
}

class newTask : public QDialog
{
    Q_OBJECT

public:
    explicit newTask(bool newtask = true,json* original=nullptr,QWidget *parent = nullptr);
    ~newTask();
    void accept();
    void reject();

private:
    bool newtask;
    json *original;
    Ui::newTask *ui;
};

#endif // NEWTASK_H
