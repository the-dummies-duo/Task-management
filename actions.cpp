#include "actions.h"
#include "mainwindow.h"
#include "newtask.h"

#include <QApplication>
#include <QLabel>
#include <QTextEdit>

#include <stdlib.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include <typeinfo>
#include <locale>

#include <QMessageBox>

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
void Actions::action_debug_text(){
    MainWindow* w =MainWindow::GetMainWindow();
    QLabel* label = w->findChild<QLabel*>("test_label");
    label->setText("Hello world");
}
void Actions::action_New(){
    newTask newtask;
    newtask.setModal(true);
    newtask.exec();
}
