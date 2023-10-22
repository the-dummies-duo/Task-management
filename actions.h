#ifndef ACTIONS_H
#define ACTIONS_H

#include "debug.h"

#include <QObject>
#include <QWidget>
#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#define pathify(str) (str.replace(str.find('/'), 1, "\\"))
#define CreateDirectoryFunc(path) CreateDirectory(path,NULL)
#include <windows.h>
#else
#define pathify(str) str
#include <sys/stat.h>
#define CreateDirectoryFunc(path) mkdir(path,NULL)
#endif

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
