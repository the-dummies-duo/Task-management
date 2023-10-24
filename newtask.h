#ifndef NEWTASK_H
#define NEWTASK_H

#include "includes.h"


namespace Ui {
class newTask;
}

class newTask : public QDialog
{
    Q_OBJECT

public:
    explicit newTask(bool newtask = true,QJsonObject* original=nullptr,QWidget *parent = nullptr);
    ~newTask();
    void accept();
    void reject();
private slots:
    void delete_();

private:
    bool newtask;
    QJsonObject *original;
    Ui::newTask *ui;
};

#endif // NEWTASK_H
