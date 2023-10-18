#include "actions.h"
//#
#include <QApplication>
#include <stdlib.h>

Actions::Actions(QWidget *parent)
    : QWidget{parent}
{
    this->mainwindow = (MainWindow*)QApplication::activeWindow();;
    this->instance = this;
}
void Actions::action_Quit(){
    MainWindow* w = (MainWindow*)QApplication::activeWindow();
    w->close();
}
Actions* Instance(){
    static Actions instance;
    return &instance;
}
void Actions::action_GitHub(){
    system("start https://github.com/the-dummies-duo/Python-task-management");
}
