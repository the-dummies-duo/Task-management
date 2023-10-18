#include "actions.h"
#include "mainwindow.h"

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

#define PREDEFS_H
#ifdef _WIN32
#define pathify(str) (str.replace(str.find('/'), 1, "\\"))
#define CreateDirectoryFunc(path) CreateDirectory(path,NULL)
#define GetExePath WinExePath
#include <windows.h>
#else
#define pathify(str) str
#define GetExePath getExecutablePath
#include <sys/stat.h>
#define CreateDirectoryFunc(path) mkdir(path,NULL)
#endif

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
    QLabel *label = w->findChild<QLabel*>("test_label");
    label->setText("Hello world");
}
void Actions::action_Save(){
    MainWindow* w =MainWindow::GetMainWindow();
    QTextEdit *label1 = w->findChild<QTextEdit*>("input1");
    QTextEdit *label2 = w->findChild<QTextEdit*>("input2");
    QString text1 = label1->toPlainText();
    QString text2 = label2->toPlainText();
    std::string path = GetExePath();
    std::string datapath = "./data";
    if (!(std::filesystem::exists(datapath) && std::filesystem::is_directory(datapath))){
        if (std::filesystem::exists(datapath)){
            if (!std::filesystem::remove(datapath)){
                throw std::runtime_error("Unable to remove" + datapath);
            }
        }
        CreateDirectoryFunc(L"./data");
    }
    std::ifstream f("./data/data.json");
    json j;
    std::string line;
    std::getline(f, line);
    f.clear();
    f.seekg(0);
    if (line.empty()){
        std::ofstream x("./data/data.json");
        x << "{}" << std::endl;
        x.close();
    }
    f >> j;
    if (j.empty()){
        j["tasks"] = json::array();
    }
    j["tasks"][0] = text1.toStdString();
    j["tasks"][1] = text2.toStdString();
    std::ofstream x("./data/data.json",std::ios::out|std::ios::trunc);
    std::cout << j << std::endl;
    x << j << std::endl;
}
