#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include "mainwindow.h"

class Actions : public QWidget
{
public:
    static Actions *Instance();
    explicit Actions(QWidget *parent = nullptr);
    static void action_Quit();
    static void action_GitHub();

signals:

private:
    MainWindow *mainwindow;
};

#endif // ACTIONS_H
