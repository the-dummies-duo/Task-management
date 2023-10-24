#ifndef ACTIONS_H
#define ACTIONS_H

#include "includes.h"
#include "mainwindow.h"

class Actions : public QWidget
{
public:
    static Actions *Instance();
    explicit Actions(QWidget *parent = nullptr);
    static void action_Quit();
    static void action_GitHub();
    static void action_New();

signals:

private:
    MainWindow *mainwindow;
};

#endif // ACTIONS_H
