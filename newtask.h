#ifndef NEWTASK_H
#define NEWTASK_H

#include <QDialog>

#include "debug.h"

namespace Ui {
class newTask;
}

class newTask : public QDialog
{
    Q_OBJECT

public:
    explicit newTask(QWidget *parent = nullptr);
    ~newTask();
    void accept();
    void reject();

private:
    Ui::newTask *ui;
};

#endif // NEWTASK_H
