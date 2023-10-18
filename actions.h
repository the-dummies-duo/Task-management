#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include "mainwindow.h"
#include <nlohmann/json.hpp>

class Actions : public QWidget
{
public:
    static Actions *Instance();
    explicit Actions(QWidget *parent = nullptr);
    static void action_Quit();
    static void action_GitHub();
    static void action_debug_text();
    static void action_Save();

signals:

private:
    MainWindow *mainwindow;
};

#endif // ACTIONS_H
