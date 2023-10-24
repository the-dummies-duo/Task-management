#include "actions.h"
#include "mainwindow.h"
#include "newtask.h"
#include "includes.h"

Actions::Actions(QWidget *parent)
    : QWidget{parent}
{
}
void Actions::action_Quit(){
    MainWindow* w = MainWindow::GetMainWindow();
    w->close();
}
void Actions::action_GitHub(){
    system("start https://github.com/the-dummies-duo/Python-task-management");
}
void Actions::action_New(){
    newTask newtask;
    newtask.setModal(true);
    newtask.exec();
}
